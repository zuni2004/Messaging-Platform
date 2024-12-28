#ifndef PRACTICE_TEMPLATE_FUNCTIONS_H
#define PRACTICE_TEMPLATE_FUNCTIONS_H

#include <string>

using namespace std;
//const int maxContacts = 2;
//const int maxMessages = 50;


struct Contacts {
    string name;
    string *phoneNumbers;
    int phoneCount;
    string *emails;
    int emailCount;
    string *addresses;
    int addressCount;
    string *messages;
    int messageCount;
};

struct User {
    int userNum;
    string username;
    string password;
//    Contacts *contacts[maxContacts];
};
//string userName;
//string passWord;

void createAccount(User user[], int maxUsers);

void changePassword2(User user[], int maxUsers);

void login(User user[], int maxUsers);

void addContact(Contacts contacts[], int &contactCount, int maxContacts, User users[], int maxUsers);

void deleteContact(Contacts contacts[], int &contactCount, int maxContacts, User users[], int maxUsers);

void saveTheContacts(Contacts contacts[], int contactCount);

//void viewMessage(Contacts contact[], User user[], int maxUsers);
//
//void addMessage(Contacts &contact, User user[], int maxUsers, string message);
//
//int searchContact(Contacts contacts[], string name, int start, int end);

#endif //PRACTICE_TEMPLATE_FUNCTIONS_H
