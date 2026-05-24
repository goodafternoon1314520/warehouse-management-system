#include "../include/Product.h"

Product::Product() {
    id = 0;
    name = "";
    quantity = 0;
    price = 0.0;
}

Product::Product(int id, std::string name, int quantity, double price) {
    this -> id = id;
    this -> name = name;
    this -> quantity = quantity;
    this -> price = price;
}

void Product::setProduct(int id, std::string name, int quantity, double price) {
    this -> id = id;
    this -> name = name;
    this -> quantity = quantity;
    this -> price = price;
}

void Product::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "--------------------------" << std::endl;
}

int Product::getId() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

int Product::getQuantity() const {
    return quantity;
}

double Product::getPrice() const {
    return price;
}