// userinfo.cpp
#include "userinfo.h"

UserInfo::UserInfo(int id, const QString& account, const QString& nickname,
                   const QString& phone, const QString& avatarUrl,
                   const QString& declaration, const QDateTime& createTime,
                   const QString& avatarBase64)
    : m_id(id), m_account(account), m_nickname(nickname), m_phone(phone),
      m_avatarUrl(avatarUrl), m_declaration(declaration), m_createTime(createTime),
      m_avatarBase64(avatarBase64) {}

int UserInfo::getId() const {
    return m_id;
}

QString UserInfo::getAccount() const {
    return m_account;
}

QString UserInfo::getNickname() const {
    return m_nickname;
}

QString UserInfo::getPhone() const {
    return m_phone;
}

QString UserInfo::getAvatarUrl() const {
    return m_avatarUrl;
}

QString UserInfo::getDeclaration() const {
    return m_declaration;
}

QDateTime UserInfo::getCreateTime() const {
    return m_createTime;
}

UserInfo::AuthInfo UserInfo::getAuthInfo() const {
    return m_authInfo;
}

QString UserInfo::getAvatarBase64() const {
    return m_avatarBase64;
}

void UserInfo::setId(int id) {
    m_id = id;
}

void UserInfo::setAccount(const QString& account) {
    m_account = account;
}

void UserInfo::setNickname(const QString& nickname) {
    m_nickname = nickname;
}

void UserInfo::setPhone(const QString& phone) {
    m_phone = phone;
}

void UserInfo::setAvatarUrl(const QString& avatarUrl) {
    m_avatarUrl = avatarUrl;
}

void UserInfo::setDeclaration(const QString& declaration) {
    m_declaration = declaration;
}

void UserInfo::setCreateTime(const QDateTime& createTime) {
    m_createTime = createTime;
}

void UserInfo::setAuthInfo(const AuthInfo& authInfo) {
    m_authInfo = authInfo;
}

void UserInfo::setAvatarBase64(const QString& avatarBase64) {
    m_avatarBase64 = avatarBase64;
}
