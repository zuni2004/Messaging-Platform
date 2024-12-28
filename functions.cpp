#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

string userName;
string passWord;

void changePassword(string &password) {
    cout << "Enter your password and change the previous one\n";
    cin >> password;

}

bool strongPassword(string &password) {
    bool upperCase = false;
    bool specialChar = false;
    bool digitNum = false;
    if (password.length() >= 8) {
        for (char c: password) {
            if (c >= 'A' && c <= 'Z') {
                upperCase = true;
            } else if (c >= '0' && c <= '9') {
                digitNum = true;
            } else if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' ||
                       c == '(' || c == ')' ||
                       c == '+' || c == '=' ||
                       c == '/' || c == '`' ||
                       c == '~') {
                specialChar = true;
            }
        }
    } else {
        cout << "Password should at least have 8 characters\n";
    }
    if (upperCase && digitNum && specialChar) {
        cout << "Password is strong\n";
        cout << endl;
        return true;
    } else {
        cout << "Password isn't strong enough\nIt should have atleast one Upper case, special and digit character\n";
        cout << endl;
    }
    return false;
}

void saveTheUsers(User user[], int maxUsers) {
    ofstream userList("UserList.txt", ios::app);
    if (userList.is_open()) {
//        userList << "|SN|" << "User Name|" << "User Id|" << "User password|" << endl;
        for (int i = 0; i < maxUsers; i++) {
            userList << user[i].userNum << "\t" << user[i].username << "\t" << user[i].password << "\t"
                     << endl;
        }
        userList.close();
    } else {
        cout << "File hasn't opened \n";
    }

}

void createAccount(User user[], int maxUsers) {
    for (int i = 0; i < maxUsers; i++) {
        user[i].userNum = i + 1;
        cout << "Enter a username for your account: ";
        cin >> user[i].username;
        cout << "Enter a password for your account:";
        cin >> user[i].password;
        while (!strongPassword(user[i].password)) {
            cout << "Change your Password\n";
            changePassword(user[i].password);
        }
    }
    saveTheUsers(user, maxUsers);
}

void changePassword2(User user[], int maxUsers) {
    cout << "Login first to change the password\n";
    cout << "Enter your username: ";
    cin >> userName;
    cout << "Enter your password: ";
    cin >> passWord;
    ifstream password("UserList.txt");
    while (!password.is_open()) {
        cout << "File isn't opening\n";
        break;
    }
    bool same = false;
    for (int i = 0; i < maxUsers; i++) {
        password >> user[i].userNum >> user[i].username >> user[i].password;
        if (userName == user[i].username && passWord == user[i].password) {
            same = true;
            cout << "Login succesful\n";
            break;
        }
    }
    password.close();
    if (same) {
        changePassword(user[maxUsers].password);
        saveTheUsers(user, maxUsers);
    } else {
        cout << "Incorrect Login id\n";
    }
}

