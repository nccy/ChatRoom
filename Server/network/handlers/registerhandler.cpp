#include "registerhandler.h"
#include "../../service/userservice.h"
#include <QJsonDocument>
#include <QJsonObject>

void RegisterHandler::process(const ProtocolHandler::Packet& packet,
                              QTcpSocket* socket) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(packet.body, &error);

    QJsonObject response;

    // 协议解析失败
    if (error.error != QJsonParseError::NoError) {
        response["success"] = false;
        response["message"] = "协议解析失败";
        sendResponse(socket,MessageType::REGISTER_RES,response);
        return;
    }

    QJsonObject req = doc.object();
    QString nickname = req["nickname"].toString().trimmed();
    QString password = req["password"].toString();
    QString phone = req["phone"].toString().trimmed();

    // 字段验证
    if (nickname.isEmpty() || password.isEmpty() || phone.isEmpty()) {
        response["success"] = false;
        response["message"] = "昵称、密码或手机号不能为空";
        sendResponse(socket,MessageType::REGISTER_RES,response);
        return;
    }

    // 用户注册并获取完整信息
    UserInfo newUser;
    bool success = UserService::registerUser(nickname, password, phone,newUser);

    response["success"] = success;
    if (success) {
        response["message"] = "注册成功";
        // 构建用户数据对象
        QJsonObject userData;
        userData["id"] = newUser.getId();
        userData["account"] = newUser.getAccount(); // 假设自动生成账号
        userData["nickname"] = newUser.getNickname();
        userData["phone"] = newUser.getPhone();
        userData["avatarUrl"] = newUser.getAvatarUrl();
        userData["declaration"] = newUser.getDeclaration();
        response["data"] = userData;
    } else {
        response["message"] = "注册失败（手机号已存在）";
    }
    sendResponse(socket,MessageType::REGISTER_RES,response);
}
