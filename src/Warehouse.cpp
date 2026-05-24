#include "../include/Warehouse.h"

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

