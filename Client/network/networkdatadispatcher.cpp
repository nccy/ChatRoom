#include "networkdatadispatcher.h"
#include "clienthandlerfactory.h"
#include <QDebug>

NetworkDataDispatcher::NetworkDataDispatcher(const QByteArray &rawData)
    : m_rawData(rawData)
{
    setAutoDelete(true); // 任务完成后自动删除
}

void NetworkDataDispatcher::run() {
    ProtocolHandler::Packet packet;
    if (!ProtocolHandler::parsePacket(m_rawData, packet)) return;

    // 根据消息类型创建处理器（工厂模式）
    QScopedPointer<NetworkDataHandler> handler(
        ClientHandlerFactory::createHandler(
            static_cast<MessageType>(packet.header.msgType)
        )
    );

    qDebug() <<"收到消息类型：" <<static_cast<MessageType>(packet.header.msgType);
    if (handler) {
        handler->processResponse(packet.body);
    }
}
