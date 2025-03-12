#ifndef SERVERHANDLERFACTORY_H
#define SERVERHANDLERFACTORY_H

#include "handlers/loginhandler.h"
#include "protocol/messagetype.h"
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
 * @brief 服务端处理器工厂
 * 职责：根据协议类型动态创建对应的业务处理器
 */
class ServerHandlerFactory {
public:
    static RequestHandler* createHandler(MessageType type);
};

#endif // SERVERHANDLERFACTORY_H
