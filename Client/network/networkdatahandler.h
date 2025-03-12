#ifndef NETWORKDATAHANDLER_H
#define NETWORKDATAHANDLER_H

#include <QObject>
#include <QByteArray>
#include "controller/clientcontroller.h"

/**
 * @brief 客户端网络数据处理基类
 * 职责：
 * - 定义响应解析接口
 * - 提供信号通知机制
 */
class NetworkDataHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkDataHandler(QObject *parent = nullptr); // 显式声明构造函数

    // 纯虚函数：必须由子类实现响应解析逻辑
    virtual void processResponse(const QByteArray& response) = 0;

signals:
    /// 通用操作结果信号
    void operationComplete(bool success, const QString& message);

};
#endif // NETWORKDATAHANDLER_H
