// editprofilehandler.h
#ifndef EDITPROFILEHANDLER_H
#define EDITPROFILEHANDLER_H

#include "network/networkdatahandler.h"
#include "model/userinfo.h"

/**
 * @brief 编辑资料响应处理器
 * 协议类型：处理 MessageType::EDIT_PROFILE_RES (假设为0x1003)
 */
class EditProfileHandler : public NetworkDataHandler
{
    Q_OBJECT
public:
    explicit EditProfileHandler(QObject *parent = nullptr);

    // 实现基类接口
    void processResponse(const QByteArray& response) override;

signals:
    // 编辑资料结果信号
    void editProfileResult(bool success,
                          const QString &message,
                          const UserInfo &updatedUser);

private:
    static constexpr int PROTOCOL_TYPE = 0x1003; // 假设的协议类型
};

#endif // EDITPROFILEHANDLER_H
