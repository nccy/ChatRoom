// userinfo.h
#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <QDateTime>
#include <QMetaType>

class UserInfo {
public:
    // 认证信息结构体
    struct AuthInfo {
        QString passwordHash;
        QString salt;
    };

    // 默认构造函数
    UserInfo() = default;

    // 带参数的构造函数
    UserInfo(int id, const QString& account, const QString& nickname,
             const QString& phone = "", const QString& avatarUrl = "",
             const QString& declaration = "", const QDateTime& createTime = QDateTime(),
             const QString& avatarBase64 = "");

    // Getter 方法
    int getId() const;
    QString getAccount() const;
    QString getNickname() const;
    QString getPhone() const;
    QString getAvatarUrl() const;
    QString getDeclaration() const;
    QDateTime getCreateTime() const;
    AuthInfo getAuthInfo() const;
    QString getAvatarBase64() const;

    // Setter 方法
    void setId(int id);
    void setAccount(const QString& account);
    void setNickname(const QString& nickname);
    void setPhone(const QString& phone);
    void setAvatarUrl(const QString& avatarUrl);
    void setDeclaration(const QString& declaration);
    void setCreateTime(const QDateTime& createTime);
    void setAuthInfo(const AuthInfo& authInfo);
    void setAvatarBase64(const QString& avatarBase64);

private:
    int m_id;
    QString m_account;
    QString m_nickname;
    QString m_phone;
    QString m_avatarUrl;
    QString m_declaration;
    QDateTime m_createTime;
    AuthInfo m_authInfo;
    QString m_avatarBase64;
};
Q_DECLARE_METATYPE(UserInfo);
#endif // USERINFO_H
