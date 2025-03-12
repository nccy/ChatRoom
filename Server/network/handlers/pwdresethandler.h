// pwdresethandler.h
#ifndef PWDRESETHANDLER_H
#define PWDRESETHANDLER_H

#include "../requesthandler.h"
#include <QTcpSocket>
#include "protocol/protocolhandler.h"

/**
 * @brief 密码重置请求处理器
 * 职责：
 * - 验证用户身份及旧密码
 * - 更新用户密码
 * - 返回密码重置结果
 */
class PwdResetHandler : public RequestHandler {
public:
    void process(const ProtocolHandler::Packet& packet,
                QTcpSocket* socket) override;
};

#endif // PWDRESETHANDLER_H
