#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>

class PasswordManager
{
public:
    void run();
private:
    void showMenu();
    void addPassword();
    void viewPasswords();
    void deletePassword();
    void savePasswords();
};

#endif
