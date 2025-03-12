#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QThreadPool>


/**
 * @brief TCP服务器主类
 * 职责：
 * - 监听指定端口接受客户端连接
 * - 使用线程池处理并发请求
 * - 管理网络连接生命周期
 */
class TcpServer : public QTcpServer {
    Q_OBJECT
public:
    explicit TcpServer(QObject* parent = nullptr, quint16 port = 12345);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QThreadPool m_threadPool;  // 请求处理线程池
};

#endif // TCPSERVER_H
