# 定义公共头文件路径
INCLUDEPATH += $$PWD

# 添加协议相关的头文件
HEADERS += \
    $$PWD/protocol/messagetype.h \
    $$PWD/protocol/protocolheader.h \
    $$PWD/protocol/protocolhandler.h \
    $$PWD/model/chatrecord.h \
    $$PWD/model/friendapplication.h \
    $$PWD/model/friendrelation.h \
    $$PWD/model/groupapplication.h \
    $$PWD/model/groupinfo.h \
    $$PWD/model/groupmember.h \
    $$PWD/model/userinfo.h

# 添加协议相关的源文件
SOURCES += $$PWD/protocol/protocolhandler.cpp \
    $$PWD/protocol/messagetype.cpp \
    $$PWD/model/chatrecord.cpp \
    $$PWD/model/friendapplication.cpp \
    $$PWD/model/friendrelation.cpp \
    $$PWD/model/groupapplication.cpp \
    $$PWD/model/groupinfo.cpp \
    $$PWD/model/groupmember.cpp \
    $$PWD/model/userinfo.cpp
