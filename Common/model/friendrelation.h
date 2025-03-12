#ifndef FRIENDRELATION_H
#define FRIENDRELATION_H

#include <QDateTime>

class FriendRelation {
public:
    FriendRelation(int id = 0, int userId = 0, int friendId = 0, const QDateTime& addTime = QDateTime());

    int getId() const;
    void setId(int id);

    int getUserId() const;
    void setUserId(int userId);

    int getFriendId() const;
    void setFriendId(int friendId);

    QDateTime getAddTime() const;
    void setAddTime(const QDateTime& addTime);

private:
    int m_id;
    int m_userId;
    int m_friendId;
    QDateTime m_addTime;
};

#endif // FRIENDRELATION_H
