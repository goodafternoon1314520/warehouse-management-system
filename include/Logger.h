#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    // 写日志
    static void log(const std::string& message);

    // 获取当前时间
    static std::string getCurrentTime();
};

#endif