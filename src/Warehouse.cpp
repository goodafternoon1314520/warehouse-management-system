#include "../include/Warehouse.h"

#include <iostream>
#include <fstream>

void Warehouse::addProduct(const Product& product) {
    products.push_back(product);
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