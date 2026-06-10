#include <iostream>
#include "../include/InventoryManager.h"

int main() {
    InventoryManager manager;
    InventoryItem item;

    item.sku = "SKU001";
    item.name = "Laptop";
    item.quantity = 100;
    item.location = "A01";

    manager.addItem(item);

    auto list = manager.getAllItems();
    std::cout << "Total: " << list.size() << std::endl;

    auto product = manager.getItemBySku("SKU001");
    std::cout << product.name << std::endl;

    product.quantity = 200;
    manager.updateItem(product);
    manager.deleteItem("SKU001");

    return 0;
}