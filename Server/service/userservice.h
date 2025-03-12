#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "model/userinfo.h"

class UserService {
public:
    /**
     * @brief 用户认证服务
     * @param account 账号
     * @param password 明文密码
     * @return 认证结果
     */
    static bool authenticate(const QString& account,
                                     const QString& password,
                                     UserInfo& outUser);
    /**
     * @brief 用户注册服务
     * @param nickname 用户昵称
     * @param password 明文密码
     * @param phone 用户手机号
     * @return 注册结果
     */
    static bool registerUser(const QString& nickname,
                             const QString& password,
                             const QString& phone,
                             UserInfo& outUser);


    static bool verifyPhoneAndCode(const QString& phone, const QString& code);

    static bool resetPasswordByPhone(const QString& phone,
                                        const QString& newPassword);
    static bool getUserByAccount(const QString& account, UserInfo& outUser);

};

#endif // USERSERVICE_H
