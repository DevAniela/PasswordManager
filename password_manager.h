#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

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
};

#endif
