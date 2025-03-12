// pwdresethandler.cpp
#include "pwdresethandler.h"
#include "../../service/userservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

void PwdResetHandler::process(const ProtocolHandler::Packet& packet,
                             QTcpSocket* socket) {
    QJsonObject response;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(packet.body, &error);

    // 协议解析失败
    if (error.error != QJsonParseError::NoError) {
        response["success"] = false;
        response["message"] = "协议格式错误";
        sendResponse(socket, MessageType::PWD_RESET_RES, response);
        return;
    }

    QJsonObject req = doc.object();
    QString phone = req["phone"].toString().trimmed();
    QString newPassword = req["new_password"].toString();

    // 字段完整性验证
    if (phone.isEmpty() || newPassword.isEmpty()) {
        response["success"] = false;
        response["message"] = "手机号和新密码必须填写";
        sendResponse(socket, MessageType::PWD_RESET_RES, response);
        return;
    }

    // 执行密码重置操作，这里假设UserService有根据手机号重置密码的方法，方法名为resetPasswordByPhone
    bool resetResult = UserService::resetPasswordByPhone(phone, newPassword);

    response["success"] = resetResult;
    if (resetResult) {
        response["message"] = "密码重置成功";
        // 构建用户数据对象
        QJsonObject Data;
        Data["new_password"] = newPassword;
        response["data"] = Data;
    } else {
        response["message"] = "密码重置失败，请稍后重试";
    }

    sendResponse(socket, MessageType::PWD_RESET_RES, response);
}
