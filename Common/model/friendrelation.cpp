#include "friendrelation.h"

FriendRelation::FriendRelation(int id, int userId, int friendId, const QDateTime& addTime)
    : m_id(id), m_userId(userId), m_friendId(friendId), m_addTime(addTime) {}

int FriendRelation::getId() const {
    return m_id;
}

void FriendRelation::setId(int id) {
    m_id = id;
}

int FriendRelation::getUserId() const {
    return m_userId;
}

void FriendRelation::setUserId(int userId) {
    m_userId = userId;
}

int FriendRelation::getFriendId() const {
    return m_friendId;
}

void FriendRelation::setFriendId(int friendId) {
    m_friendId = friendId;
}

QDateTime FriendRelation::getAddTime() const {
    return m_addTime;
}

void FriendRelation::setAddTime(const QDateTime& addTime) {
    m_addTime = addTime;
}
