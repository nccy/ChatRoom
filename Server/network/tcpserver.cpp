#include "tcpserver.h"
#include "requestdispatcher.h"
#include <QTcpSocket>
#include <QDebug>

TcpServer::TcpServer(QObject* parent, quint16 port)
    : QTcpServer(parent)
{
    if (!listen(QHostAddress::Any, port)) {
        qCritical() << "服务端启动失败:" << errorString();
    } else {
        qInfo() << "服务端正在监听端口：" << port;
    }
    // 初始化线程池
    const int coreCount = QThread::idealThreadCount();

    m_threadPool.setMaxThreadCount(qMax(4, coreCount * 2));  // 根据CPU核心数调整

    qDebug()
        << "服务器正在启动..."
        << "\nCPU核心数: " << coreCount
        << "\n线程池大小: " << m_threadPool.maxThreadCount()
        << "\n监听端口: " << port;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    // 输出提示信息，表示有新的客户端连接请求，显示其套接字描述符
    qDebug() << "收到新的客户端连接请求，套接字描述符: " << socketDescriptor;

    // 直接创建任务并传递socket描述符到线程池
    m_threadPool.start(new RequestDispatcher(socketDescriptor));


//    QTcpSocket* clientSocket = new QTcpSocket(this);
//    // 尝试为客户端套接字设置套接字描述符，并检查是否成功
//    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
//        qDebug() << "成功为客户端套接字设置描述符: " << socketDescriptor;

//        // 连接数据到达信号
//        connect(clientSocket, &QTcpSocket::readyRead, [=]() {
//            if (clientSocket->bytesAvailable() > 0) {
//                // 输出提示信息，表示有数据到达，开始分发请求
//                qDebug() << "客户端（套接字描述符: " << socketDescriptor << "）有数据到达，开始分发请求到线程池处理";
//                m_threadPool.start(new RequestDispatcher(clientSocket));
//            }
//        });

//        // 自动清理断开连接的socket
//        connect(clientSocket, &QTcpSocket::disconnected, [=]() {
//            // 输出提示信息，表示客户端断开连接，开始清理套接字
//            qDebug() << "客户端（套接字描述符: " << socketDescriptor << "）断开连接，开始清理套接字";
//            clientSocket->deleteLater();
//        });
//    } else {
//        // 若设置套接字描述符失败，输出错误提示信息
//        qWarning() << "无法为客户端套接字设置描述符: " << socketDescriptor << "，错误信息: " << clientSocket->errorString();
//        delete clientSocket;
//    }
}
