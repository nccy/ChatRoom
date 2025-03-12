#include "chatrecord.h"

ChatRecord::ChatRecord(int id, int senderId, int receiverId, ReceiverType receiverType,
                       MessageType messageType, const QString& messageContent,
                       const QDateTime& timestamp, int version)
    : m_id(id), m_senderId(senderId), m_receiverId(receiverId), m_receiverType(receiverType),
      m_messageType(messageType), m_messageContent(messageContent), m_timestamp(timestamp), m_version(version) {}

int ChatRecord::getId() const {
    return m_id;
}

void ChatRecord::setId(int id) {
    m_id = id;
}

int ChatRecord::getSenderId() const {
    return m_senderId;
}

void ChatRecord::setSenderId(int senderId) {
    m_senderId = senderId;
}

int ChatRecord::getReceiverId() const {
    return m_receiverId;
}

void ChatRecord::setReceiverId(int receiverId) {
    m_receiverId = receiverId;
}

ChatRecord::ReceiverType ChatRecord::getReceiverType() const {
    return m_receiverType;
}

void ChatRecord::setReceiverType(ReceiverType receiverType) {
    m_receiverType = receiverType;
}

ChatRecord::MessageType ChatRecord::getMessageType() const {
    return m_messageType;
}

void ChatRecord::setMessageType(MessageType messageType) {
    m_messageType = messageType;
}

QString ChatRecord::getMessageContent() const {
    return m_messageContent;
}

void ChatRecord::setMessageContent(const QString& messageContent) {
    m_messageContent = messageContent;
}

QDateTime ChatRecord::getTimestamp() const {
    return m_timestamp;
}

void ChatRecord::setTimestamp(const QDateTime& timestamp) {
    m_timestamp = timestamp;
}

int ChatRecord::getVersion() const {
    return m_version;
}

void ChatRecord::setVersion(int version) {
    m_version = version;
}
