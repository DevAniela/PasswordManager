#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H
#include <string>

class PasswordManager
{
public:
    void run();
    void addPassword();
    void viewPasswords();
    void deletePassword();
    void savePasswords();
private:
    void showMenu();
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
};

#endif
