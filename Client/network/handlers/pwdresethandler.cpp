// pwdresethandler.cpp
#include "pwdresethandler.h"
#include "model/userinfo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "controller/clientcontroller.h"

PwdResetHandler::PwdResetHandler(QObject *parent)
    : NetworkDataHandler(parent)
{
    // 连接信号到控制器
    connect(this, &PwdResetHandler::pwdResetResult,
           ClientController::instance(), &ClientController::passwordResetResult,
           Qt::QueuedConnection);
}

void PwdResetHandler::processResponse(const QByteArray& response) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(response, &error);

    if (error.error != QJsonParseError::NoError) {
        // 因为无法从解析失败的响应中获取新密码，所以传递空字符串
        emit pwdResetResult(false, "协议解析失败", "");
        return;
    }

    const QJsonObject res = doc.object();
    bool success = res["success"].toBool();
    QString message = res["message"].toString();
    QString newPassword;
    UserInfo user;
    if (success) {
        QJsonObject Data = res["data"].toObject();
        // 构建用户对象（根据实际返回字段）
         newPassword= Data["new_password"].toString();
    }

    emit pwdResetResult(success, message,  newPassword);
}
