#ifndef GROUPMEMBER_H
#define GROUPMEMBER_H

#include <QDateTime>

class GroupMember {
public:
    GroupMember(int id = 0, int groupId = 0, int userId = 0, const QDateTime& joinTime = QDateTime());

    int getId() const;
    void setId(int id);

    int getGroupId() const;
    void setGroupId(int groupId);

    int getUserId() const;
    void setUserId(int userId);

    QDateTime getJoinTime() const;
    void setJoinTime(const QDateTime& joinTime);

private:
    int m_id;
    int m_groupId;
    int m_userId;
    QDateTime m_joinTime;
};

#endif // GROUPMEMBER_H
