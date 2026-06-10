#include <iostream>

#include "../include/InventoryManager.h"

int main() {
    InventoryManager manager;
    InventoryItem item;

    item.sku = "SKU001";
    item.name = "Laptop";
    item.quantity = 100;
    item.location = "A01";

    if (manager.addItem(item))
        std::cout << "Add Success" << std::endl;
}