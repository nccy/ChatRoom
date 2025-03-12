#ifndef DBCONFIG_H
#define DBCONFIG_H

/**
 * @brief 数据库连接配置参数
 * 注意：实际项目应通过配置文件加载
 */
#define DB_HOST "127.0.0.1"     // 数据库服务器地址
#define DB_PORT 3306            // 数据库端口
#define DB_NAME "chat_server"    // 数据库名称
#define DB_USER "root"           // 数据库用户名
#define DB_PASS "123456"        // 数据库密码
#define POOL_SIZE 10             // 连接池最大连接数
#define CONN_TIMEOUT 5000       // 连接超时时间（毫秒）

#endif // DBCONFIG_H
