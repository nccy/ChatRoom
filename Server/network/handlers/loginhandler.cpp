#include "loginhandler.h"
#include "../../service/userservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QBuffer>
#include <QDebug>

void LoginHandler::process(const ProtocolHandler::Packet& packet,
                          QTcpSocket* socket) {
    QJsonObject response;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(packet.body, &error);

    // 协议解析失败
    if (error.error != QJsonParseError::NoError) {
        response["success"] = false;
        response["message"] = "协议解析失败";
        sendResponse(socket,MessageType::LOGIN_RES,response);
        return;
    }

    QJsonObject req = doc.object();
    QString account = req["account"].toString().trimmed();
    QString password = req["password"].toString();

    // 字段完整性验证
    if (account.isEmpty() || password.isEmpty()) {
        response["success"] = false;
        response["message"] = "账号密码不能为空";
        sendResponse(socket,MessageType::LOGIN_RES,response);
        return;
    }

    // 用户认证并获取完整信息
    UserInfo user;
    bool authResult = UserService::authenticate(account, password, user);

    response["success"] = authResult;
    if (authResult) {
        response["message"] = "登录成功";
        // 构建用户数据对象
        QJsonObject userData;
        userData["id"] = user.getId();
        userData["account"] = user.getAccount();
        userData["nickname"] = user.getNickname();
        userData["phone"] = user.getPhone();
        userData["avatarUrl"] = user.getAvatarUrl();
        // 处理头像图片
       QString avatarUrl = user.getAvatarUrl();
       qDebug() << avatarUrl;
       QImage image;
       if (image.load(avatarUrl)) {
           QByteArray byteArray;
           QBuffer buffer(&byteArray);
           buffer.open(QIODevice::WriteOnly);
           if (image.save(&buffer, "PNG")) { // 根据实际格式调整
               QString base64Image = QString::fromLatin1(byteArray.toBase64());
               userData["avatar"] = base64Image;
           } else {
               userData["avatar"] = "";
           }
       } else {
           userData["avatar"] = "";
       }
        response["data"] = userData;
    } else {
        response["message"] = "用户名或密码错误";
    }

    sendResponse(socket,MessageType::LOGIN_RES,response);
}
