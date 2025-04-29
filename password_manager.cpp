#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "password_manager.h"

void PasswordManager::run()
{
    int choice;
    do
    {
        showMenu();
        std::cin >> choice;
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
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Not a valid choice.\n";
        }
    }
    while (choice != 5);
}

void PasswordManager::showMenu()
{
    std::cout << "\n=== Password Manager ===\n";
    std::cout << "1. Add password\n";
    std::cout << "2. View passwords\n";
    std::cout << "3. Delete password\n";
    std::cout << "4. Save passwords\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice ";
}

void PasswordManager::addPassword()
{
    std::string website, username, password;
    std::cin.ignore(); // Clear input buffer

    std::cout << "Enter website: ";
    getline(std::cin, website);

    std::cout << "Enter username: ";
    getline(std::cin, username);

    std::cout << "Enter password: ";
    getline(std::cin, password);

    std::ofstream file("passwords.txt", std::ios::app); // Append mode
    if (file.is_open())
    {
        file << website << ',' << encrypt(username) << ',' << encrypt(password) << '\n';
        file.close();
        std::cout << "Password saved successfully.\n";
    }
    else
    {
        std::cerr << "Error opening file for writing.\n";
    }
}

void PasswordManager::viewPasswords()
{
    std::ifstream file("passwords.txt");
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "No saved passwords found.\n";
        return;
    }

    std::cout << "\n--- Saved Passwords ---\n";
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string website, username, password;

        getline(ss, website, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');

        std::cout << "Website: " << website << "\n";
        std::cout << "Username: " << decrypt(username) << "\n";
        std::cout << "Password: " << decrypt(password) << "\n";
        std::cout << "-----------------------\n";
    }
    file.close();
}

void PasswordManager::deletePassword()
{
    std::string targetWebsite;
    std::cin.ignore();

    std::cout << "Enter website to delete: ";
    getline(std::cin, targetWebsite);

    std::ifstream inFile("passwords.txt");
    std::ofstream outFile("temp.txt");

    bool found = false;
    std::string line;

    if (!inFile.is_open())
    {
        std::cerr << "No saved passwords to delete.\n";
        return;
    }

    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string website;
        getline(ss, website, ',');

        if (website != targetWebsite)
        {
            outFile << line << '\n';
        }
        else
        {
            found = true;
        }
    }
    inFile.close();
    outFile.close();

    remove("passwords.txt");
    rename("temp.txt", "passwords.txt");

    if (found)
        std::cout << "Password deleted successfully.\n";
    else
        std::cout << "No matching website found.";
}

void PasswordManager::savePasswords()
{
    std::cout << "[Save Passwords] - Not yet implemented.\n";
}

std::string PasswordManager::encrypt(const std::string& text)
{
    std::string encrypted = text;
    for (char& c : encrypted)
    {
        c += 3;
    }
    return encrypted;
}

std::string PasswordManager::decrypt(const std::string& text)
{
    std::string decrypted = text;
    for (char& c : decrypted)
    {
        c -= 3;
    }
    return decrypted;
}
