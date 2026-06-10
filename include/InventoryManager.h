#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>

#include "InventoryItem.h"

class InventoryManager {
public:
    bool addItem(const InventoryItem& item);

    bool updateItem(const InventoryItem& item);

    // bool deleteItem(int id);

    bool deleteItem(const std::string& sku);

    std::vector<InventoryItem> getAllItems();

    InventoryItem getItemBySku(const std::string& sku);
};



#endif