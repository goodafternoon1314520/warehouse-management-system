#include "../include/TokenManager.h"

#include <ctime>

std::string TokenManager::generateToken(const std::string& username) {
    std::string token = username + "_" + std::to_string(time(0));
    tokenMap[token] = username;

    return token;
}

bool TokenManager::validateToken(const std::string& token) {
    return tokenMap.find(token) != tokenMap.end();
}

std::string TokenManager::getUsername(const std::string& token) {
    return tokenMap[token];
}