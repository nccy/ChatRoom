QT       += core network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 引入公共模块的pri文件
include(../common/common.pri)

SOURCES += \
    dao/userdao.cpp \
    database/dbconnectionpool.cpp \
    main.cpp \
    network/handlers/editprofilehandler.cpp \
    network/handlers/forgotpasswordhandler.cpp \
    network/handlers/loginhandler.cpp \
    network/handlers/pwdresethandler.cpp \
    network/handlers/registerhandler.cpp \
    network/requestdispatcher.cpp \
    network/requesthandler.cpp \
    network/serverhandlerfactory.cpp \
    network/tcpserver.cpp \
    service/userservice.cpp

HEADERS += \
    dao/userdao.h \
    database/dbconfig.h \
    database/dbconnectionpool.h \
    network/handlers/editprofilehandler.h \
    network/handlers/forgotpasswordhandler.h \
    network/handlers/loginhandler.h \
    network/handlers/pwdresethandler.h \
    network/handlers/registerhandler.h \
    network/requestdispatcher.h \
    network/requesthandler.h \
    network/serverhandlerfactory.h \
    network/tcpserver.h \
    service/userservice.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
