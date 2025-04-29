#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "password_manager.h"

using namespace std;

void PasswordManager::run()
{
    int choice;
    do
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            addPassword();
            break;
        case 2:
            viewPasswords();
            break;
        case 3:
            deletePassword();
            break;
        case 4:
            savePasswords();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Not a valid choice.\n";
        }
    }
    while (choice != 5);
}

void PasswordManager::showMenu()
{
    cout << "\n=== Password Manager ===\n";
    cout << "1. Add password\n";
    cout << "2. View passwords\n";
    cout << "3. Delete password\n";
    cout << "4. Save passwords\n";
    cout << "5. Exit\n";
    cout << "Enter your choice ";
}

void PasswordManager::addPassword()
{
    string website, username, password;
    cin.ignore(); // Clear input buffer

    cout << "Enter website: ";
    getline(cin, website);

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    ofstream file("passwords.txt", ios::app); // Append mode
    if (file.is_open())
    {
        file << website << ',' << username << ',' << password << '\n';
        file.close();
        cout << "Password saved successfully.\n";
    }
    else
    {
        cerr << "Error opening file for writing.\n";
    }
}

void PasswordManager::viewPasswords()
{
    ifstream file("passwords.txt");
    string line;

    if (!file.is_open())
    {
        cerr << "No saved passwords found.\n";
        return;
    }

    cout << "\n--- Saved Passwords ---\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        string website, username, password;

        getline(ss, website, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');

        cout << "Website: " << website << "\n";
        cout << "Username: " << username << "\n";
        cout << "Password: " << password << "\n";
        cout << "-----------------------\n";
    }
    file.close();
}

void PasswordManager::deletePassword()
{
    cout << "[Delete Password] - Not yet implemented.\n";
}

void PasswordManager::savePasswords()
{
    cout << "[Save Passwords] - Not yet implemented.\n";
}
