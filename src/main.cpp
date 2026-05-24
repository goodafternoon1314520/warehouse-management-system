#include <iostream>
// #include <vector>

#include "../include/Product.h"
#include "../include/Warehouse.h"

int main() {
    // std::vector<Product> products;
    Warehouse warehouse;

    // 启动自动加载
    warehouse.loadFromFile("../data/products.txt");

    int choice;

    while (true) {
        std::cout << "\n===== Warehouse System =====\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. Show Products\n";
        std::cout << "3. Save Data\n";
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

            Product product(id, name, quantity, price);

            warehouse.addProduct(product);

            std::cout << "Product Added!\n";
        }

        else if (choice == 2) {
            /*
            if (products.empty())
                std::cout << "No Product!\n";
            else {
                for (const auto& p : products)
                    p.display();
            }
            */

            warehouse.showProducts();
        }

        else if (choice == 3)
            warehouse.saveToFile("../data/products.txt");

        else if (choice == 0) {
            // 退出并自动保存
            warehouse.saveToFile("../data/products.txt");

            std::cout << "Bye!\n";
            break;
        }

        else
            std::cout << "Invalid Choice!\n";
    }
    return 0;
}