#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;

public:
    Database();

    ~Database();

    // 连接数据库
    bool connect(const std::string& dbName);

    // 执行SQL
    bool execute(const std::string& sql);

    // 获取数据库对象
    sqlite3* getDB();

    // 查询SQL
    bool query(const std::string& sql, int (*callback)(void*, int, char**, char**));

    static sqlite3* getConnection();
};

#endif