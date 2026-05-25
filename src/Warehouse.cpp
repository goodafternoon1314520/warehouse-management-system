#include "../include/Warehouse.h"
#include "../include/Logger.h"

#include <iostream>
#include <fstream>

bool Warehouse::addProduct(const Product& product) {
    for (const auto& p : products) {
        if (p.getId() == product.getId()) {
            std::cout << "Product ID already exists!\n";
            return false;
        }
    }

    products.push_back(product);

    return true;
}

void Warehouse::showProducts() const {
    if (products.empty()) {
        std::cout << "No products!\n";
        return;
    }

    for (const auto& product : products)
        product.display();
}

void Warehouse::saveToFile(const std::string& filename) {
    std::ofstream fout(filename);

    if (!fout) {
        std::cout << "File open failed!\n";
        return;
    }

    for (const auto& product : products) {
        fout << product.getId() << " "
             << product.getName() << " "
             << product.getQuantity() << " "
             << product.getPrice() << std::endl;
    }

    fout.close();

    std::cout << "Data saved successfully!\n";
}

void Warehouse::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);

    if (!fin) {
        std::cout << "No data file found.\n";
        return;
    }

    int id;
    std::string name;
    int quantity;
    double price;

    while (fin >> id >> name >> quantity >> price) {
        Product product(id, name, quantity, price);

        products.push_back(product);
    }
    fin.close();

    std::cout << "Data loaded successfully!\n";
}

Product* Warehouse::findProduct(int id) {
    for (auto& product : products) {
        if (product.getId() == id)
            return &product;
    }
    return nullptr;
}

bool Warehouse::deleteProduct(int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it -> getId() == id) {
            products.erase(it);
            return true;
        }
    }
    return false;
}

bool Warehouse::updateProduct(int id, std::string name, int quantity, double price) {
    Product* product = findProduct(id);

    if (product == nullptr)
        return false;

    product -> setProduct(id, name, quantity, price);

    return true;
}

bool Warehouse::stockIn(int id, int amount) {
    Product* product = findProduct(id);

    if (product == nullptr)
        return false;

    product -> increaseQuantity(amount);

    std::string logMessage = "Stock In\nProduct ID: " + std::to_string(id) + "\nAmount: +" + std::to_string(amount);
    Logger::log(logMessage);

    return true;
}

bool Warehouse::stockOut(int id, int amount) {
    Product* product = findProduct(id);

    if (product == nullptr)
        return false;

    bool success =  product -> decreaseQuantity(amount);

    if (success) {
        std::string logMessage = "Stock Out\nProduct ID: " + std::to_string(id) + "\nAmount: -" + std::to_string(amount);
        Logger::log(logMessage);
    }
    return success;
}

int Warehouse::getTotalProducts() const {
    return products.size();
}

double Warehouse::getTotalValue() const {
    double total = 0;

    for (const auto& product : products)
        total += product.getQuantity() * product.getPrice();

    return total;
}

void Warehouse::showLowStockProducts(int threshold) const {
    bool found = false;

    for (const auto& product : products) {
        if (product.getQuantity() < threshold) {
            product.display();
            found = true;
        }
    }

    if (!found)
        std::cout << "No low stock products." << std::endl;
}