#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include "model/userinfo.h"
#include <QMutex>

class ClientController : public QObject
{
    Q_OBJECT
private:
    explicit ClientController(QObject *parent = nullptr); // 私有构造函数
    static QMutex s_mutex;
    static ClientController* s_instance;

public:
    static ClientController* instance();
    QString pixmapToString(const QPixmap pixmap);

signals:
    //登录信号
    void loginResult(bool success, const QString &message, const UserInfo user);

    //注册信号
    void registerResult(bool success, const QString &message, const UserInfo& newUser);

    //忘记密码信号
    void codeVerificationResult(bool success, const QString &message, const QString &phoneNumber);

    //重置密码信号
    void passwordResetResult(bool success, const QString &message,const QString &newPassword);
    // 编辑资料请求结果信号
    void editProfileResult(bool success, const QString &message,const UserInfo &updatedUser);

    // 更新资料请求结果信号
    void updateProfileResult(bool success, const QString &message, const UserInfo &updatedUser);

public slots:
    //登录处理
    void handleLogin(const QString &username, const QString &password);

    void handleRegistration(const QString& nickname,
                            const QString& password,
                            const QString& phone);
    void handleForgotPassword(const QString& phone, const QString& captcha, const QString& curCaptcha);

    void handleResetPassword(const QString& phone, const QString &newPassword, const QString &confirmPassword);

    //编辑
    void editProfileRequested(const QString &account); // 请求编辑资料
    void updateProfileRequest(const QString &nickname, const QString &declaration, const QString &phone, const QPixmap &avatar); // 发送更新请求信号
};

#endif // CLIENTCONTROLLER_H
