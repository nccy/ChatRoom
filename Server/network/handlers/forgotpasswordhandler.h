#ifndef FORGOTPASSWORDHANDLER_H
#define FORGOTPASSWORDHANDLER_H

#include "../requesthandler.h"
#include <QTcpSocket>
#include "protocol/protocolhandler.h"

/**
 * @brief 忘记密码请求处理器
 * 职责：
 * - 验证手机号及验证码
 * - 返回验证结果响应
 */
class ForgotPasswordHandler : public RequestHandler {
public:
    void process(const ProtocolHandler::Packet& packet,
                QTcpSocket* socket) override;
};

#endif // FORGOTPASSWORDHANDLER_H
