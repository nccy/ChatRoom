#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "protocol/protocolhandler.h"
#include <QTcpSocket>

/**
 * @brief 请求处理器抽象基类
 * 提供错误响应标准实现
 */
class RequestHandler {
public:
    virtual ~RequestHandler() = default;

    virtual void process(const ProtocolHandler::Packet& packet,
                       QTcpSocket* socket) = 0;

    // 通用发送响应方法
    static void sendResponse(QTcpSocket* socket, MessageType messageType, const QJsonObject& response);
};

#endif // REQUESTHANDLER_H
