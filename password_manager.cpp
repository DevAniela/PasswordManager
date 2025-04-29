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
        file << website << ',' << encrypt(username) << ',' << encrypt(password) << '\n';
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
        cout << "Username: " << decrypt(username) << "\n";
        cout << "Password: " << decrypt(password) << "\n";
        cout << "-----------------------\n";
    }
    file.close();
}

void PasswordManager::deletePassword()
{
    string targetWebsite;
    cin.ignore();

    cout << "Enter website to delete: ";
    getline(cin, targetWebsite);

    ifstream inFile("passwords.txt");
    ofstream outFile("temp.txt");

    bool found = false;
    string line;

    if (!inFile.is_open())
    {
        cerr << "No saved passwords to delete.\n";
        return;
    }

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string website;
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
        cout << "Password deleted successfully.\n";
    else
        cout << "No matching website found.";
}

void PasswordManager::savePasswords()
{
    cout << "[Save Passwords] - Not yet implemented.\n";
}

string PasswordManager::encrypt(const string& text)
{
    string encrypted = text;
    for (char& c : encrypted)
    {
        c += 3;
    }
    return encrypted;
}

string PasswordManager::decrypt(const string& text)
{
    string decrypted = text;
    for (char& c : decrypted)
    {
        c -= 3;
    }
    return decrypted;
}
