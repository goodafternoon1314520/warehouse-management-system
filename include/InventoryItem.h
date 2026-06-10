#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <string>

struct InventoryItem {
    int id;
    std::string sku;
    std::string name;
    int quantity;
    std::string location;
};

#endif