#include "../include/User.h"

#include <fstream>

User::User() {

}

User::User(std::string username, std::string password, std::string role) {
    this -> username = username;
    this -> password = password;
    this -> role = role;
}

bool User::login(std::string inputUser, std::string inputPass) {
    return username == inputUser && password == inputPass;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getRole() const {
    return role;
}