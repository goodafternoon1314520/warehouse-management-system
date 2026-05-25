#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string role;

public:
    User();

    User(std::string username, std::string password, std::string role);

    // 登录验证
    bool login(std::string inputUser, std::string inputPass);

    // Getter
    std::string getUsername() const;
    std::string getRole() const;
};

#endif