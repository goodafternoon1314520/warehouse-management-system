#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    // 安全输入整数
    static int inputInt();

    // 安全输入double
    static double inputDouble();

    // 安全输入字符串
    static std::string inputString();
};

#endif