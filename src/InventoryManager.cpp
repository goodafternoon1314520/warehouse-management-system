#include "../include/InventoryManager.h"
#include "../include/Database.h"
#include <iostream>

bool InventoryManager::addItem(const InventoryItem& item) {
    sqlite3* db = Database::getConnection();
    if (!db) {
        std::cout << "Failed to open DB!\n";
        return false;
    }

    const char* sql = "INSERT INTO inventory (sku, name, quantity, location) VALUES(?,?,?,?)";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, item.sku.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, item.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, item.quantity);
    sqlite3_bind_text(stmt, 4, item.location.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cout << "SQLite Insert Error: " << sqlite3_errmsg(db) << std::endl;
    }

    // bool success = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return rc == SQLITE_DONE;
}

std::vector<InventoryItem> InventoryManager::getAllItems() {
    sqlite3* db = Database::getConnection();

    std::vector<InventoryItem> result;
    const char* sql = "SELECT id, sku, name, quantity, location FROM inventory";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        InventoryItem item;

        item.id = sqlite3_column_int(stmt, 0);
        item.sku = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        item.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        item.quantity = sqlite3_column_int(stmt, 3);
        item.location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        result.push_back(item);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

// 根据SKU查询
InventoryItem InventoryManager::getItemBySku(const std::string& sku) {
    sqlite3* db = Database::getConnection();
    InventoryItem item;

    const char* sql = "SELECT id, sku, name, quantity, location FROM inventory WHERE sku = ?";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, sku.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        item.id = sqlite3_column_int(stmt, 0);
        item.sku = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        item.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        item.quantity = sqlite3_column_int(stmt, 3);
        item.location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return item;
}

// 更新库存
bool InventoryManager::updateItem(const InventoryItem& item) {
    sqlite3* db = Database::getConnection();
    const char* sql = "UPDATE inventory SET name = ?, quantity = ?, location = ? WHERE sku = ?";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, item.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, item.quantity);
    sqlite3_bind_text(stmt, 3, item.location.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, item.sku.c_str(), -1, SQLITE_TRANSIENT);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return success;
}

// 删除库存
bool InventoryManager::deleteItem(const std::string& sku) {
    sqlite3* db = Database::getConnection();
    const char* sql = "DELETE FROM inventory WHERE sku = ?";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, sku.c_str(), -1, SQLITE_TRANSIENT);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return success;
}