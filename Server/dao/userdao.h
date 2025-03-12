#ifndef USERDAO_H
#define USERDAO_H

#include "model/userinfo.h"
#include <QSqlDatabase>

class UserDAO {
public:
    /**
     * @brief 根据账号查询用户信息
     * @param account 用户账号
     * @param db 数据库连接
     * @return 包含完整用户信息的对象，id为-1表示未找到
     */
    static UserInfo getUserByAccount(const QString& account, QSqlDatabase& db);


    // 根据手机号获取用户信息（新增）
    static UserInfo getUserByPhone(const QString& phone, QSqlDatabase& db);

    /**
     * @brief 插入新用户信息，成功返回true，失败返回false
     * 插入成功后，user对象的id会被设置为新插入记录的ID
     */
    static bool addUser(UserInfo &user, QSqlDatabase& db);

    /**
     * @brief 更新用户信息（根据用户ID），成功返回true，失败返回false
     */
    static bool updateUser(const UserInfo &user, QSqlDatabase& db);

    static bool updateAuthInfo(const QString& account,
                                        const QString& newHash,
                                        const QString& newSalt,
                                        QSqlDatabase& db);
};

#endif // USERDAO_H
