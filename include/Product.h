#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

class Product {
private:
    int id;
    std::string name;
    int quantity;
    double price;

public:
    // 构造函数
    Product();

    Product(int id, std::string name, int quantity, double price);

    // 设置数据
    void setProduct(int id, std::string name, int quantity, double price);

    // 显示商品
    void display() const;

    // Getter
    int getId() const;
    std::string getName() const;
    int getQuantity() const;
    double getPrice() const;

    // 增加库存
    void increaseQuantity(int amount);

    // 减少库存
    bool decreaseQuantity(int amount);
};

#endif