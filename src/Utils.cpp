#include "../include/Utils.h"

#include <iostream>
#include <limits>

int Utils::inputInt() {
    int value;

    while (true) {
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please enter an integer: ";
        }
        else
            return value;
    }
}

double Utils::inputDouble() {
    double value;

    while (true) {
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please enter an number: ";
        }
        else
            return value;
    }
}

std::string Utils::inputString() {
    std::string value;
    std::cin >> value;

    return value;
}