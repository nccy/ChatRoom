// editprofilehandler.cpp
#include "editprofilehandler.h"
#include "controller/clientcontroller.h"
#include <QJsonDocument>
#include <QJsonObject>

EditProfileHandler::EditProfileHandler(QObject *parent)
    : NetworkDataHandler(parent)
{
    // 连接信号到控制器
    connect(this, &EditProfileHandler::editProfileResult,
            ClientController::instance(), &ClientController::editProfileResult,
            Qt::QueuedConnection);
}

void EditProfileHandler::processResponse(const QByteArray& response)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(response, &error);

    // 协议解析失败处理
    if (error.error != QJsonParseError::NoError) {
        emit editProfileResult(false, "资料更新协议解析失败", UserInfo());
        return;
    }

    const QJsonObject res = doc.object();
    const bool success = res["success"].toBool();
    const QString message = res["message"].toString();

    if (success) {
        // 解析更新后的用户数据
        const QJsonObject userObj = res["data"].toObject();
        UserInfo updatedUser(
            userObj["id"].toInt(),
            userObj["account"].toString(),
            userObj["nickname"].toString(),
            userObj["phone"].toString(),
            userObj["avatarUrl"].toString(),
            userObj["declaration"].toString()
        );

        // 设置头像Base64数据（如果有返回）
        if(userObj.contains("avatar")){
            updatedUser.setAvatarBase64(userObj["avatar"].toString());
        }

        emit editProfileResult(true, message, updatedUser);
    } else {
        emit editProfileResult(false, message, UserInfo());
    }
}
