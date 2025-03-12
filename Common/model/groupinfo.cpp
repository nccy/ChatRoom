#include "groupinfo.h"

GroupInfo::GroupInfo(int id, const QString& groupNumber, const QString& groupName,
                     const QString& groupAvatarUrl, int creatorId,
                     const QDateTime& createTime, const QString& introduction,
                     const QString& notice, const QString& groupAvatarBase64)
    : m_id(id), m_groupNumber(groupNumber), m_groupName(groupName),
      m_groupAvatarUrl(groupAvatarUrl), m_creatorId(creatorId),
      m_createTime(createTime), m_introduction(introduction),
      m_notice(notice), m_groupAvatarBase64(groupAvatarBase64) {}

int GroupInfo::getId() const {
    return m_id;
}

void GroupInfo::setId(int id) {
    m_id = id;
}

QString GroupInfo::getGroupNumber() const {
    return m_groupNumber;
}

void GroupInfo::setGroupNumber(const QString& groupNumber) {
    m_groupNumber = groupNumber;
}

QString GroupInfo::getGroupName() const {
    return m_groupName;
}

void GroupInfo::setGroupName(const QString& groupName) {
    m_groupName = groupName;
}

QString GroupInfo::getGroupAvatarUrl() const {
    return m_groupAvatarUrl;
}

void GroupInfo::setGroupAvatarUrl(const QString& groupAvatarUrl) {
    m_groupAvatarUrl = groupAvatarUrl;
}

int GroupInfo::getCreatorId() const {
    return m_creatorId;
}

void GroupInfo::setCreatorId(int creatorId) {
    m_creatorId = creatorId;
}

QDateTime GroupInfo::getCreateTime() const {
    return m_createTime;
}

void GroupInfo::setCreateTime(const QDateTime& createTime) {
    m_createTime = createTime;
}

QString GroupInfo::getIntroduction() const {
    return m_introduction;
}

void GroupInfo::setIntroduction(const QString& introduction) {
    m_introduction = introduction;
}

QString GroupInfo::getNotice() const {
    return m_notice;
}

void GroupInfo::setNotice(const QString& notice) {
    m_notice = notice;
}

QString GroupInfo::getGroupAvatarBase64() const {
    return m_groupAvatarBase64;
}

void GroupInfo::setGroupAvatarBase64(const QString& groupAvatarBase64) {
    m_groupAvatarBase64 = groupAvatarBase64;
}
