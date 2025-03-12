#include "groupapplication.h"

GroupApplication::GroupApplication(int id, int groupId, int applicantId, Status status,
                                   const QDateTime& createTime, const QDateTime& updateTime)
    : m_id(id), m_groupId(groupId), m_applicantId(applicantId), m_status(status),
      m_createTime(createTime), m_updateTime(updateTime) {}

int GroupApplication::getId() const {
    return m_id;
}

void GroupApplication::setId(int id) {
    m_id = id;
}

int GroupApplication::getGroupId() const {
    return m_groupId;
}

void GroupApplication::setGroupId(int groupId) {
    m_groupId = groupId;
}

int GroupApplication::getApplicantId() const {
    return m_applicantId;
}

void GroupApplication::setApplicantId(int applicantId) {
    m_applicantId = applicantId;
}

GroupApplication::Status GroupApplication::getStatus() const {
    return m_status;
}

void GroupApplication::setStatus(Status status) {
    m_status = status;
}

QDateTime GroupApplication::getCreateTime() const {
    return m_createTime;
}

void GroupApplication::setCreateTime(const QDateTime& createTime) {
    m_createTime = createTime;
}

QDateTime GroupApplication::getUpdateTime() const {
    return m_updateTime;
}

void GroupApplication::setUpdateTime(const QDateTime& updateTime) {
    m_updateTime = updateTime;
}
