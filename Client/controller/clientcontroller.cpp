#include "clientcontroller.h"
#include "../Client/network/tcpclient.h"
#include "protocol/protocolhandler.h"
#include <QJsonObject>
#include <QRegularExpression>
#include <QBuffer>
#include <QImage>
#include <QImageWriter>
#include <QPixmap>

ClientController::ClientController(QObject *parent)
    : QObject(parent)
{
}

QMutex ClientController::s_mutex;
ClientController* ClientController::s_instance = nullptr;

ClientController* ClientController::instance() {
    if (!s_instance) {
        QMutexLocker lock(&s_mutex);
        if (!s_instance) {
            s_instance = new ClientController();
        }
    }
    return s_instance;
}

void ClientController::handleLogin(const QString &account, const QString &password)
{
    if (account.isEmpty() || password.isEmpty()) {
        emit loginResult(false, "账号或密码不能为空", UserInfo());
        return;
    }

    QJsonObject data{
        {"account", account},
        {"password", password}
    };

    TcpClient::instance()->sendPacket(MessageType::LOGIN_REQ, QJsonDocument(data));
}

void ClientController::handleRegistration(const QString& nickname,
                                        const QString& password,
                                        const QString& phone)
{
    if (nickname.isEmpty() || password.isEmpty() || phone.isEmpty()) {
        emit registerResult(false, "昵称、密码或手机号不能为空", UserInfo());
        return;
    }

    // 密码强度校验
    if (password.length() < 8) {
        emit registerResult(false, "密码长度不能小于8位", UserInfo());
        return;
    }

    // 手机号验证，确保是 11 位数字
    QRegularExpression phoneRegex("^\\d{11}$");
    if (!phoneRegex.match(phone).hasMatch()) {
        emit registerResult(false, "手机号必须为 11 位数字", UserInfo());
        return;
    }

    QJsonObject data{
        {"nickname", nickname},
        {"password", password},
        {"phone", phone}
    };

    TcpClient::instance()->sendPacket(MessageType::REGISTER_REQ, QJsonDocument(data));
}

void ClientController::handleForgotPassword(const QString& phone, const QString& captcha, const QString& curCaptcha)
{
    // 基础验证
    if (phone.isEmpty() || captcha.isEmpty()) {
        emit codeVerificationResult(false, "手机号和验证码不能为空", "");
        return;
    }

    // 手机号格式验证
    QRegularExpression phoneRegex("^\\d{11}$");
    if (!phoneRegex.match(phone).hasMatch()) {
        emit codeVerificationResult(false, "手机号格式不正确", phone);
        return;
    }

    // 验证码格式验证（假设是4位数字）
    QRegularExpression captchaRegex("^[0-9a-zA-Z]{4}$");
    if (!captchaRegex.match(captcha).hasMatch()) {
        emit codeVerificationResult(false, "验证码必须为4位数字", phone);
        return;
    }

    // 判断验证码和当前验证码是否一致
    if (captcha != curCaptcha) {
        emit codeVerificationResult(false, "验证码输入错误", phone);
        return;
    }

    QJsonObject data{
        {"phone", phone},
        {"captcha", captcha}
    };

    TcpClient::instance()->sendPacket(MessageType::FORGOT_PWD_REQ, QJsonDocument(data));
}

void ClientController::handleResetPassword(const QString& phone, const QString &newPassword, const QString &confirmPassword)
{
    // 密码为空校验
    if (newPassword.isEmpty() || confirmPassword.isEmpty()) {
        emit passwordResetResult(false, "新密码和确认密码不能为空", "");
        return;
    }
    // 密码强度校验
    if (newPassword.length() < 8) {
        emit registerResult(false, "密码长度不能小于8位", UserInfo());
        return;
    }
    // 密码一致性验证
    if (newPassword != confirmPassword) {
        emit passwordResetResult(false, "两次输入的密码不一致", "");
        return;
    }


    QJsonObject data{
        {"new_password", newPassword},
        {"phone", phone}
    };

    TcpClient::instance()->sendPacket(MessageType::PWD_RESET_REQ, QJsonDocument(data));
}

void ClientController::editProfileRequested(const QString &account)
{
    // 这里可以添加更多逻辑，比如检查是否已经登录等
    QJsonObject data;
    data["account"] = account;
    TcpClient::instance()->sendPacket(MessageType::EDIT_PROFILE_REQ, QJsonDocument(data));
}

void ClientController::updateProfileRequest(const QString &nickname, const QString &declaration, const QString &phone, const QPixmap &avatar)
{
    // 昵称、手机号为空校验
    if (nickname.isEmpty() || phone.isEmpty()) {
        emit updateProfileResult(false, "昵称和手机号不能为空", UserInfo());
        return;
    }
    // 手机号格式校验
    QRegularExpression phoneRegex("^d{11}$");
    if (!phoneRegex.match(phone).hasMatch()) {
        emit updateProfileResult(false, "手机号格式不正确", UserInfo());
        return;
    }

    QString avatarBase64 = pixmapToString(avatar);

    QJsonObject data{
        {"nickname", nickname},
        {"declaration", declaration},
        {"phone", phone},
        {"avatar", avatarBase64}
    };

    TcpClient::instance()->sendPacket(MessageType::UPDATE_PROFILE_REQ, QJsonDocument(data));
}

QString ClientController::pixmapToString(QPixmap pixmap) {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    QImage image = pixmap.toImage();
    QImageWriter writer(&buffer, "PNG");
    writer.write(image);
    buffer.close();
    return QString::fromLatin1(byteArray.toBase64().data());
}
