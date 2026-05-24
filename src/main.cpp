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
        std::cout << "3. Find Product\n";
        std::cout << "4. Delete Product\n";
        std::cout << "5. Update Product\n";
        std::cout << "6. Stock In\n";
        std::cout << "7. Stock Out\n";
        std::cout << "8. Save Data\n";
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

        else if (choice == 3) {
            // warehouse.saveToFile("../data/products.txt");
            int id;

            std::cout << "Input Product ID: ";
            std::cin >> id;

            Product* product = warehouse.findProduct(id);

            if (product == nullptr)
                std::cout << "Product not found!\n";
            else
                product -> display();
        }

        else if (choice == 4) {
            int id;

            std::cout << "Input Product ID: ";
            std::cin >> id;

            if (warehouse.deleteProduct(id))
                std::cout << "Product deleted!\n";
            else
                std::cout << "Product not found!\n";
        }

        else if (choice == 5) {
            int id;
            std::string name;
            int quantity;
            double price;

            std::cout << "Input Product ID: ";
            std::cin >> id;

            std::cout << "Input Name: ";
            std::cin >> name;

            std::cout << "Input Quantity: ";
            std::cin >> quantity;

            std::cout << "Input Price: ";
            std::cin >> price;

            if (warehouse.updateProduct(id, name, quantity, price))
                std::cout << "Product Updated!\n";
            else
                std::cout << "Product not found!\n";
        }

        else if (choice == 6) {
            int id;
            int amount;

            std::cout << "Input Product ID: ";
            std::cin >> id;

            std::cout << "Input Amount: ";
            std::cin >> amount;

            if (warehouse.stockIn(id, amount))
                std::cout << "Stock in success!\n";
            else
                std::cout << "Product not found!\n";
        }

        else if (choice == 7) {
            int id;
            int amount;

            std::cout << "Input Product ID: ";
            std::cin >> id;

            std::cout << "Input Amount: ";
            std::cin >> amount;

            if (warehouse.stockOut(id, amount))
                std::cout << "Stock out success!\n";
            else
                std::cout << "Product not failed!\n";
        }

        else if (choice == 8)
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