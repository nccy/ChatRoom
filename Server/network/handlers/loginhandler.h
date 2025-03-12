#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "../requesthandler.h"
#include <QTcpSocket>
#include "protocol/protocolhandler.h"

/**
 * @brief 登录请求处理器
 * 职责：
 * - 验证用户登录凭证
 * - 返回登录结果响应
 */
class LoginHandler : public RequestHandler {
public:
    void process(const ProtocolHandler::Packet& packet,
                QTcpSocket* socket) override;
};

#endif // LOGINHANDLER_H
