#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <string>

#include "Product.h"

class Warehouse {
private:
    std::vector<Product> products;

public:
    // 添加商品
    void addProduct(const Product& product);

    // 显示商品
    void showProducts() const;

    // 保存文件
    void saveToFile(const std::string& filename);

    // 家在文件
    void loadFromFile(const std::string& filename);
};

#endif