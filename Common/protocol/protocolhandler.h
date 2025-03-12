#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include "protocolheader.h"
#include "messagetype.h"
#include <QByteArray>
#include <QJsonDocument>

/**
 * @brief 协议处理核心类
 * 功能：
 * - 构建发送数据包
 * - 解析接收数据包
 * - 校验数据完整性
 */
class ProtocolHandler {
public:
    /// 按照 1 字节对齐  不进行额外的字节填充
    #pragma pack(push, 1)
    struct Packet {
        ProtocolHeader header;
        QByteArray body;
    };
    #pragma pack(pop)

    /// 构建网络数据包
    static QByteArray buildPacket(MessageType type, const QJsonDocument& content);

    /// 解析网络数据包
    static bool parsePacket(const QByteArray& rawData, Packet& outPacket);
};

#endif // PROTOCOLHANDLER_H
