#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include <QMutex>
#include "protocol/protocolhandler.h"

class NetworkDataDispatcher;

/**
 * @brief TCP客户端核心管理类（单例模式）
 * 职责：
 * - 维护唯一Socket连接
 * - 提供线程安全的数据发送接口
 * - 接收数据并分发给处理器
 */
class TcpClient : public QObject
{
    Q_OBJECT
public:
    static TcpClient* instance();

    // 连接管理
    void connectToServer(const QString& host, quint16 port);
    void disconnectFromHost();
    bool isConnected() const;

    // 发送协议数据包（线程安全）
    void sendPacket(MessageType type, const QJsonDocument& data);

signals:

    void connectionStatusChanged(bool connected); // 连接状态变化信号

private slots:
    void onSocketReadyRead();    // 接收数据槽
    void onSocketConnected();    // 连接成功槽
    void onSocketDisconnected(); // 连接断开槽

private:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();

    QTcpSocket* m_socket;                 // Socket连接对象
    mutable QMutex m_socketMutex;        // Socket操作互斥锁
    QThreadPool m_dispatcherPool;       // 数据分发线程池
    QByteArray m_receiveBuffer; // 新增接收缓冲区
    QMutex m_bufferMutex;        // 缓冲区互斥锁

    static QMutex s_instanceMutex;      // 单例实例互斥锁
    static TcpClient* m_instance;       // 单例实例指针
};
#endif // TCPCLIENT_H
