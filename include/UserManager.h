#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>

#include "User.h"

class UserManager {
private:
    std::vector<User> users;

public:
    // 加载用户
    void loadUsers(const std::string& filename);

    // 登录
    User* login(std::string username, std::string password);
};

#endif