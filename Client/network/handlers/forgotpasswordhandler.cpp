#include "forgotpasswordhandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "controller/clientcontroller.h"

ForgotPasswordHandler::ForgotPasswordHandler(QObject *parent)
    : NetworkDataHandler(parent)
{
    // 将信号连接到 ClientController 的槽，使用队列连接确保线程安全
    connect(this, &ForgotPasswordHandler::codeVerificationResult,
            ClientController::instance(), &ClientController::codeVerificationResult,
            Qt::QueuedConnection);
}

void ForgotPasswordHandler::processResponse(const QByteArray &response)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(response, &error);

    // 协议解析失败处理
    if (error.error != QJsonParseError::NoError) {
        emit codeVerificationResult(false, "协议解析失败", "");
        return;
    }

    const QJsonObject res = doc.object();
    const bool success = res["success"].toBool();
    const QString message = res["message"].toString();
    QString phoneNumber;

    // 从 data 字段提取手机号（根据服务端实际响应结构调整）
    if (res.contains("data")) {
        const QJsonObject data = res["data"].toObject();
        phoneNumber = data["phone"].toString();
    }

    // 发送验证结果信号
    emit codeVerificationResult(success, message, phoneNumber);
}
