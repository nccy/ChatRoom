#include "requesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

void RequestHandler::sendResponse(QTcpSocket* socket, MessageType messageType, const QJsonObject& response) {
    socket->write(ProtocolHandler::buildPacket(
            messageType,
            QJsonDocument(response)
    ));
    socket->flush();
}
