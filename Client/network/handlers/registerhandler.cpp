#include "registerhandler.h"
#include "model/userinfo.h"
#include <QJsonDocument>
#include <QJsonObject>

RegisterHandler::RegisterHandler(QObject *parent)
    : NetworkDataHandler(parent) // 正确调用基类构造函数
{
    // 统一信号连接方式
        connect(this, &RegisterHandler::registerResult,
               ClientController::instance(), &ClientController::registerResult,
               Qt::QueuedConnection);
}

void RegisterHandler::processResponse(const QByteArray& response) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(response, &error);

    if (error.error != QJsonParseError::NoError) {
        emit operationComplete(false, tr("协议解析失败"));
        return;
    }

    const QJsonObject res = doc.object();
    bool success = res["success"].toBool();
    QString message = res["message"].toString();

    if (success) {
        QJsonObject userObj = res["data"].toObject(); // 统一数据字段
        UserInfo user(
            userObj["id"].toInt(),
            userObj["account"].toString(),
            userObj["nickname"].toString(),
            userObj["phone"].toString(),
            userObj["avatarUrl"].toString(),
            userObj["declaration"].toString()
        );
        emit registerResult(true, message, user);
    } else {
        emit registerResult(false, message, UserInfo());
    }
}
