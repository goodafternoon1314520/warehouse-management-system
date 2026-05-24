#include <../include/Logger.h>

#include <fstream>
#include <ctime>

std::string Logger::getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return std::string(dt);
}

void Logger::log(const std::string& message) {
    std::ofstream fout("../data/logs.txt", std::ios::app);

    if (!fout)
        return;

    fout << "[" << getCurrentTime() << "]";
    fout << message << std::endl;
    fout << "-------------------------\n";
    fout.close();
}