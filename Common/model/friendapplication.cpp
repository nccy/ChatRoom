#include "friendapplication.h"

FriendApplication::FriendApplication(int id, int senderId, int receiverId, Status status,
                                     const QDateTime& createTime, const QDateTime& updateTime)
    : m_id(id), m_senderId(senderId), m_receiverId(receiverId), m_status(status),
      m_createTime(createTime), m_updateTime(updateTime) {}

int FriendApplication::getId() const {
    return m_id;
}

void FriendApplication::setId(int id) {
    m_id = id;
}

int FriendApplication::getSenderId() const {
    return m_senderId;
}

void FriendApplication::setSenderId(int senderId) {
    m_senderId = senderId;
}

int FriendApplication::getReceiverId() const {
    return m_receiverId;
}

void FriendApplication::setReceiverId(int receiverId) {
    m_receiverId = receiverId;
}

FriendApplication::Status FriendApplication::getStatus() const {
    return m_status;
}

void FriendApplication::setStatus(Status status) {
    m_status = status;
}

QDateTime FriendApplication::getCreateTime() const {
    return m_createTime;
}

void FriendApplication::setCreateTime(const QDateTime& createTime) {
    m_createTime = createTime;
}

QDateTime FriendApplication::getUpdateTime() const {
    return m_updateTime;
}

void FriendApplication::setUpdateTime(const QDateTime& updateTime) {
    m_updateTime = updateTime;
}
