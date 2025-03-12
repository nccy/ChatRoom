#ifndef PROTOCOLHEADER_H
#define PROTOCOLHEADER_H

#include <QtGlobal>

/**
 * @brief 协议头结构体
 * 内存布局（总长度8字节，尽量保持4的整数倍，方便后续计算字节数不用考虑补齐）：
 * +----------------+----------------+----------------+
 * |  数据长度(4)   |  魔数(2)       |  消息类型(2)   |
 * +----------------+----------------+----------------+
 */

struct ProtocolHeader {
    quint32 dataSize;  ///< JSON 数据部分的长度（不含协议头）
    quint16 magic;     ///< 固定值0x12345678，用于校验数据有效性
    quint16 msgType;   ///< 消息类型（对应MessageType枚举值）
};

constexpr quint16 PROTOCOL_MAGIC = 0x1234; ///< 协议魔数定义

#endif // PROTOCOLHEADER_H
