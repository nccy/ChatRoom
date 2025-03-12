#ifndef FORGOTPASSWORDHANDLER_H
#define FORGOTPASSWORDHANDLER_H

#include "network/networkdatahandler.h"
#include <QObject>

/**
 * @brief 忘记密码响应处理器
 * 协议类型：处理 MessageType::FORGOT_PWD_RES
 */
class ForgotPasswordHandler : public NetworkDataHandler
{
    Q_OBJECT
public:
    explicit ForgotPasswordHandler(QObject *parent = nullptr);

    // 实现基类接口
    void processResponse(const QByteArray &response) override;

signals:
    // 验证码验证结果信号
    void codeVerificationResult(bool success, const QString &message, const QString &phoneNumber);
};

#endif // FORGOTPASSWORDHANDLER_H
