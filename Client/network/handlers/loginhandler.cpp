#include "loginhandler.h"
#include "model/userinfo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "controller/clientcontroller.h"

LoginHandler::LoginHandler(QObject *parent)
    : NetworkDataHandler(parent) // 正确调用基类构造函数
{
    connect(this, &LoginHandler::loginResult,
               ClientController::instance(), &ClientController::loginResult,
               Qt::QueuedConnection);
}

void LoginHandler::processResponse(const QByteArray& response) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(response, &error);

    if (error.error != QJsonParseError::NoError) {
        emit loginResult(false, "协议解析失败", UserInfo());
        return;
    }

    const QJsonObject res = doc.object();
    bool success = res["success"].toBool();
    QString message = res["message"].toString();

    if (success) {
        QJsonObject userObj = res["data"].toObject();
        UserInfo user(
            userObj["id"].toInt(),
            userObj["account"].toString(),
            userObj["nickname"].toString(),
            userObj["phone"].toString(),
            userObj["avatarUrl"].toString(),
            userObj["declaration"].toString()
        );
        user.setAvatarBase64(userObj["avatar"].toString());
        emit loginResult(true, message, user);
    } else {
        emit loginResult(false, message, UserInfo());
    }
}
