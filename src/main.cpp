#include <iostream>
#include <vector>

#include "../include/Product.h"

int main() {
    std::vector<Product> products;
    int choice;

    while (true) {
        std::cout << "\n===== Warehouse System =====\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. Show Products\n";
        std::cout << "0. Exit\n";

        std::cout << "Choose: ";
        std::cin >> choice;


        if (choice == 1) {
            int id;
            std::string name;
            int quantity;
            double price;

            std::cout << "Input ID: ";
            std::cin >> id;

            std::cout << "Input Name: ";
            std::cin >> name;

            std::cout << "Input Quantity: ";
            std::cin >> quantity;

            std::cout << "Input Price: ";
            std::cin >> price;

            Product p(id, name, quantity, price);

            products.push_back(p);

            std::cout << "Product Added!\n";
        }

        else if (choice == 2) {
            if (products.empty())
                std::cout << "No Product!\n";
            else {
                for (const auto& p : products)
                    p.display();
            }
        }
        else if (choice == 0) {
            std::cout << "Bye!\n";
            break;
        }
    }
    return 0;
}