#ifndef DBCONNECTIONPOOL_H
#define DBCONNECTIONPOOL_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QSqlDatabase>

/**
 * @brief 数据库连接池管理类
 * 职责：
 * - 管理预创建的数据库连接
 * - 提供线程安全的连接获取/释放接口
 * - 自动维护连接有效性
 */
class DBConnectionPool : public QObject {
    Q_OBJECT
public:
    /**
     * @brief 获取全局唯一实例
     * @return 单例指针
     */
    static DBConnectionPool* getInstance();

    /**
     * @brief 获取数据库连接（带超时等待）
     * @param timeoutMs 超时时间（毫秒）
     * @return 可用数据库连接对象，超时返回无效对象
     */
    QSqlDatabase getConnection(int timeoutMs = 5000);

    /**
     * @brief 释放连接回连接池
     * @param conn 要释放的连接对象
     */
    void releaseConnection(QSqlDatabase conn);

    /**
     * @brief 销毁所有连接并重置实例
     */
    void destroy();

private:
    explicit DBConnectionPool(QObject *parent = nullptr);
    ~DBConnectionPool();

    /// 初始化数据库结构（建库建表）
    void initializeDatabase();

    /// 初始化连接池
    void initConnectionPool();

    /// 创建新连接（私有方法）
    QSqlDatabase createNewConnection();

    /// 验证连接有效性
    bool validateConnection(QSqlDatabase &conn);

    QQueue<QSqlDatabase> m_pool;      // 连接池队列
    QMutex m_mutex;                   // 线程安全锁
    QWaitCondition m_condition;       // 连接可用条件变量
    static QMutex s_instanceMutex;    // 单例实例锁
    static DBConnectionPool* m_instance;
};

#endif // DBCONNECTIONPOOL_H
