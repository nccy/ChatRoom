#include "forgotpasswordhandler.h"
#include "../../service/userservice.h"
#include <QJsonDocument>
#include <QJsonObject>

void ForgotPasswordHandler::process(const ProtocolHandler::Packet& packet,
                                   QTcpSocket* socket) {
    QJsonObject response;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(packet.body, &error);

    // 协议解析失败
    if (error.error != QJsonParseError::NoError) {
        response["success"] = false;
        response["message"] = "协议解析失败";
        sendResponse(socket, MessageType::FORGOT_PWD_RES, response);
        return;
    }

    QJsonObject req = doc.object();
    QString phone = req["phone"].toString().trimmed();
    QString code = req["captcha"].toString().trimmed();

    // 字段完整性验证
    if (phone.isEmpty() || code.isEmpty()) {
        response["success"] = false;
        response["message"] = "手机号和验证码不能为空";
        sendResponse(socket, MessageType::FORGOT_PWD_RES, response);
        return;
    }

    // 验证手机号和验证码
    bool verifyResult = UserService::verifyPhoneAndCode(phone, code);

    response["success"] = verifyResult;
    if (verifyResult) {
        response["message"] = "手机号和验证码校验通过";
        // 可返回临时令牌或重置权限标识
        response["data"] = QJsonObject{{"phone", phone}};
    } else {
        response["message"] = "该账号未注册";
    }

    sendResponse(socket, MessageType::FORGOT_PWD_RES, response);
}
