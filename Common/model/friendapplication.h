#ifndef FRIENDAPPLICATION_H
#define FRIENDAPPLICATION_H

#include <QDateTime>

class FriendApplication {
public:
    enum Status {
        PENDING = 0,
        APPROVED = 1,
        REJECTED = 2
    };

    FriendApplication(int id = 0, int senderId = 0, int receiverId = 0, Status status = PENDING,
                      const QDateTime& createTime = QDateTime(), const QDateTime& updateTime = QDateTime());

    int getId() const;
    void setId(int id);

    int getSenderId() const;
    void setSenderId(int senderId);

    int getReceiverId() const;
    void setReceiverId(int receiverId);

    Status getStatus() const;
    void setStatus(Status status);

    QDateTime getCreateTime() const;
    void setCreateTime(const QDateTime& createTime);

    QDateTime getUpdateTime() const;
    void setUpdateTime(const QDateTime& updateTime);

private:
    int m_id;
    int m_senderId;
    int m_receiverId;
    Status m_status;
    QDateTime m_createTime;
    QDateTime m_updateTime;
};

#endif // FRIENDAPPLICATION_H
