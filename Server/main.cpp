#include <QCoreApplication>
#include <QThreadPool>
#include <QDebug>
#include <qtextcodec.h>
#include "network/tcpserver.h"
#include <database/dbconnectionpool.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 设置编码格式
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // 解析命令行参数
    quint16 port = 12345;
    if (argc > 1) {
        bool ok;
        port = QString(argv[1]).toUShort(&ok);
        if (!ok) {
            qCritical() << "无效的端口号，使用默认端口 12345";
            port = 12345;
        }
    }

    // 创建TCP服务器
    TcpServer server(nullptr, port);
    if (!server.isListening()) {
        qCritical() << "服务器启动失败";
        return EXIT_FAILURE;
    }

    qInfo() << "服务器成功启动";

    //初始化数据库
    DBConnectionPool::getInstance();


    return a.exec();
}
