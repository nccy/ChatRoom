#include "clienthandlerfactory.h"

NetworkDataHandler* ClientHandlerFactory::createHandler(MessageType type)
{
    switch (type) {
        // 用户身份与社交 - 认证核心
        case MessageType::LOGIN_RES:
            return new LoginHandler();
        case MessageType::REGISTER_RES:
            return new RegisterHandler();
        case MessageType::FORGOT_PWD_RES:
            return new ForgotPasswordHandler();
        case MessageType::PWD_RESET_RES:
            return new PwdResetHandler();

        // 用户身份与社交 - 用户资料
        case MessageType::EDIT_PROFILE_RES:
            return new EditProfileHandler();
//        // 用户身份与社交 - 用户资料
//        case MessageType::USER_UPDATE_RES:
//            return new UserUpdateHandler();

//        // 用户身份与社交 - 好友系统
//        case MessageType::FRIEND_SEARCH_RES:
//            return new FriendSearchHandler();
//        case MessageType::FRIEND_ADD_RES:
//            return new FriendAddHandler();
//        case MessageType::FRIEND_LIST_RES:
//            return new FriendListHandler();
//        case MessageType::FRIEND_DELETE_RES:
//            return new FriendDeleteHandler();

//        // 实时消息通信 - 消息收发
//        case MessageType::TEXT_MSG:
//            return new TextMsgHandler();
//        case MessageType::IMAGE_MSG:
//            return new ImageMsgHandler();
//        case MessageType::FILE_MSG:
//            return new FileMsgHandler();
//        case MessageType::FILE_ACK:
//            return new FileAckHandler();

//        // 实时消息通信 - 消息状态
//        case MessageType::MSG_STATUS_RES:
//            return new MsgStatusHandler();

//        // 实时消息通信 - 历史记录
//        case MessageType::HISTORY_RES:
//            return new HistoryHandler();

//        // 群组管理 - 群组核心
//        case MessageType::GROUP_CREATE_RES:
//            return new GroupCreateHandler();
//        case MessageType::GROUP_JOIN_RES:
//            return new GroupJoinHandler();
//        case MessageType::GROUP_QUIT_RES:
//            return new GroupQuitHandler();

//        // 群组管理 - 群管理
//        case MessageType::GROUP_LIST_RES:
//            return new GroupListHandler();
//        case MessageType::GROUP_INFO_RES:
//            return new GroupInfoHandler();
//        case MessageType::GROUP_UPDATE_RES:
//            return new GroupUpdateHandler();

//        // 数据查询与通知 - 全局搜索
//        case MessageType::SEARCH_GLOBAL_RES:
//            return new SearchGlobalHandler();

//        // 数据查询与通知 - 通知推送
//        case MessageType::NOTIFY_FRIEND_REQ:
//            return new NotifyFriendHandler();
//        case MessageType::NOTIFY_GROUP_INVITE:
//            return new NotifyGroupInviteHandler();
//        case MessageType::NOTIFY_MSG_UPDATE:
//            return new NotifyMsgUpdateHandler();

//        // 系统控制 - 连接管理
//        case MessageType::HEARTBEAT:
//            return new HeartbeatHandler();
//        case MessageType::CONNECTION_CLOSE:
//            return new ConnectionCloseHandler();

//        // 系统控制 - 数据同步
//        case MessageType::SYNC_FULL_REQ:
//            return new SyncFullHandler();
//        case MessageType::SYNC_INCREMENTAL:
//            return new SyncIncrementalHandler();

//        // 系统控制 - 错误处理
//        case MessageType::ERROR_COMMON:
//            return new ErrorCommonHandler();
//        case MessageType::ERROR_DB_FAILURE:
//            return new ErrorDbFailureHandler();

        default:
            return nullptr;
    }
}
