#include "requestdispatcher.h"
#include "serverhandlerfactory.h"
#include <QElapsedTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QEventLoop>
#include <QDataStream>
RequestDispatcher::RequestDispatcher(qintptr socketDescriptor)
    : m_socketDescriptor(socketDescriptor) {
    setAutoDelete(true); // 任务完成后自动删除
}

/**
 * @brief RequestDispatcher::run 处理客户端请求的核心函数
 * 该函数会从客户端套接字读取数据，解析协议包，根据协议类型创建对应的请求处理器，
 * 并调用处理器处理请求，同时进行错误处理和耗时统计。
 */
void RequestDispatcher::run() {
    QTcpSocket* clientSocket = new QTcpSocket(); // 在工作线程创建socket

    // 设置socket描述符（此时已在工作线程）
    if (!clientSocket->setSocketDescriptor(m_socketDescriptor)) {
        qWarning() << "无法设置套接字描述符:" << clientSocket->errorString();
        delete clientSocket;
        return;
    }
    QObject::connect(clientSocket, &QTcpSocket::readyRead, [=]() {
        QMutexLocker lock(&m_socketMutex);

        // 读取数据并追加到缓冲区
        QByteArray newData = clientSocket->readAll();
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
            processClientData(clientSocket, completePacket);
        }
    });
    QObject::connect(clientSocket, &QTcpSocket::disconnected, [=]() {
        // 输出提示信息，表示客户端断开连接，开始清理套接字
        qDebug() << "客户端（套接字描述符: " << m_socketDescriptor << "）断开连接，开始清理套接字";
        clientSocket->deleteLater(); // 安全删除socket
    });

    // 进入事件循环以保持线程存活
    QEventLoop eventLoop;
    QObject::connect(clientSocket, &QTcpSocket::disconnected, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
}
void RequestDispatcher::processClientData(QTcpSocket* socket, const QByteArray& data) {
    ProtocolHandler::Packet packet;
    if (!ProtocolHandler::parsePacket(data, packet)) {
        RequestHandler::sendResponse(socket,MessageType::UNKNOWN,QJsonObject{
            {"success", false},
            {"message", "协议格式错误"}
        });
        socket->disconnectFromHost();
        return;
    }

    QScopedPointer<RequestHandler> handler(
        ServerHandlerFactory::createHandler(
            static_cast<MessageType>(packet.header.msgType)
        )
    );

    if (!handler) {
        RequestHandler::sendResponse(socket,MessageType::UNKNOWN,QJsonObject{
            {"success", false},
            {"message", "不支持协议"}
        });
        return;
    }

    QElapsedTimer timer;
    timer.start();
    handler->process(packet, socket);
    qDebug() << "[耗时统计] 类型: "
             << static_cast<MessageType>(packet.header.msgType)
             << "耗时:" << timer.elapsed() << "ms";
}
