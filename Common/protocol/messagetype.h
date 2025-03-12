#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include <QtGlobal>
#include <QDebug>

/**
 * @brief 全功能消息类型枚举
 * 协议分类架构：
 * - 0x1XXX: 用户身份与社交关系
 * - 0x2XXX: 实时消息通信
 * - 0x3XXX: 群组管理操作
 * - 0x4XXX: 数据查询与通知
 * - 0x5XXX: 文件传输控制
 * - 0xFXXX: 系统级控制
 */
enum class MessageType : quint16 {
    // 系统保留
    UNKNOWN             = 0x0000,  ///< 非法类型

    // ============== 用户身份与社交 0x1XXX ==============
    // 认证核心
    LOGIN_REQ           = 0x1001,  ///< 登录请求（含设备信息）
    LOGIN_RES           = 0x1002,  ///< 登录响应（含用户基础数据包）
    REGISTER_REQ        = 0x1003,  ///< 注册请求（昵称+手机号+密码）
    REGISTER_RES        = 0x1004,  ///< 注册响应（分配账号）
    FORGOT_PWD_REQ      = 0x1005,  ///< 忘记密码请求
    FORGOT_PWD_RES      = 0x1006,  ///< 忘记密码响应
    PWD_RESET_REQ       = 0x1007,  ///< 密码重置请求
    PWD_RESET_RES       = 0x1008,  ///< 密码重置结果

    // 用户资料
    UPDATE_PROFILE_REQ     = 0x1101,  ///< 用户资料更新请求
    UPDATE_PROFILE_RES     = 0x1102,  ///< 用户资料更新响应
    EDIT_PROFILE_REQ       = 0x1103,  ///< 编辑信息请求
    EDIT_PROFILE_RES       = 0x1104,   ///< 编辑信息响应

    // 好友系统
    FRIEND_SEARCH_REQ   = 0x1201,  ///< 搜索好友（账号/手机号）
    FRIEND_SEARCH_RES   = 0x1202,  ///< 好友搜索结果
    FRIEND_ADD_REQ      = 0x1203,  ///< 发送好友申请
    FRIEND_ADD_RES      = 0x1204,  ///< 申请结果响应
    FRIEND_LIST_REQ     = 0x1205,  ///< 拉取好友列表
    FRIEND_LIST_RES     = 0x1206,  ///< 好友列表数据（含在线状态）
    FRIEND_DELETE_REQ   = 0x1207,  ///< 删除好友关系
    FRIEND_DELETE_RES   = 0x1208,  ///< 删除结果确认

    // ============== 实时消息通信 0x2XXX ==============
    // 消息收发
    TEXT_MSG            = 0x2001,  ///< 文本消息（支持@）
    IMAGE_MSG           = 0x2002,  ///< 图片消息（含缩略图URL）
    FILE_MSG            = 0x2003,  ///< 文件传输请求
    FILE_ACK            = 0x2004,  ///< 文件接收确认

    // 消息状态
    MSG_STATUS_REQ      = 0x2101,  ///< 消息已读状态查询
    MSG_STATUS_RES      = 0x2102,  ///< 消息状态响应（已读/未读）

    // 历史记录
    HISTORY_REQ         = 0x2201,  ///< 聊天记录查询（支持分页）
    HISTORY_RES         = 0x2202,  ///< 历史消息数据包

    // ============== 群组管理 0x3XXX ==============
    // 群组核心
    GROUP_CREATE_REQ    = 0x3001,  ///< 创建群聊（含初始成员）
    GROUP_CREATE_RES    = 0x3002,  ///< 返回群号及二维码
    GROUP_JOIN_REQ      = 0x3003,  ///< 申请加入群聊
    GROUP_JOIN_RES      = 0x3004,  ///< 入群审批结果
    GROUP_QUIT_REQ      = 0x3005,  ///< 退出群聊
    GROUP_QUIT_RES      = 0x3006,  ///< 退群确认

    // 群管理
    GROUP_LIST_REQ      = 0x3101,  ///< 获取用户群列表
    GROUP_LIST_RES      = 0x3102,  ///< 群列表（含未读消息数）
    GROUP_INFO_REQ      = 0x3103,  ///< 群详情查询（成员列表）
    GROUP_INFO_RES      = 0x3104,  ///< 群信息数据包
    GROUP_UPDATE_REQ    = 0x3105,  ///< 修改群名称/头像
    GROUP_UPDATE_RES    = 0x3106,  ///< 群信息变更确认

    // ============== 数据查询与通知 0x4XXX ==============
    // 全局搜索
    SEARCH_GLOBAL_REQ   = 0x4001,  ///< 综合搜索（用户/群/记录）
    SEARCH_GLOBAL_RES   = 0x4002,  ///< 分类搜索结果

    // 通知推送
    NOTIFY_FRIEND_REQ   = 0x4101,  ///< 好友申请到达通知
    NOTIFY_GROUP_INVITE = 0x4102,  ///< 群邀请通知
    NOTIFY_MSG_UPDATE   = 0x4103,  ///< 消息状态变更推送

    // ============== 系统控制 0xFXXX ==============
    // 连接管理
    HEARTBEAT           = 0xF001,  ///< 心跳包（5分钟间隔）
    CONNECTION_CLOSE    = 0xF002,  ///< 安全断开连接

    // 数据同步
    SYNC_FULL_REQ       = 0xF101,  ///< 全量数据同步（登录时）
    SYNC_INCREMENTAL    = 0xF102,  ///< 增量数据推送（服务端触发）

    // 错误处理
    ERROR_COMMON        = 0xFF01,  ///< 通用错误（含错误码）
    ERROR_DB_FAILURE    = 0xFF02   ///< 数据库操作异常
};

// 重载 << 操作符
// 只保留声明
QDebug operator<<(QDebug debug, MessageType type);

#endif // MESSAGETYPE_H