void addContact(Contacts contacts[], int &contactCount, int maxContacts, User users[], int maxUsers) {
    cout << "Login first\n";
    cout << "Enter your username: ";
    cin >> userName;
    cout << "Enter your password: ";
    cin >> passWord;
    ifstream password("UserList.txt");
    if (!password.is_open()) {
        cout << "File isn't opening\n";
        return;
    }
    bool same = false;
    int userIndex = -1;
    for (int i = 0; i < maxUsers; i++) {
        password >> users[i].userNum >> users[i].username >> users[i].password;
        if (userName == users[i].username && passWord == users[i].password) {
            same = true;
            userIndex = i;
            cout << "Login successful\n";
            break;
        }
    }
    password.close();
    if (same) {
        if (contactCount == maxContacts) {
            cout << "You have reached the maximum number of contacts.\n";
            return;
        }
        Contacts newContact;
        cout << "Enter the name of the contact: ";
        cin.ignore();
        getline(cin, newContact.name);
        cout << "Enter the number of phone numbers you want to add: ";
        cin >> newContact.phoneCount;
        if (newContact.phoneCount < 0) {
            cout << "Invalid input.\n";
            return;
        }
        newContact.phoneNumbers = new string[newContact.phoneCount];
        for (int i = 0; i < newContact.phoneCount; i++) {
            cout << "Enter phone number " << i + 1 << ": ";
            cin >> newContact.phoneNumbers[i];
        }
        cout << "Enter the number of emails: ";
        cin >> newContact.emailCount;
        if (newContact.emailCount < 0) {
            cout << "Invalid input.\n";
            return;
        }
        newContact.emails = new string[newContact.emailCount];
        for (int i = 0; i < newContact.emailCount; i++) {
            cout << "Enter email no. " << i + 1 << ": ";
            cin >> newContact.emails[i];
        }
        cout << "Enter the number of addresses: ";
        cin >> newContact.addressCount;
        if (newContact.addressCount < 0) {
            cout << "Invalid input.\n";
            return;
        }
        newContact.addresses = new string[newContact.addressCount];
        for (int i = 0; i < newContact.addressCount; i++) {
            cout << "Enter address " << i + 1 << ": ";
            cin.ignore();
            getline(cin, newContact.addresses[i]);
        }
        newContact.messageCount = 0;
        newContact.messages = nullptr;
        contacts[contactCount] = newContact;
        contactCount++;
        saveTheContacts(contacts, contactCount);
        cout << "Contact created successfully.\n";
    } else {
        cout << "Incorrect Login id\n";
    }
}

void deleteContact(Contacts contacts[], int &contactCount, int maxContacts, User users[], int maxUsers) {
    cout << "Login first\n";
    cout << "Enter your username: ";
    cin >> userName;
    cout << "Enter your password: ";
    cin >> passWord;
    ifstream password("UserList.txt");
    if (!password.is_open()) {
        cout << "File isn't opening\n";
        return;
    }
    bool same = false;
    int userIndex = -1;
    for (int i = 0; i < maxUsers; i++) {
        password >> users[i].userNum >> users[i].username >> users[i].password;
        if (userName == users[i].username && passWord == users[i].password) {
            same = true;
            userIndex = i;
            cout << "Login successful\n";
            break;
        }
    }
    password.close();
    if (same) {
        string name;
        cout << "Enter the name of the contact to delete: ";
        cin.ignore();
        getline(cin, name);
        ifstream file("ContactList.txt");
        if (!file.is_open()) {
            cout << "File isn't opened\n";
        }
        int index = -1;
        for (int i = 0; i < contactCount; i++) {
            for (int j = 0; j < 2; j++) {
                file >> contacts[i].name;
                if (contacts[i].name == name) {
                    index = i;
                    cout << "Contact found\n";
                    break;
                }
            }
        }
        if (index == -1) {
            cout << "Contact not found.\n";
            return;
        }
        for (int i = index; i < contactCount - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        delete[] contacts[contactCount - 1].phoneNumbers;
        delete[] contacts[contactCount - 1].emails;
        delete[] contacts[contactCount - 1].addresses;
        delete[] contacts[contactCount - 1].messages;
        contactCount--;
        cout << "Contact deleted successfully.\n";
        saveTheContacts(contacts, contactCount);
    } else {
        cout << "Incorrect Login id\n";
    }
}

void saveTheContacts(Contacts contacts[], int contactCount) {
    ofstream file("ContactList.txt", ios::app);
    if (file.is_open()) {
        for (int i = 0; i < contactCount; i++) {
            file << contacts[i].name << "\t" << contacts[i].phoneCount << "\t";
            for (int j = 0; j < contacts[i].phoneCount; j++) {
                file << contacts[i].phoneNumbers[j] << "\t";
            }
            file << contacts[i].emailCount << "\t";
            for (int j = 0; j < contacts[i].emailCount; j++) {
                file << contacts[i].emails[j] << "\t";
            }
            file << contacts[i].addressCount << "\t";
            for (int j = 0; j < contacts[i].addressCount; j++) {
                file << contacts[i].addresses[j] << "\t";
            }
            file << contacts[i].messageCount << "\n";
        }
        file.close();
        cout << "Data saved successfully.\n";
    } else {
        cout << "Error in opening file.\n";
    }
}

