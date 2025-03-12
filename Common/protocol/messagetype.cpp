#include "messagetype.h"

QDebug operator<<(QDebug debug, MessageType type) {
    switch (type) {
        case MessageType::UNKNOWN:
            debug << "UNKNOWN";
            break;
        case MessageType::LOGIN_REQ:
            debug << "LOGIN_REQ";
            break;
        case MessageType::LOGIN_RES:
            debug << "LOGIN_RES";
            break;
        case MessageType::REGISTER_REQ:
            debug << "REGISTER_REQ";
            break;
        case MessageType::REGISTER_RES:
            debug << "REGISTER_RES";
            break;
        case MessageType::FORGOT_PWD_REQ:
            debug << "FORGOT_PWD_REQ";
            break;
        case MessageType::FORGOT_PWD_RES:
            debug << "FORGOT_PWD_RES";
            break;
        case MessageType::PWD_RESET_REQ:
            debug << "PWD_RESET_REQ";
            break;
        case MessageType::PWD_RESET_RES:
            debug << "PWD_RESET_RES";
            break;
        case MessageType::UPDATE_PROFILE_REQ:
            debug << "UPDATE_PROFILE_REQ";
            break;
        case MessageType::UPDATE_PROFILE_RES:
            debug << "UPDATE_PROFILE_RES";
            break;
        case MessageType::EDIT_PROFILE_REQ:
            debug << "EDIT_PROFILE_REQ";
            break;
        case MessageType::EDIT_PROFILE_RES:
            debug << "EDIT_PROFILE_RES";
            break;
        case MessageType::FRIEND_SEARCH_REQ:
            debug << "FRIEND_SEARCH_REQ";
            break;
        case MessageType::FRIEND_SEARCH_RES:
            debug << "FRIEND_SEARCH_RES";
            break;
        case MessageType::FRIEND_ADD_REQ:
            debug << "FRIEND_ADD_REQ";
            break;
        case MessageType::FRIEND_ADD_RES:
            debug << "FRIEND_ADD_RES";
            break;
        case MessageType::FRIEND_LIST_REQ:
            debug << "FRIEND_LIST_REQ";
            break;
        case MessageType::FRIEND_LIST_RES:
            debug << "FRIEND_LIST_RES";
            break;
        case MessageType::FRIEND_DELETE_REQ:
            debug << "FRIEND_DELETE_REQ";
            break;
        case MessageType::FRIEND_DELETE_RES:
            debug << "FRIEND_DELETE_RES";
            break;
        case MessageType::TEXT_MSG:
            debug << "TEXT_MSG";
            break;
        case MessageType::IMAGE_MSG:
            debug << "IMAGE_MSG";
            break;
        case MessageType::FILE_MSG:
            debug << "FILE_MSG";
            break;
        case MessageType::FILE_ACK:
            debug << "FILE_ACK";
            break;
        case MessageType::MSG_STATUS_REQ:
            debug << "MSG_STATUS_REQ";
            break;
        case MessageType::MSG_STATUS_RES:
            debug << "MSG_STATUS_RES";
            break;
        case MessageType::HISTORY_REQ:
            debug << "HISTORY_REQ";
            break;
        case MessageType::HISTORY_RES:
            debug << "HISTORY_RES";
            break;
        case MessageType::GROUP_CREATE_REQ:
            debug << "GROUP_CREATE_REQ";
            break;
        case MessageType::GROUP_CREATE_RES:
            debug << "GROUP_CREATE_RES";
            break;
        case MessageType::GROUP_JOIN_REQ:
            debug << "GROUP_JOIN_REQ";
            break;
        case MessageType::GROUP_JOIN_RES:
            debug << "GROUP_JOIN_RES";
            break;
        case MessageType::GROUP_QUIT_REQ:
            debug << "GROUP_QUIT_REQ";
            break;
        case MessageType::GROUP_QUIT_RES:
            debug << "GROUP_QUIT_RES";
            break;
        case MessageType::GROUP_LIST_REQ:
            debug << "GROUP_LIST_REQ";
            break;
        case MessageType::GROUP_LIST_RES:
            debug << "GROUP_LIST_RES";
            break;
        case MessageType::GROUP_INFO_REQ:
            debug << "GROUP_INFO_REQ";
            break;
        case MessageType::GROUP_INFO_RES:
            debug << "GROUP_INFO_RES";
            break;
        case MessageType::GROUP_UPDATE_REQ:
            debug << "GROUP_UPDATE_REQ";
            break;
        case MessageType::GROUP_UPDATE_RES:
            debug << "GROUP_UPDATE_RES";
            break;
        case MessageType::SEARCH_GLOBAL_REQ:
            debug << "SEARCH_GLOBAL_REQ";
            break;
        case MessageType::SEARCH_GLOBAL_RES:
            debug << "SEARCH_GLOBAL_RES";
            break;
        case MessageType::NOTIFY_FRIEND_REQ:
            debug << "NOTIFY_FRIEND_REQ";
            break;
        case MessageType::NOTIFY_GROUP_INVITE:
            debug << "NOTIFY_GROUP_INVITE";
            break;
        case MessageType::NOTIFY_MSG_UPDATE:
            debug << "NOTIFY_MSG_UPDATE";
            break;
        case MessageType::HEARTBEAT:
            debug << "HEARTBEAT";
            break;
        case MessageType::CONNECTION_CLOSE:
            debug << "CONNECTION_CLOSE";
            break;
        case MessageType::SYNC_FULL_REQ:
            debug << "SYNC_FULL_REQ";
            break;
        case MessageType::SYNC_INCREMENTAL:
            debug << "SYNC_INCREMENTAL";
            break;
        case MessageType::ERROR_COMMON:
            debug << "ERROR_COMMON";
            break;
        case MessageType::ERROR_DB_FAILURE:
            debug << "ERROR_DB_FAILURE";
            break;
        default:
            debug << "UNKNOWN_TYPE";
    }
    return debug;
}
