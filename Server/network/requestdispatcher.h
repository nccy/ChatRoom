#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <QRunnable>
#include <QTcpSocket>
#include <QMutex>
#include "protocol/protocolhandler.h"

/**
 * @brief 请求分发器（线程任务）
 * 职责：
 * - 解析协议完整性
 * - 根据协议类型分发到对应处理器
 * - 保障线程安全的Socket操作
 */
class RequestDispatcher : public QRunnable {
public:
    explicit RequestDispatcher(qintptr socketDescriptor);
    void processClientData(QTcpSocket* socket, const QByteArray& data);
    void run() override;

private:
    qintptr m_socketDescriptor; // 存储socket描述符
    QMutex m_socketMutex;     // Socket操作互斥锁
    QByteArray m_receiveBuffer; // 新增接收缓冲区
    QMutex m_bufferMutex;        // 缓冲区互斥锁
};

#endif // REQUESTDISPATCHER_H
