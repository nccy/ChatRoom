#ifndef REGISTERHANDLER_H
#define REGISTERHANDLER_H

#include "../requesthandler.h"
#include <QTcpSocket>
#include "protocol/protocolhandler.h"

/**
 * @brief 注册请求处理器
 * 职责：
 * - 验证用户注册信息
 * - 处理用户注册逻辑
 * - 返回注册结果响应
 */
class RegisterHandler : public RequestHandler {
public:
    void process(const ProtocolHandler::Packet& packet,
                 QTcpSocket* socket) override;
};

#endif // REGISTERHANDLER_H
