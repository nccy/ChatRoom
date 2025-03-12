#include "userdao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

UserInfo UserDAO::getUserByAccount(const QString& account, QSqlDatabase& db) {
    UserInfo user;

    QSqlQuery query(db);
    query.prepare(
        "SELECT "
        "  id, account, nickname, phone, avatar_url, declaration, "
        "  password_hash, salt, create_time "
        "FROM user_info "
        "WHERE account = :account"
    );
    query.bindValue(":account", account);

    if (query.exec() && query.next()) {
        user = UserInfo(
            query.value("id").toInt(),
            query.value("account").toString(),
            query.value("nickname").toString(),
            query.value("phone").toString(),
            query.value("avatar_url").toString(),
            query.value("declaration").toString(),
            query.value("create_time").toDateTime()
        );

        UserInfo::AuthInfo authInfo;
        authInfo.passwordHash = query.value("password_hash").toString();
        authInfo.salt = query.value("salt").toString();
        user.setAuthInfo(authInfo);
    }

    if (query.lastError().isValid()) {
        qCritical() << "[getUserByAccount] 数据库错误:"
                    << query.lastError().text()
                    << "| 账号:" << account;
    }

    return user;
}

UserInfo UserDAO::getUserByPhone(const QString& phone, QSqlDatabase& db) {
    UserInfo user;

    QSqlQuery query(db);
    query.prepare(
        "SELECT "
        "  id, account, nickname, phone, avatar_url, declaration, "
        "  password_hash, salt, create_time "
        "FROM user_info "
        "WHERE phone = :phone"
    );
    query.bindValue(":phone", phone);

    if (query.exec() && query.next()) {
        user = UserInfo(
            query.value("id").toInt(),
            query.value("account").toString(),
            query.value("nickname").toString(),
            query.value("phone").toString(),
            query.value("avatar_url").toString(),
            query.value("declaration").toString(),
            query.value("create_time").toDateTime()
        );

        UserInfo::AuthInfo authInfo;
        authInfo.passwordHash = query.value("password_hash").toString();
        authInfo.salt = query.value("salt").toString();
        user.setAuthInfo(authInfo);
    }

    if (query.lastError().isValid()) {
        qCritical() << "[getUserByPhone] 数据库错误:"
                    << query.lastError().text()
                    << "| 手机号:" << phone;
    }

    return user;
}

bool UserDAO::addUser(UserInfo &user, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO user_info ("
        "  account, nickname, password_hash, salt, "
        "  phone, avatar_url, declaration"
        ") VALUES ("
        "  :account, :nickname, :password_hash, :salt, "
        "  :phone, :avatar_url, :declaration"
        ")"
    );

    // 绑定必须字段
    query.bindValue(":account", user.getAccount());
    query.bindValue(":nickname", user.getNickname());
    query.bindValue(":password_hash", user.getAuthInfo().passwordHash);
    query.bindValue(":salt", user.getAuthInfo().salt);

    // 处理可选字段
    query.bindValue(":phone",
        user.getPhone().isEmpty() ? QVariant() : user.getPhone());
    query.bindValue(":avatar_url",
        user.getAvatarUrl().isEmpty() ? QVariant() : user.getAvatarUrl());
    query.bindValue(":declaration",
        user.getDeclaration().isEmpty() ? QVariant() : user.getDeclaration());

    if (!query.exec()) {
        qCritical() << "[addUser] 插入失败:" << query.lastError().text();
        return false;
    }

    // 设置自增ID
    user.setId(query.lastInsertId().toInt());
    return true;
}

bool UserDAO::updateUser(const UserInfo &user, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare(
        "UPDATE user_info SET "
        "  nickname = :nickname, "
        "  phone = :phone, "
        "  avatar_url = :avatar_url, "
        "  declaration = :declaration "
        "WHERE id = :id"
    );

    query.bindValue(":nickname", user.getNickname());
    query.bindValue(":phone",
        user.getPhone().isEmpty() ? QVariant() : user.getPhone());
    query.bindValue(":avatar_url",
        user.getAvatarUrl().isEmpty() ? QVariant() : user.getAvatarUrl());
    query.bindValue(":declaration",
        user.getDeclaration().isEmpty() ? QVariant() : user.getDeclaration());
    query.bindValue(":id", user.getId());

    if (!query.exec()) {
        qCritical() << "[updateUser] 更新失败:" << query.lastError().text();
        return false;
    }

    // 验证实际更新行数
    return query.numRowsAffected() > 0;
}

bool UserDAO::updateAuthInfo(const QString& account,
                           const QString& newHash,
                           const QString& newSalt,
                           QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare(
        "UPDATE user_info SET "
        "  password_hash = :password_hash, "
        "  salt = :salt "
        "WHERE account = :account"
    );

    query.bindValue(":password_hash", newHash);
    query.bindValue(":salt", newSalt);
    query.bindValue(":account", account);

    if (!query.exec()) {
        qCritical() << "[updateAuthInfo] 更新失败:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}
