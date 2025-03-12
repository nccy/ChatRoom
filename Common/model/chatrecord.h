#ifndef CHATRECORD_H
#define CHATRECORD_H

#include <QString>
#include <QDateTime>

class ChatRecord {
public:
    enum ReceiverType {
        USER = 0,
        GROUP = 1
    };

    enum MessageType {
        TEXT = 1,
        IMAGE = 2,
        FILE = 3
    };

    ChatRecord(int id = 0, int senderId = 0, int receiverId = 0, ReceiverType receiverType = USER,
               MessageType messageType = TEXT, const QString& messageContent = "",
               const QDateTime& timestamp = QDateTime(), int version = 1);

    int getId() const;
    void setId(int id);

    int getSenderId() const;
    void setSenderId(int senderId);

    int getReceiverId() const;
    void setReceiverId(int receiverId);

    ReceiverType getReceiverType() const;
    void setReceiverType(ReceiverType receiverType);

    MessageType getMessageType() const;
    void setMessageType(MessageType messageType);

    QString getMessageContent() const;
    void setMessageContent(const QString& messageContent);

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime& timestamp);

    int getVersion() const;
    void setVersion(int version);

private:
    int m_id;
    int m_senderId;
    int m_receiverId;
    ReceiverType m_receiverType;
    MessageType m_messageType;
    QString m_messageContent;
    QDateTime m_timestamp;
    int m_version;
};

#endif // CHATRECORD_H
