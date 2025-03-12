#include "userservice.h"
#include "../dao/userdao.h"
#include "../database/dbconnectionpool.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QRandomGenerator>

bool UserService::authenticate(const QString& account,
                                       const QString& password,
                                       UserInfo& outUser) {
    // 获取数据库连接
    QSqlDatabase db = DBConnectionPool::getInstance()->getConnection();
    if (!db.isValid()) {
        qCritical() << "无法获取数据库连接";
        return false;
    }

    // 查询用户完整信息
    UserInfo user = UserDAO::getUserByAccount(account, db);
    DBConnectionPool::getInstance()->releaseConnection(db); // 确保连接释放

    // 用户不存在
    if (user.getId() == -1) {
        qInfo() << "账号不存在:" << account;
        return false;
    }

    // 密码验证
    auto authInfo = user.getAuthInfo();
    QByteArray saltedPassword = (password + authInfo.salt).toUtf8();
    QString calculatedHash = QCryptographicHash::hash(saltedPassword,
        QCryptographicHash::Sha256).toHex();

    // 认证成功时返回用户数据
    if (calculatedHash == authInfo.passwordHash) {
        outUser = user; // 通过引用返回完整用户对象
        return true;
    }

    // 密码不匹配
    qInfo() << "密码验证失败，账号:" << account;
    return false;
}

bool UserService::registerUser(const QString& nickname, const QString& password, const QString& phone, UserInfo& outUser) {
    // 获取数据库连接
    QSqlDatabase db = DBConnectionPool::getInstance()->getConnection();
    if (!db.isValid()) {
        qCritical() << "无法获取数据库连接";
        return false;
    }

    // 生成盐值
    QString salt = QString::number(QRandomGenerator::global()->generate());

    // 计算密码哈希值
    QByteArray saltedPassword = (password + salt).toUtf8();
    QString passwordHash = QCryptographicHash::hash(saltedPassword, QCryptographicHash::Sha256).toHex();

    // 生成账号（这里简单使用手机号作为账号，可根据实际情况修改）
    QString account = phone;

    // 创建User对象
    UserInfo user;
    user.setAccount(account);
    user.setNickname(nickname);
    user.setPhone(phone);
    user.setAvatarUrl(":/image/default.png");
    user.setAuthInfo({passwordHash, salt});

    // 调用UserDAO::addUser函数插入用户信息
    bool success = UserDAO::addUser(user, db);

    // 释放数据库连接
    DBConnectionPool::getInstance()->releaseConnection(db);

    if (success) {
        // 注册成功时，通过引用返回完整用户对象
        outUser = user;
    }

    return success;
}

bool UserService::verifyPhoneAndCode(const QString& phone, const QString& code) {
    // 获取数据库连接
    QSqlDatabase db = DBConnectionPool::getInstance()->getConnection();
    if (!db.isValid()) {
        qCritical() << "无法获取数据库连接 | 手机号:" << phone;
        return false;
    }
     qDebug() << "验证码为：" <<code;

    // 检查手机号是否注册
    UserInfo user = UserDAO::getUserByPhone(phone, db);

    // 释放数据库连接
    DBConnectionPool::getInstance()->releaseConnection(db);

    if (user.getId() == 0 || user.getAccount().isEmpty()) {
        // 用户对象为空
        qDebug() << "未找到该手机号对应的用户";
        return false;
    } else {
        // 用户对象不为空
        qDebug() << "找到了该手机号对应的用户";
    }
    return true;
}

bool UserService::resetPasswordByPhone(const QString& phone,
                                      const QString& newPassword) {
    // 获取数据库连接
    QSqlDatabase db = DBConnectionPool::getInstance()->getConnection();
    if (!db.isValid()) {
        qCritical() << "[密码重置] 数据库连接失败";
        return false;
    }

    // 查询用户信息
    UserInfo user = UserDAO::getUserByPhone(phone, db);
    if (user.getId() == -1) {
        DBConnectionPool::getInstance()->releaseConnection(db);
        qInfo() << "[密码重置] 手机号未注册:" << phone;
        return false;
    }

    // 生成新盐（与注册时相同的逻辑）
    const QString newSalt = QString::number(QRandomGenerator::global()->generate());

    // 计算新密码哈希
    QByteArray saltedPassword = (newPassword + newSalt).toUtf8();
    QString newHash = QCryptographicHash::hash(saltedPassword,
        QCryptographicHash::Sha256).toHex();

    // 更新数据库
    bool success = UserDAO::updateAuthInfo(user.getAccount(), newHash, newSalt, db);
    DBConnectionPool::getInstance()->releaseConnection(db);

    if (!success) {
        qWarning() << "[密码重置] 数据库更新失败，账号:"
                  << user.getAccount();
        return false;
    }

    qInfo() << "[密码重置] 成功，账号:" << user.getAccount();
    return true;
}

bool UserService::getUserByAccount(const QString& account, UserInfo& outUser) {
        // 获取数据库连接
        QSqlDatabase db = DBConnectionPool::getInstance()->getConnection();
        if (!db.isValid()) {
            qCritical() << "[获取用户信息] 数据库连接失败";
            return false;
        }

        // 查询用户信息
        UserInfo user = UserDAO::getUserByAccount(account, db);
        if (user.getId() == -1) {
            qInfo() << "[获取用户信息] 账号未注册:" << account;
        }

        // 释放数据库连接
        DBConnectionPool::getInstance()->releaseConnection(db);

        outUser=user;
        return true;
}
