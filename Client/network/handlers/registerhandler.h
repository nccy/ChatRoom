#ifndef REGISTERHANDLER_H
#define REGISTERHANDLER_H

#include "network/networkdatahandler.h"
#include "model/userinfo.h"

/**
 * @brief 注册响应处理器
 * 协议类型：处理 MessageType::REGISTER_RES (0x1004)
 */
class RegisterHandler : public NetworkDataHandler
{
    Q_OBJECT
public:
    explicit RegisterHandler(QObject *parent = nullptr);

    // 实现基类接口
    void processResponse(const QByteArray& response) override;
signals:
    //注册信号
    void registerResult(bool success, const QString &message, const UserInfo& newUser);

};

#endif // REGISTERHANDLER_H
