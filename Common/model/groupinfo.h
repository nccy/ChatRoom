#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QString>
#include <QDateTime>

class GroupInfo {
public:
    GroupInfo(int id = 0, const QString& groupNumber = "", const QString& groupName = "",
              const QString& groupAvatarUrl = "", int creatorId = 0,
              const QDateTime& createTime = QDateTime(), const QString& introduction = "",
              const QString& notice = "", const QString& groupAvatarBase64 = "");

    int getId() const;
    void setId(int id);

    QString getGroupNumber() const;
    void setGroupNumber(const QString& groupNumber);

    QString getGroupName() const;
    void setGroupName(const QString& groupName);

    QString getGroupAvatarUrl() const;
    void setGroupAvatarUrl(const QString& groupAvatarUrl);

    int getCreatorId() const;
    void setCreatorId(int creatorId);

    QDateTime getCreateTime() const;
    void setCreateTime(const QDateTime& createTime);

    QString getIntroduction() const;
    void setIntroduction(const QString& introduction);

    QString getNotice() const;
    void setNotice(const QString& notice);

    QString getGroupAvatarBase64() const;
    void setGroupAvatarBase64(const QString& groupAvatarBase64);

private:
    int m_id;
    QString m_groupNumber;
    QString m_groupName;
    QString m_groupAvatarUrl;
    int m_creatorId;
    QDateTime m_createTime;
    QString m_introduction;
    QString m_notice;
    QString m_groupAvatarBase64;
};

#endif // GROUPINFO_H
