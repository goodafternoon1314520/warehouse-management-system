#include "../include/UserManager.h"

#include <fstream>

void UserManager::loadUsers(const std::string& filename) {
    std::ifstream fin(filename);

    if (!fin)
        return;

    std::string username;
    std::string password;
    std::string role;

    while (fin >> username >> password >> role) {
        User user(username, password, role);
        users.push_back(user);
    }
    fin.close();
}

User* UserManager::login(std::string username, std::string password) {
    for (auto& user : users) {
        if (user.login(username, password))
            return &user;
    }
    return nullptr;
}