#include "../include/Database.h"

#include <iostream>

Database::Database() {
    db = nullptr;
}

Database::~Database() {
    if (db != nullptr)
        sqlite3_close(db);
}

bool Database::connect(const std::string& dbName) {
    int result = sqlite3_open(dbName.c_str(), &db);

    if (result != SQLITE_OK) {
        std::cout << "Database connection failed!\n";
        return false;
    }
    std::cout << "Database connected.\n";
    return true;
}

bool Database::execute(const std::string& sql) {
    char* errMsg = nullptr;

    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        std::cout << "SQL Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

sqlite3* Database::getDB() {
    return db;
}

