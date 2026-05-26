#ifndef TOKENMANAGER_H
#define TOKENMANAGER_H

#include <string>
#include <unordered_map>

class TokenManager {
private:
    std::unordered_map<std::string, std::string> tokenMap;

public:
    // 生成token
    std::string generateToken(const std::string& username);

    // 验证token
    bool validateToken(const std::string& token);

    // 获取用户名
    std::string getUsername(const std::string& token);
};

#endif