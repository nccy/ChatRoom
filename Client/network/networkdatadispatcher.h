#ifndef NETWORKDATADISPATCHER_H
#define NETWORKDATADISPATCHER_H

#include <QRunnable>
#include <QByteArray>
#include "protocol/protocolhandler.h"
#include "network/networkdatahandler.h"

/**
 * @brief 数据分发器（线程任务）
 * 职责：
 * - 解析协议完整性
 * - 根据消息类型分发到对应处理器
 * 设计要点：
 * - 继承QRunnable适配线程池
 * - 使用智能指针自动释放资源
 */
class NetworkDataDispatcher : public QRunnable
{
public:
    explicit NetworkDataDispatcher(const QByteArray &rawData);
    void run() override;

    void connectHandler(NetworkDataHandler* handler);

private:
    const QByteArray m_rawData; // 原始网络数据（只读）
};
#endif // NETWORKDATADISPATCHER_H
