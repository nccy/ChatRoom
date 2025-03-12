#include "editprofilehandler.h"
#include "../../service/userservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QBuffer>
#include <QDebug>

void EditProfileHandler::process(const ProtocolHandler::Packet& packet,
                                 QTcpSocket* socket) {
    QJsonObject response;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(packet.body, &error);

    // 协议解析失败
    if (error.error != QJsonParseError::NoError) {
        response["success"] = false;
        response["message"] = "协议解析失败";
        sendResponse(socket, MessageType::EDIT_PROFILE_RES, response);
        return;
    }

    UserInfo user;
    QJsonObject req = doc.object();
    QString account = req["account"].toString().trimmed();

    bool authResult = UserService::getUserByAccount(account,user);

    response["success"] = authResult;
    if (authResult) {
        response["message"] = "获取用户信息成功";
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
        response["message"] = "获取用户信息失败";
    }

    sendResponse(socket, MessageType::EDIT_PROFILE_RES, response);
}
