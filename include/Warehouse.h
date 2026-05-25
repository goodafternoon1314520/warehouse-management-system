#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <string>

#include "Product.h"
#include "Database.h"

class Warehouse {
private:
    std::vector<Product> products;

    Database database;

public:
    // 添加商品
    bool addProduct(const Product& product);

    // 显示商品
    void showProducts() const;

    // 保存文件
    void saveToFile(const std::string& filename);

    // 加载文件
    // void loadFromFile(const std::string& filename);
    void loadFromDatabase();

    // 查找商品
    Product* findProduct(int id);

    // 删除商品
    bool deleteProduct(int id);

    // 修改商品
    bool updateProduct(int id, std::string name, int quantity, double price);

    // 商品入库
    bool stockIn(int id, int amount);

    // 商品出库
    bool stockOut(int id, int amount);

    // 商品总数
    int getTotalProducts() const;

    // 仓库总价值
    double getTotalValue() const;

    // 显示低库存商品
    void showLowStockProducts(int threshold) const;

    // 按价格排序
    void sortByPrice();

    // 按库存排序
    void sortByQuantity();

    // 按名称搜索
    void searchByName(const std::string& name);

    Warehouse();
};

#endif