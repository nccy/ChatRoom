#include "dbconnectionpool.h"
#include "dbconfig.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QUuid>
#include <QCoreApplication>
#include <QTimer>

QMutex DBConnectionPool::s_instanceMutex;
DBConnectionPool* DBConnectionPool::m_instance = nullptr;

DBConnectionPool::DBConnectionPool(QObject *parent)
    : QObject(parent) {
    initializeDatabase();
    initConnectionPool();
}

DBConnectionPool::~DBConnectionPool() {
    destroy();
}

DBConnectionPool* DBConnectionPool::getInstance() {
    QMutexLocker locker(&s_instanceMutex);
    if (!m_instance) {
        m_instance = new DBConnectionPool();
    }
    return m_instance;
}

void DBConnectionPool::initializeDatabase() {
    qDebug() << "初始化数据库结构...";

    // 连接到 MySQL 服务器（不指定数据库）
    QString adminConnName = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlDatabase adminDb = QSqlDatabase::addDatabase("QMYSQL", adminConnName);
    adminDb.setHostName(DB_HOST);
    adminDb.setPort(DB_PORT);
    adminDb.setUserName(DB_USER);
    adminDb.setPassword(DB_PASS);

    if (!adminDb.open()) {
        qCritical().nospace() << "!! MySQL 连接失败: "
                              << adminDb.lastError().text().trimmed()
                              << " (错误码:"
                              << adminDb.lastError().nativeErrorCode() << ")";
        return;
    }

    // 创建数据库
    {
        QSqlQuery createDbQuery(adminDb);
        QString createDbSQL = QString("CREATE DATABASE IF NOT EXISTS `%1` CHARACTER SET utf8mb4")
                              .arg(DB_NAME);

        if (!createDbQuery.exec(createDbSQL)) {
            qCritical() << "!! 创建数据库失败:" << createDbQuery.lastError().text();
            adminDb.close();
            QSqlDatabase::removeDatabase(adminConnName);
            return;
        }
    }

    adminDb.close();
    QTimer::singleShot(0, [adminConnName](){
            QSqlDatabase::removeDatabase(adminConnName);
        });
    // 创建数据表
    QString initConnName = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlDatabase initDb = QSqlDatabase::addDatabase("QMYSQL", initConnName);
    initDb.setHostName(DB_HOST);
    initDb.setPort(DB_PORT);
    initDb.setDatabaseName(DB_NAME);
    initDb.setUserName(DB_USER);
    initDb.setPassword(DB_PASS);

    if (!initDb.open()) {
        qCritical() << "!! 数据库连接失败:" << initDb.lastError().text();
        return;
    }

    // 设置自动提交（限制QSqlQuery作用域）
    {
        QSqlQuery setAutoCommitQuery(initDb);
        if (!setAutoCommitQuery.exec("SET AUTOCOMMIT = 1")) {
            qCritical() << "!! 设置自动提交失败:" << setAutoCommitQuery.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }
    // 创建用户表
    {
        QSqlQuery createUserTable(initDb);
        QString userTableSQL = R"(
            CREATE TABLE IF NOT EXISTS `user_info` (
                `id` INT PRIMARY KEY AUTO_INCREMENT COMMENT '自增主键，唯一标识用户',
                `account` VARCHAR(50) UNIQUE NOT NULL COMMENT '用户账号（唯一，不可重复）',
                `nickname` VARCHAR(50) NOT NULL COMMENT '用户昵称',
                `password_hash` VARCHAR(255) NOT NULL COMMENT '加密后的密码（如 SHA-256 + 盐值）',
                `salt` VARCHAR(64) NOT NULL COMMENT '加密盐值',
                `phone` VARCHAR(20) UNIQUE COMMENT '用户手机号（唯一）',
                `avatar_url` VARCHAR(255) COMMENT '用户头像的网络 URL',
                `declaration` TEXT COMMENT '用户个性签名或宣言',
                `create_time` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '用户注册时间（服务器时间）'
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
        )";

        if (!createUserTable.exec(userTableSQL)) {
            qCritical() << "!! 创建用户表失败:" << createUserTable.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }

    // 创建好友表
    {
        QSqlQuery createFriendRelationTable(initDb);
        QString friendRelationTableSQL = R"(
            CREATE TABLE IF NOT EXISTS `friend_relation` (
                `id` INT PRIMARY KEY AUTO_INCREMENT COMMENT '自增主键',
                `user_id` INT NOT NULL COMMENT '用户 ID（关联 user_info.id）',
                `friend_id` INT NOT NULL COMMENT '好友 ID（关联 user_info.id）',
                `add_time` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '好友关系建立时间',
                FOREIGN KEY (`user_id`) REFERENCES `user_info`(`id`),
                FOREIGN KEY (`friend_id`) REFERENCES `user_info`(`id`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
        )";

        if (!createFriendRelationTable.exec(friendRelationTableSQL)) {
            qCritical() << "!! 创建好友表失败:" << createFriendRelationTable.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }

    // 创建好友申请表
    {
        QSqlQuery createFriendApplicationTable(initDb);
        QString friendApplicationTableSQL = R"(
            CREATE TABLE IF NOT EXISTS `friend_application` (
                `id` INT PRIMARY KEY AUTO_INCREMENT COMMENT '自增主键',
                `sender_id` INT NOT NULL COMMENT '发送者 ID（关联 user_info.id）',
                `receiver_id` INT NOT NULL COMMENT '接收者 ID（关联 user_info.id）',
                `status` TINYINT NOT NULL DEFAULT 0 COMMENT '状态：0=待处理，1=同意，2=拒绝',
                `create_time` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '申请创建时间',
                `update_time` DATETIME COMMENT '状态更新时间',
                FOREIGN KEY (`sender_id`) REFERENCES `user_info`(`id`),
                FOREIGN KEY (`receiver_id`) REFERENCES `user_info`(`id`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
        )";

        if (!createFriendApplicationTable.exec(friendApplicationTableSQL)) {
            qCritical() << "!! 创建好友申请表失败:" << createFriendApplicationTable.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }

    // 创建群聊信息表
    {
        QSqlQuery createGroupInfoTable(initDb);
        QString groupInfoTableSQL = R"(
            CREATE TABLE IF NOT EXISTS `group_info` (
                `id` INT PRIMARY KEY AUTO_INCREMENT COMMENT '自增主键',
                `group_number` VARCHAR(50) UNIQUE NOT NULL COMMENT '群号（唯一，不可重复）',
                `group_name` VARCHAR(100) NOT NULL COMMENT '群名称',
                `group_avatar_url` VARCHAR(255) COMMENT '群头像的网络 URL',
                `creator_id` INT NOT NULL COMMENT '群主 ID（关联 user_info.id）',
                `create_time` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '群创建时间',
                `introduction` TEXT COMMENT '群简介，补充群聊信息',
                `notice` TEXT COMMENT '群公告，群聊重要通知信息'
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
        )";

        if (!createGroupInfoTable.exec(groupInfoTableSQL)) {
            qCritical() << "!! 创建群聊表失败:" << createGroupInfoTable.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }

    // 创建群成员表
    {
        QSqlQuery createGroupMemberTable(initDb);
        QString groupMemberTableSQL = R"(
            CREATE TABLE IF NOT EXISTS `group_member` (
                `id` INT PRIMARY KEY AUTO_INCREMENT COMMENT '自增主键',
                `group_id` INT NOT NULL COMMENT '群 ID（关联 group_info.id）',
                `user_id` INT NOT NULL COMMENT '成员 ID（关联 user_info.id）',
                `join_time` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '加入群聊时间',
                FOREIGN KEY (`group_id`) REFERENCES `group_info`(`id`),
                FOREIGN KEY (`user_id`) REFERENCES `user_info`(`id`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
        )";

        if (!createGroupMemberTable.exec(groupMemberTableSQL)) {
            qCritical() << "!! 创建群成员表失败:" << createGroupMemberTable.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }

    // 创建群聊申请表
    {
        QSqlQuery createGroupApplicationTable(initDb);
        QString groupApplicationTableSQL = R"(
            CREATE TABLE IF NOT EXISTS `group_application` (
                `id` INT PRIMARY KEY AUTO_INCREMENT COMMENT '自增主键',
                `group_id` INT NOT NULL COMMENT '目标群 ID（关联 group_info.id）',
                `applicant_id` INT NOT NULL COMMENT '申请人 ID（关联 user_info.id）',
                `status` TINYINT NOT NULL DEFAULT 0 COMMENT '状态：0=待处理，1=同意，2=拒绝',
                `create_time` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '申请创建时间',
                `update_time` DATETIME COMMENT '状态更新时间',
                FOREIGN KEY (`group_id`) REFERENCES `group_info`(`id`),
                FOREIGN KEY (`applicant_id`) REFERENCES `user_info`(`id`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
        )";

        if (!createGroupApplicationTable.exec(groupApplicationTableSQL)) {
            qCritical() << "!! 创建群聊申请表失败:" << createGroupApplicationTable.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }

    // 创建聊天记录表
    {
        QSqlQuery createChatRecordTable(initDb);
        QString chatRecordTableSQL = R"(
            CREATE TABLE IF NOT EXISTS `chat_record` (
                `id` INT PRIMARY KEY AUTO_INCREMENT COMMENT '自增主键，唯一标识每条聊天记录',
                `sender_id` INT NOT NULL COMMENT '发送者 ID，关联 user_info 表中的用户 ID，用于标识消息的发送者',
                `receiver_id` INT NOT NULL COMMENT '接收者 ID，可能是用户 ID 或者群 ID，具体由 receiver_type 决定',
                `receiver_type` TINYINT NOT NULL COMMENT '接受者类型，用于区分接收者是普通用户还是群聊，例如 0 表示用户，1 表示群聊',
                `message_type` TINYINT NOT NULL COMMENT '消息类型：1=文本，2=图片，3=文件，用于标识消息的具体类型',
                `message_content` TEXT NOT NULL COMMENT '消息内容（文本或文件 URL），如果是文本消息则直接存储文本，如果是图片或文件则存储其网络 URL',
                `timestamp` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '消息发送时间，记录消息发送的具体时间，默认值为当前服务器时间',
                `version` INT DEFAULT 1 COMMENT '乐观锁版本号（用于冲突解决），在并发更新聊天记录时用于检测数据冲突',
                FOREIGN KEY (`sender_id`) REFERENCES `user_info`(`id`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='聊天记录表，存储所有聊天消息，支持消息同步和历史查询'
        )";

        if (!createChatRecordTable.exec(chatRecordTableSQL)) {
            qCritical() << "!! 创建聊天记录表失败:" << createChatRecordTable.lastError().text();
            initDb.close();
            QSqlDatabase::removeDatabase(initConnName);
            return;
        }
    }

    initDb.close();
    QTimer::singleShot(0, [initConnName](){
            QSqlDatabase::removeDatabase(initConnName);
        });
    qInfo() << "数据库结构初始化完成";
}

void DBConnectionPool::initConnectionPool() {
    qDebug() << "初始化连接池...";
    int successCount = 0;

    for (int i = 0; i < POOL_SIZE; ++i) {
        QSqlDatabase db = createNewConnection();
        if (db.isOpen()) {
            m_pool.enqueue(db);
            successCount++;
        }
    }

    if (successCount == 0) {
        qFatal("!! 无法创建任何有效连接，请检查数据库配置");
    }
    qInfo() << "连接池初始化完成，有效连接:" << successCount << "/" << POOL_SIZE;
}

QSqlDatabase DBConnectionPool::getConnection(int timeoutMs) {
    QMutexLocker locker(&m_mutex);

    // 带超时的等待逻辑
    while (m_pool.isEmpty()) {
        qWarning() << "连接池已耗尽，等待可用连接...";
        if (!m_condition.wait(&m_mutex, timeoutMs)) {
            qCritical() << "!! 获取连接超时 (" << timeoutMs << "ms)";
            return QSqlDatabase();
        }
    }

    QSqlDatabase conn = m_pool.dequeue();
    if (!validateConnection(conn)) {
        qWarning() << "连接" << conn.connectionName() << "已失效，尝试重建...";
        conn = createNewConnection();
    }

    qDebug() << "分配连接:" << conn.connectionName();
    return conn;
}

void DBConnectionPool::releaseConnection(QSqlDatabase conn) {
    if (!conn.isOpen()) {
        qWarning() << " 无效连接，尝试重建...";
        conn = createNewConnection();
        if (!conn.isOpen()) return;
    }

    QMutexLocker locker(&m_mutex);
    m_pool.enqueue(conn);
    m_condition.wakeOne(); // 通知等待线程
    qDebug() << "释放连接:" << conn.connectionName();
}

QSqlDatabase DBConnectionPool::createNewConnection() {
    QString connName = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connName);
    db.setHostName(DB_HOST);
    db.setPort(DB_PORT);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASS);

    if (!db.open()) {
        qCritical().nospace() << "!! 连接创建失败 [" << connName << "]: "
                            << db.lastError().text().trimmed()
                            << " (错误码:"
                            << db.lastError().nativeErrorCode() << ")";
        return QSqlDatabase();
    }
    return db;
}

bool DBConnectionPool::validateConnection(QSqlDatabase &conn) {
    if (!conn.isOpen()) return false;

    QSqlQuery query("SELECT 1", conn);
    return query.exec() && query.next() && (query.value(0).toInt() == 1);
}

void DBConnectionPool::destroy() {
    QMutexLocker locker(&m_mutex);
    qDebug() << "关闭所有数据库连接...";

    while (!m_pool.isEmpty()) {
        QSqlDatabase conn = m_pool.dequeue();
        QString connName = conn.connectionName();
        conn.close();
        QSqlDatabase::removeDatabase(connName);
        qDebug() << "关闭连接:" << connName;
    }

    QSqlDatabase::removeDatabase("AdminConnection");
    QSqlDatabase::removeDatabase("InitConnection");
    qInfo() << "所有连接已关闭";
}
