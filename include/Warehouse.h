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
    bool addProduct(const Product& product);

    // 显示商品
    void showProducts() const;

    // 保存文件
    void saveToFile(const std::string& filename);

    // 加载文件
    void loadFromFile(const std::string& filename);

    // 查找商品
    Product* findProduct(int id);

    // 删除商品
    bool deleteProduct(int id);

    // 修改商品
    bool updateProduct(int id, std::string name, int quantity, double price);
};

#endif