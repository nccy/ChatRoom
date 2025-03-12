#ifndef GROUPAPPLICATION_H
#define GROUPAPPLICATION_H

#include <QDateTime>

class GroupApplication {
public:
    enum Status {
        PENDING = 0,
        APPROVED = 1,
        REJECTED = 2
    };

    GroupApplication(int id = 0, int groupId = 0, int applicantId = 0, Status status = PENDING,
                     const QDateTime& createTime = QDateTime(), const QDateTime& updateTime = QDateTime());

    int getId() const;
    void setId(int id);

    int getGroupId() const;
    void setGroupId(int groupId);

    int getApplicantId() const;
    void setApplicantId(int applicantId);

    Status getStatus() const;
    void setStatus(Status status);

    QDateTime getCreateTime() const;
    void setCreateTime(const QDateTime& createTime);

    QDateTime getUpdateTime() const;
    void setUpdateTime(const QDateTime& updateTime);

private:
    int m_id;
    int m_groupId;
    int m_applicantId;
    Status m_status;
    QDateTime m_createTime;
    QDateTime m_updateTime;
};

#endif // GROUPAPPLICATION_H
