

#ifndef SYSTEM_ADMIN_H
#define SYSTEM_ADMIN_H
#include <string>
class Admin {
public:
    std::string adminId;
    std::string name;
    std::string password;

    Admin(std::string id, std::string n, std::string pwd);

    bool verifyPassword(const std::string& pwd) const;
    void displayInfo() const;
    std::string serialize() const;
    static Admin deserialize(const std::string& data);
};



#endif //SYSTEM_ADMIN_H
