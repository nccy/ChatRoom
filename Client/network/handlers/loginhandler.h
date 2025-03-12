#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "network/networkdatahandler.h"
#include "model/userinfo.h"
/**
 * @brief 登录响应处理器
 * 协议类型：处理 MessageType::LOGIN_RES (0x1002)
 */
class LoginHandler : public NetworkDataHandler
{
    Q_OBJECT
public:
    explicit LoginHandler(QObject *parent = nullptr);

    // 实现基类接口
    void processResponse(const QByteArray& response) override;

signals:
    //登录信号
    void loginResult(bool success, const QString &message, const UserInfo user);
};
#endif // LOGINHANDLER_H
