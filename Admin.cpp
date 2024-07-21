
#include "Admin.h"
#include <iostream>
#include <sstream>

Admin::Admin(std::string id, std::string n, std::string pwd)
        : adminId(id), name(n), password(pwd) {}

bool Admin::verifyPassword(const std::string& pwd) const {
    return password == pwd;
}

void Admin::displayInfo() const {
    std::cout << "Admin ID: " << adminId << "\n"
              << "Name: " << name << "\n";
}

std::string Admin::serialize() const {
    std::ostringstream oss;
    oss << adminId << "," << name << "," << password;
    return oss.str();
}

Admin Admin::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string id, name, pwd;
    std::getline(iss, id, ',');
    std::getline(iss, name, ',');
    std::getline(iss, pwd, ',');
    return Admin(id, name, pwd);
}
