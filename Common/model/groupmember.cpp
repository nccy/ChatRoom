#include "groupmember.h"

GroupMember::GroupMember(int id, int groupId, int userId, const QDateTime& joinTime)
    : m_id(id), m_groupId(groupId), m_userId(userId), m_joinTime(joinTime) {}

int GroupMember::getId() const {
    return m_id;
}

void GroupMember::setId(int id) {
    m_id = id;
}

int GroupMember::getGroupId() const {
    return m_groupId;
}

void GroupMember::setGroupId(int groupId) {
    m_groupId = groupId;
}

int GroupMember::getUserId() const {
    return m_userId;
}

void GroupMember::setUserId(int userId) {
    m_userId = userId;
}

QDateTime GroupMember::getJoinTime() const {
    return m_joinTime;
}

void GroupMember::setJoinTime(const QDateTime& joinTime) {
    m_joinTime = joinTime;
}
