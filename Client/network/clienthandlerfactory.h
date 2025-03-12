#ifndef CLIENTHANDLERFACTORY_H
#define CLIENTHANDLERFACTORY_H

#include "networkdatahandler.h"
#include "protocol/messagetype.h"
#include "handlers/loginhandler.h"
#include "handlers/registerhandler.h"
#include "handlers/forgotpasswordhandler.h"
#include "handlers/pwdresethandler.h"
#include "handlers/editprofilehandler.h"
//#include "handlers/userupdatehandler.h"
//#include "handlers/friendsearchhandler.h"
//#include "handlers/friendaddhandler.h"
//#include "handlers/friendlisthandler.h"
//#include "handlers/frienddeletehandler.h"
//#include "handlers/textmsghandler.h"
//#include "handlers/imagemshandler.h"
//#include "handlers/filemsghandler.h"
//#include "handlers/fileackhandler.h"
//#include "handlers/msgstatushandler.h"
//#include "handlers/historyhandler.h"
//#include "handlers/groupcreatehandler.h"
//#include "handlers/groupjoinhandler.h"
//#include "handlers/groupquithandler.h"
//#include "handlers/grouplisthandler.h"
//#include "handlers/groupinfohandler.h"
//#include "handlers/groupupdatehandler.h"
//#include "handlers/searchglobalhandler.h"
//#include "handlers/notifyfriendhandler.h"
//#include "handlers/notifygroupinvitehandler.h"
//#include "handlers/notifymsgupdatehandler.h"
//#include "handlers/heartbeathandler.h"
//#include "handlers/connectionclosehandler.h"
//#include "handlers/syncfullhandler.h"
//#include "handlers/syncincrementalhandler.h"
//#include "handlers/errorcommonhandler.h"
//#include "handlers/errordbfailurehandler.h"
/**
 * @brief 客户端处理器工厂
 * 职责：根据协议类型动态创建对应的响应处理器
 * 设计要点：
 * - 与服务端ServerHandlerFactory对称设计
 * - 使用switch-case实现简单工厂模式
 */
class ClientHandlerFactory
{
public:
    static NetworkDataHandler* createHandler(MessageType type);
};
#endif // CLIENTHANDLERFACTORY_H
