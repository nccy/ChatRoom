#include "protocolhandler.h"
#include <QDataStream>
#include <QJsonParseError>
#include <QDebug>

/*
|----------------|----------------|----------------|----------------|
| dataSize (4)   | magic (2)      | msgType (2)    | JSON数据 (N)   |
|----------------|----------------|----------------|----------------|
*/

/**
 * @brief 构建网络数据包
 *
 * 该函数用于根据给定的消息类型和JSON文档内容构建一个完整的网络数据包。
 * 数据包的结构由协议头和JSON数据组成，协议头包含数据大小、魔数和消息类型信息。
 *
 * @param type 消息类型，使用MessageType枚举表示
 * @param content JSON文档内容，包含实际要传输的数据
 * @return QByteArray 构建好的网络数据包，以字节数组形式返回
 */
QByteArray ProtocolHandler::buildPacket(MessageType type, const QJsonDocument& content) {
    // 创建一个空的字节数组，用于存储最终的数据包
    QByteArray packet;
    // 创建一个QDataStream对象，将其与packet关联，并设置为只写模式
    QDataStream stream(&packet, QIODevice::WriteOnly);
    // 设置数据流的字节序为小端字节序，确保数据在不同设备间传输的一致性
    stream.setByteOrder(QDataStream::LittleEndian);

    // 构造协议头
    // 将JSON文档转换为紧凑格式的字节数组
    const QByteArray jsonData = content.toJson(QJsonDocument::Compact);
    // 初始化协议头结构体，包含数据大小、魔数和消息类型
    ProtocolHeader header{
        // 数据大小为JSON数据的字节数
        .dataSize = static_cast<quint32>(jsonData.size()),
        // 魔数，用于标识协议类型，确保数据的合法性
        .magic = PROTOCOL_MAGIC,
        // 将消息类型枚举转换为无符号16位整数
        .msgType = static_cast<quint16>(type)
    };

    // 写入二进制数据
    // 将协议头的各个字段按顺序写入数据流
    stream << header.dataSize << header.magic << header.msgType;

    // 直接append不会包含长度前缀
    // 将JSON数据追加到数据包的末尾
    packet.append(jsonData);

    qDebug() <<  "正在构建数据包中......";
    qDebug() <<  "头部大小：" << sizeof(ProtocolHeader) << "数据大小：" << header.dataSize;
    // 返回构建好的数据包
    return packet;
}

/**
 * @brief 解析网络数据包
 *
 * 该函数用于解析接收到的原始字节数据，将其拆分为协议头和JSON数据，并存储到Packet结构体中。
 * 在解析过程中，会进行协议头完整性检查、魔数校验和数据完整性校验，确保数据的正确性。
 *
 * @param rawData 接收到的原始字节数据，包含协议头和JSON数据
 * @param outPacket 输出参数，用于存储解析后的协议头和JSON数据
 * @return bool 解析成功返回true，失败返回false
 */
bool ProtocolHandler::parsePacket(const QByteArray& rawData, Packet& outPacket) {
    // 检查原始数据的长度是否足够包含协议头
    if (rawData.size() < static_cast<int>(sizeof(ProtocolHeader))) {
        // 若不足，输出警告信息
        qWarning("协议头不完整，需要至少%zu字节", sizeof(ProtocolHeader));
        // 返回解析失败
        return false;
    }

    // 创建一个QDataStream对象，将其与rawData关联，用于读取数据
    QDataStream stream(rawData);
    // 设置数据流的字节序为小端字节序，与构建数据包时保持一致
    stream.setByteOrder(QDataStream::LittleEndian);

    // 读取协议头
    // 从数据流中按顺序读取协议头的各个字段
    stream >> outPacket.header.dataSize
          >> outPacket.header.magic
          >> outPacket.header.msgType;


//    qDebug() << outPacket.header.dataSize
//            << outPacket.header.magic
//            << outPacket.header.msgType;
    // 魔数校验
    // 检查接收到的魔数是否与预定义的魔数一致
    if (outPacket.header.magic != PROTOCOL_MAGIC) {
        // 若不一致，输出警告信息
        qWarning("协议魔数校验失败（收到：0x%x）", outPacket.header.magic);
        // 返回解析失败
        return false;
    }

    qDebug() <<  "正在解析数据包中......";
    qDebug() << "头部大小：" << sizeof(ProtocolHeader) << "数据大小：" <<outPacket.header.dataSize ;
    // 数据完整性校验
    // 计算完整数据包的预期长度，包括协议头和JSON数据
    const int expectedSize = sizeof(ProtocolHeader) + outPacket.header.dataSize;


    // 检查原始数据的长度是否达到预期长度
    if (rawData.size() < expectedSize) {
        // 若不足，输出警告信息
        qWarning("数据不完整，需要%d字节，收到%d字节",
                expectedSize, rawData.size());
        // 返回解析失败
        return false;
    }

    // 提取JSON数据
    // 从原始数据中提取出JSON数据部分，存储到outPacket的body成员中
    outPacket.body = rawData.mid(sizeof(ProtocolHeader), outPacket.header.dataSize);
    // 返回解析成功
    return true;
}
