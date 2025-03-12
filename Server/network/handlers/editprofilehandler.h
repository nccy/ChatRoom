#ifndef EDITPROFILEHANDLER_H
#define EDITPROFILEHANDLER_H

#include "../requesthandler.h"
#include <QTcpSocket>
#include "protocol/protocolhandler.h"

/**
 * @brief 编辑用户资料请求处理器
 * 职责：
 * - 处理用户资料编辑请求
 * - 返回编辑结果响应
 */
class EditProfileHandler : public RequestHandler {
public:
    void process(const ProtocolHandler::Packet& packet,
                 QTcpSocket* socket) override;
};

#endif // EDITPROFILEHANDLER_H
