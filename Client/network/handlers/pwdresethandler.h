// pwdresethandler.h
#ifndef PWDRESETHANDLER_H
#define PWDRESETHANDLER_H

#include "network/networkdatahandler.h"
#include "model/userinfo.h"

/**
 * @brief 密码重置响应处理器
 * 协议类型：处理 MessageType::PWD_RESET_RES (0x1004)
 */
class PwdResetHandler : public NetworkDataHandler
{
    Q_OBJECT
public:
    explicit PwdResetHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray& response) override;

signals:
    void pwdResetResult(bool success, const QString &message,const QString &newPassword);
};

#endif // PWDRESETHANDLER_H
