#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

const int maxUsers = 100;
User user[maxUsers];
int contactCount = 0;
const int maxContacts = 5;
const int maxMessages = 10;
Contacts contacts[maxContacts];

int main() {
    int choice;
    cout << "MESSAGING PLATFORM\n";
    cout << "1. Create an account\n";
    cout << "2. Change Password\n";
    cout << "3. Add Contact\n";
    cout << "4. Delete Contacts\n";
    cout << "5. View Contacts\n";
    cout << "6. View Messages\n";
    cout << "7. Send messages\n";
    cout << "8. Search Contacts\n";
    cout << "9. Exit\n";
    cin >> choice;
    switch (choice) {
        case 1: {
            createAccount(user, maxUsers);
            break;
        }
        case 2: {
            changePassword2(user, maxUsers);
            break;
        }
        case 3: {
            addContact(contacts, contactCount, maxContacts, user, maxUsers);
            break;
        }
        case 4: {
            deleteContact(contacts, contactCount, maxContacts, user, maxUsers);
            break;
        }
//        case 5: {
//            viewContacts(contacts, contactCount);
//            break;
//        }
//        case 6: {
//            viewMessage(contact, user, maxUsers);
//            break;
//        }
//        case 7: {
//            addMessage(contact, user, maxUsers, message);
//            break;
//        }
//        case 8: {
//            searchContact(contacts, name, start, end);
//        }
        default: {
            cout << "Exiting the Platform\n";
            break;
        }
    }
    return 0;
}