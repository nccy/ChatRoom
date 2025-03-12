// tcplient.cpp
#include "tcpclient.h"
#include "networkdatadispatcher.h"
#include <QDataStream>
#include "protocol/protocolhandler.h"

// 静态成员初始化
QMutex TcpClient::s_instanceMutex;
TcpClient* TcpClient::m_instance = nullptr;

TcpClient* TcpClient::instance() {
    // 双重检查锁定保证线程安全
    if (!m_instance) {
        QMutexLocker lock(&s_instanceMutex);
        if (!m_instance) {
            qDebug() << "创建TcpClient单例实例";
            m_instance = new TcpClient();
        }
    }
    return m_instance;
}

TcpClient::TcpClient(QObject *parent)
    : QObject(parent),
      m_socket(new QTcpSocket(this)),
      m_dispatcherPool(new QThreadPool(this))
{
    // 配置线程池（最多同时处理4个数据包）
    // 初始化线程池
    const int coreCount = QThread::idealThreadCount();
    m_dispatcherPool.setMaxThreadCount(qMax(4, coreCount * 2));  // 根据CPU核心数调整
    qDebug() << "线程池最大线程数设置为:" << m_dispatcherPool.maxThreadCount();

    // 连接Socket信号槽
    connect(m_socket, &QTcpSocket::connected,
            this, &TcpClient::onSocketConnected);
    connect(m_socket, &QTcpSocket::disconnected,
            this, &TcpClient::onSocketDisconnected);
    connect(m_socket, &QTcpSocket::readyRead,
            this, &TcpClient::onSocketReadyRead);

    qDebug() << "TcpClient已初始化，Socket信号槽已连接";
}

TcpClient::~TcpClient() {
    qDebug() << "TcpClient析构，尝试断开与服务器的连接";
    disconnectFromHost();
    delete m_socket;
    qDebug() << "TcpClient析构完成，Socket已删除";
}

void TcpClient::connectToServer(const QString& host, quint16 port) {
    QMutexLocker lock(&m_socketMutex);
    if (m_socket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "尝试连接到服务器......  主机:" << host << "端口:" << port;
        m_socket->connectToHost(host, port);
    } else {
        qDebug() << "Socket状态不是未连接状态，无法发起新的连接";
    }
}

void TcpClient::disconnectFromHost() {
    QMutexLocker lock(&m_socketMutex);
    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        qDebug() << "尝试断开与服务器的连接";
        m_socket->disconnectFromHost();
    } else {
        qDebug() << "Socket状态已是未连接状态，无需断开连接";
    }
}

bool TcpClient::isConnected() const {
    QMutexLocker lock(&m_socketMutex);
    bool connected = m_socket->state() == QAbstractSocket::ConnectedState;
    qDebug() << "检查连接状态，当前连接状态为:" << (connected ? "已连接" : "未连接");
    return connected;
}

void TcpClient::sendPacket(MessageType type, const QJsonDocument& data) {
    QMutexLocker lock(&m_socketMutex);
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "尝试发送数据包，消息类型:" << type;
        const QByteArray packet = ProtocolHandler::buildPacket(type, data);
        qint64 bytesWritten = m_socket->write(packet);
        if (bytesWritten == -1) {
            qWarning() << "发送数据包失败:" << m_socket->errorString();
        } else if (bytesWritten < packet.size()) {
            qWarning() << "部分数据已发送:" << bytesWritten << "/" << packet.size();
        } else {
            qDebug() << "数据包发送成功，发送字节数:" << bytesWritten;
        }
    } else {
        qDebug() << "Socket未连接，无法发送数据包";
    }
}

// 私有槽函数实现
void TcpClient::onSocketConnected() {
    qDebug() << "已连接到服务器";
    emit connectionStatusChanged(true);
}

void TcpClient::onSocketDisconnected() {
    qDebug() << "已断开与服务器的连接";
    emit connectionStatusChanged(false);
}

void TcpClient::onSocketReadyRead() {
    QMutexLocker lock(&m_socketMutex);

    // 读取数据并追加到缓冲区
    QByteArray newData = m_socket->readAll();
    {
        QMutexLocker bufferLock(&m_bufferMutex);
        m_receiveBuffer.append(newData);
    }

    // 循环处理完整包
    while (true) {
        QByteArray completePacket;
        {
            QMutexLocker bufferLock(&m_bufferMutex);

            // 检查是否有足够数据解析包头
            if (m_receiveBuffer.size() < static_cast<int>(sizeof(ProtocolHeader))) {
                break;
            }

            // 解析包头（不移动缓冲区指针）
            QDataStream headerStream(m_receiveBuffer);
            headerStream.setByteOrder(QDataStream::LittleEndian);

            quint32 dataSize;
            quint16 magic, msgType;
            headerStream >> dataSize >> magic >> msgType;

            if (magic != PROTOCOL_MAGIC ) {
                qCritical() << "协议错误，清空缓冲区或超出限制";
                m_receiveBuffer.clear();
                break;
            }

            // 检查数据完整性
            const quint32 totalPacketSize = sizeof(dataSize) + sizeof(magic) + sizeof(msgType) + dataSize;
            if (m_receiveBuffer.size() < static_cast<int>(totalPacketSize)) {
                break; // 等待更多数据
            }

            // 提取完整包
            completePacket = m_receiveBuffer.left(totalPacketSize);
            m_receiveBuffer.remove(0, totalPacketSize); // 移除已处理数据
        }
        qDebug() << "分发完整包，大小:" << completePacket.size();
        // 分发完整数据包
        NetworkDataDispatcher* task = new NetworkDataDispatcher(completePacket);
        m_dispatcherPool.start(task);

    }
}
