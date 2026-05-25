#include <iostream>
// #include <vector>

#include "../include/Product.h"
#include "../include/Warehouse.h"
#include "../include/UserManager.h"
#include "../include/Utils.h"
#include "../include/Database.h"

int main() {
    try {
        Database database;

        // database.connect("../data/warehouse.db");

        UserManager userManager;

        userManager.loadUsers("../data/users.txt");

        std::string username;
        std::string password;

        std::cout << "===== Login =====\n";

        std::cout << "Username: ";
        // std::cin >> username;
        username = Utils::inputString();

        std::cout << "Password: ";
        // std::cin >> password;
        password = Utils::inputString();

        User* currentUser = userManager.login(username, password);

        if (currentUser == nullptr) {
            std::cout << "Login failed!\n";
            return 0;
        }

        std::cout << "Welcome " << currentUser -> getUsername() << std::endl;

        // std::vector<Product> products;
        Warehouse warehouse;

        // 启动自动加载
        // warehouse.loadFromFile("../data/products.txt");
        warehouse.loadFromDatabase();

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
            std::cout << "9. Statistics\n";
            std::cout << "10. Sort By Price\n";
            std::cout << "11. Sort By Quantity\n";
            std::cout << "12. Search By name\n";
            std::cout << "13. Update Product (DB)\n";
            std::cout << "14. Delete Product (DB)\n";
            std::cout << "15. Reload From DB\n";
            std::cout << "0. Exit\n";

            std::cout << "Choose: ";
            // std::cin >> choice;
            choice = Utils::inputInt();

            if (choice == 1) {
                int id;
                std::string name;
                int quantity;
                double price;

                std::cout << "Input ID: ";
                // std::cin >> id;
                id = Utils::inputInt();

                std::cout << "Input Name: ";
                // std::cin >> name;
                name = Utils::inputString();

                std::cout << "Input Quantity: ";
                // std::cin >> quantity;
                quantity = Utils::inputInt();

                std::cout << "Input Price: ";
                // std::cin >> price;
                price = Utils::inputDouble();

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
                // std::cin >> id;
                id = Utils::inputInt();

                Product* product = warehouse.findProduct(id);

                if (product == nullptr)
                    std::cout << "Product not found!\n";
                else
                    product -> display();
            }

            else if (choice == 4) {
                if (currentUser -> getRole() != "admin") {
                    std::cout << "Promission denied\n";
                    continue;
                }

                int id;

                std::cout << "Input Product ID: ";
                // std::cin >> id;
                id = Utils::inputInt();

                if (warehouse.deleteProduct(id))
                    std::cout << "Product deleted!\n";
                else
                    std::cout << "Product not found!\n";
            }

            else if (choice == 5) {
                if (currentUser -> getRole() != "admin") {
                    std::cout << "Promission denied\n";
                    continue;
                }

                int id;
                std::string name;
                int quantity;
                double price;

                std::cout << "Input Product ID: ";
                // std::cin >> id;
                id = Utils::inputInt();

                std::cout << "Input Name: ";
                // std::cin >> name;
                name = Utils::inputString();

                std::cout << "Input Quantity: ";
                // std::cin >> quantity;
                quantity = Utils::inputInt();

                std::cout << "Input Price: ";
                // std::cin >> price;
                price = Utils::inputDouble();

                if (warehouse.updateProduct(id, name, quantity, price))
                    std::cout << "Product Updated!\n";
                else
                    std::cout << "Product not found!\n";
            }

            else if (choice == 6) {
                int id;
                int amount;

                std::cout << "Input Product ID: ";
                // std::cin >> id;
                id = Utils::inputInt();

                std::cout << "Input Amount: ";
                // std::cin >> amount;
                amount = Utils::inputInt();

                if (warehouse.stockIn(id, amount))
                    std::cout << "Stock in success!\n";
                else
                    std::cout << "Product not found!\n";
            }

            else if (choice == 7) {
                int id;
                int amount;

                std::cout << "Input Product ID: ";
                // std::cin >> id;
                id = Utils::inputInt();

                std::cout << "Input Amount: ";
                // std::cin >> amount;
                amount = Utils::inputInt();

                if (warehouse.stockOut(id, amount))
                    std::cout << "Stock out success!\n";
                else
                    std::cout << "Product not failed!\n";
            }

            else if (choice == 8)
                warehouse.saveToFile("../data/products.txt");

            else if (choice == 9) {
                std::cout << "\n===== Statistics =====\n";
                std::cout << "Total Products: " << warehouse.getTotalProducts() << std::endl;

                std::cout << "Total Inventory Value: " << warehouse.getTotalValue() << std::endl;

                std::cout << "\nLow Stock Products: " << std::endl;
                warehouse.showLowStockProducts(5);
            }

            else if (choice == 10) {
                warehouse.sortByPrice();
                warehouse.showProducts();
            }

            else if (choice == 11) {
                warehouse.sortByQuantity();
                warehouse.showProducts();
            }

            else if (choice == 12) {
                std::string name;
                std::cout << "Input product name: ";
                // std::cin >> name;
                name = Utils::inputString();
                warehouse.searchByName(name);
            }

            else if (choice == 13) {
                int id;
                std::string name;
                int quantity;
                double price;

                std::cout << "ID: ";
                std::cin >> id;

                std::cout << "New Name: ";
                std::cin >> name;

                std::cout << "New Quantity: ";
                std::cin >> quantity;

                std::cout << "New Price: ";
                std::cin >> price;

                if (warehouse.updateProductInDB(id, name, quantity, price))
                    std::cout << "Updated successfully!\n";
            }

            else if (choice == 14) {
                int id;

                std::cout << "ID: ";
                std::cin >> id;

                if (warehouse.deleteProductFromDB(id))
                    std::cout << "Deleted successfully!\n";
            }

            else if (choice == 15)
                warehouse.loadFromDatabase();

            else if (choice == 0) {
                // 退出并自动保存
                warehouse.saveToFile("../data/products.txt");

                std::cout << "Bye!\n";
                break;
            }

            else
                std::cout << "Invalid Choice!\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "System Error: " << e.what() << std::endl;
    }
    return 0;
}