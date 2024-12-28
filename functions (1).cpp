
// Created by InnoSTARK on 11/16/2023.
#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int PASSWORD=20;
struct User{
    int cnt;
    string username;
    char password[PASSWORD];
    string email;
    int phone;
};
User new1;
static int emal=0;
static int adres=0;
static int saved=0;
template <typename T>
bool check(const T& value) {//to check if number already exists or not using template
    ifstream file("account");
    if (!file.is_open()) {
        cout<<"Error opening the file"<<endl;
        return false;
    }
    int n;
    T fileValue;
    while (file>>n>>fileValue) {
        if (fileValue==value) {
            file.close();
            return true;
        }
        char c;
        while (file.get(c) && c != '\n');
    }
    file.close();
    return false;
}
bool checking(string value){//to check if email already exists or not
    ifstream file("account");
    if (!file.is_open()) {
        cout<<"Error opening the file"<<endl;
        return false;
    }
    int n;
    int no;
    string fileValue;
    while (file>>n>>no>>fileValue) {
        if (fileValue==value) {
            file.close();
            return true;
        }
        char c;
        while (file.get(c) && c != '\n');
    }
    file.close();
    return false;
}

bool check2(string word) {//this is to check if username already exists or not
    ifstream file("account");
    if (!file.is_open()) {
        cout<< "Error opening the file"<<endl;
        return false;
    }
    int phon;//phone
    string ema;//email
    string user;//username
    int n;//number of accounts registered
    string passy;//password stored
    while(file>>n>>phon>>ema>>user>>passy) {
        if (word==user) {
            file.close();
            cout<<"Username already exists try again"<<endl;
            return true;
        }
    }
    file.close();
    return false;
}
void cnt(){
    string line;
    fstream variable;
    variable.open("account",ios::in);
    new1.cnt=0;
        while(getline(variable,line)){
            new1.cnt++;
        }
    }
bool passwordCheck(char pass[]){//this is to check if password is worthy
    for (int i = 0; pass[i] != '\0'; i++) {
        if (pass[i] == ' ') {
            cout << "Password cannot contain a space." << endl;
            return false;
        }
    }
    int cnt=0;
    bool chuck=false;
    for(int i=0;pass[i]!='\0';i++){
        cnt++;
        if(pass[i]>='0' && pass[i]<='9'){
            chuck=true;
        }
    }
    if(cnt<8 && !chuck){
        cout<<"password doesn't meet its requirements"<<endl;
        return false;
    }
    return true;
}
void setAccount(){//this is for setting account
    cout<<"Please input your contact number"<<endl;
    cin>>new1.phone;
    if(check(new1.phone)){
        cout<<"this number is already registered , please try again"<<endl;
        do{
            cout<<"Please input your contact number"<<endl;
            cin>>new1.phone;
        }
        while(check(new1.phone));
    }
    cout<<"Please input your email id" << endl;
    cin>>new1.email;
    if (checking(new1.email)) {
        cout<<"This email is already registered" << endl;
        do {
            cout<<"Try again"<<endl;
            cout<<"Please input your email id" << endl;
            cin>>new1.email;
        } while (checking(new1.email));
    }
    cout<<"You may now enter your username"<<endl;
    cin>>new1.username;
    if(check2(new1.username)){
        do{
            cout<<"Try again"<<endl;
            cout<<"You may now enter your username"<<endl;
            cin>>new1.username;
        }
        while(check(new1.username));
    }
    cout<<"Enter a password , it must contain 8 characters"
          " including a number at least"
          "maximum number of characters allowed are 20"<<endl;
    cin.getline(new1.password,PASSWORD);
    if(!passwordCheck(new1.password)){
        do{
            cout<<"Enter a password , it must contain 8 characters"
                  " including a number at least"
                  "maximum number of characters allowed are 20"<<endl;
            cin.getline(new1.password,PASSWORD);
        }
        while(!passwordCheck(new1.password));
    }
    fstream variable,variable2;
    variable.open("account",ios::out|ios::app);
    variable2.open("personal",ios::out|ios::app);
    if(!variable && !variable2){
        cout<<"error opening file"<<endl;
    }
    else {
        cnt();
        variable << new1.cnt <<" "<< new1.phone <<" "<<
        new1.email <<" "<< new1.username <<" "<< new1.password << endl;
        variable2<<new1.cnt<<" "<<new1.username<<endl;
    }
    cout<<"Your account has been successfully created"<<endl;
    variable.close();
    variable2.close();
    fstream variable3;
    variable3.open(new1.username+".txt",ios::out);
    variable3<<"";
    variable3.close();
}
bool reset(string mail) {//this is for resetting password
    string mal;
    char nuw[PASSWORD];
    cout << "Please enter your email attached with the username: ";
    cin >> mal;
    if (mal != mail) {
        cout << "Unable to reset password" << endl;
        return false;
    } else {
        cout << "Enter new password: ";
        cin.ignore();
        cin.getline(nuw, PASSWORD);
        if (!passwordCheck(nuw)) {
            do {
                cout << "Enter a password, it must contain 8 characters including a number at least, "
                        "maximum number of characters allowed are 20" << endl;
                cin.getline(nuw, PASSWORD);
            } while (!passwordCheck(nuw));
        }
        fstream variable, variable2;
        variable.open("account", ios::in);
        variable2.open("temp", ios::out | ios::app);
        if (!variable || !variable2) {
            cout << "Not able to open files" << endl;
            return false;
        }
        int n;       // Number of accounts
        int phon;    // Phone number
        string user; // Username
        string pass; // Password
        string inputmail;
        while (variable >> n >> phon >> inputmail >> user >> pass) {
            if (inputmail == mail) {
                variable2 << n << " " << phon << " " << inputmail << " " << user << " " << nuw << endl;
            } else {
                variable2 << n << " " << phon << " " << inputmail << " " << user << " " << pass << endl;
            }
        }
        variable.close();
        variable2.close();
        remove("account");
        rename("temp", "account");
        return true;
    }
}
bool login() {//this is for login
    fstream variable;
    variable.open("account", ios::in);
    cout << "Enter username: ";
    cin >> new1.username;
    string em; // email
    int n;     //number of accounts
    int phon;//phone number
    string user; //username
    string pass; //password
    string mail;
    int cnt = 0; //number of wrong inputs
    char choice; //choice yes or no
    bool loginSuccessful = false;
    while (variable >> n >> phon >>mail>> user >> pass) {
        if (new1.username == user) {
            cout << "Please enter your password: ";
            cin >> new1.password;
            if (new1.password == pass) {
                new1.phone=phon;
                cout << "Successfully logged in" << endl;
                loginSuccessful = true;
                break; //exit loop if login successfuk
            } else {
                do {
                    cout << "Incorrect password entered" << endl;
                    if (cnt >= 3) {
                        cout << "Forgotten password? Would you like to reset? (y/n): ";
                        cin >> choice;
                        if (choice == 'y' || choice == 'Y') {
                            if(!reset(mail)){
                                  loginSuccessful=false;
                                  break;
                            }else{
                                cout << "Password reset successful" << endl;
                                loginSuccessful = true;
                                break; //exit loop
                            }
                        }
                    }
                    cout << "Please enter your password: ";
                    cin >> new1.password;
                    cnt++;
                } while (new1.password != pass);
                loginSuccessful=true;
            }
            break;
        }
    }
    if (!loginSuccessful) {
        cout << "Login failed. User not found or incorrect password." << endl;
    }else{
        cout<<"Successfully logged in"<<endl;
    }
    variable.close(); // Close the file after use
    return loginSuccessful;
}
static int contactCount=0;
void addContacts();
void displayContacts();
void save2file();
void searchInfile();
void removeContact();
void sendmessages();
void clearMemory();
void VIEWmessages();
void menu() {//this is where everything is called
    int choice;
    do {
        cout << "\n Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        switch (choice) {
            case 1:
                setAccount();
                break;
            case 2: {
                if (login()) {
                    int choice2;
                    do {
                        cout << "1. Add Contact" << endl;
                        cout << "2. Display recently added contacts" << endl;
                        cout << "3. Search contact" << endl;
                        cout << "4. Remove contact " << endl;
                        cout << "5.Send messages" << endl;//make a file for other person
                        cout << "6.View message history" << endl;
                        cout << "7. Log out" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice2;
                        switch (choice2) {
                            case 1: {
                                addContacts();
                                break;
                            }
                            case 2: {
                                displayContacts();
                                break;
                            }
                            case 3: {
                                cout<<"already saved"<<endl;
                                break;
                            }
                            case 4: {
                                removeContact();
                                break;
                            }
                            case 5: {
                                sendmessages();
                                break;
                            }
                            case 6: {
                                cout<<endl;
                                VIEWmessages();
                                break;
                            }
                            default: {
                                cout << "Invalid choice. Please try again"<<endl;
                            }
                        }
                    } while (choice2 != 7);
                    clearMemory();
                    cout << "Logging out"<<endl;
                    saved=0;
                    emal=0;
                    adres=0;
                    contactCount=0;
                }
                break;
            }
            case 3:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}
const int maxlines=4;
const int MAXCONTACTS=100;
const int CONTACTS = 100;

const int EMAILS = 5;
const int ADDRESSES = 5;
static int nomber=0;//number of contacts stored in total

struct Contact {
    string name;
    int phoneNumbers;
    string* emails;
    string* addresses;
};
Contact *arr[MAXCONTACTS];
bool ask(){
    char c;
    cout<<"would u like to add more y/n"<<endl;
    cin>>c;
    if(c=='y'||c=='Y'){
        return true;
    }
    return false;
}
bool isPhoneNumberAlreadyStored(const int& phoneNumber) {
    for (int i = 0; i < contactCount; ++i) {
        if (arr[i]->phoneNumbers == phoneNumber) {
            return true;
        }
    }
    return false;
}
bool isAlreadyStoredInFile(const int& phoneNumber){
    fstream variable;
    variable.open(new1.username+".txt",ios::in);
    int n, number;
    string name;
    string space;
    while(variable>>n>>name>>number){
        if(number==phoneNumber){
            return true;
        }
        getline(variable,space);
        for(int i=0;i<maxlines;i++){
            string dummy;
            getline(variable,dummy);
        }
    }
    return false;
}
//this is crucial for messaging
struct other{
    string username;
};
other use;
bool checkIfpersonACC(int phone){//check if person has account on this platform
    //check if that phone number exists in account , if it does
    //write in that file , this person's info and everything
    //write sent in recieved
    fstream variable;
    variable.open("account",ios::in);
    int phon;//phone
    string ema;//email
    string user;//username
    int n;//number of accounts registered
    string pass;//password stored
    while(variable>>n>>phon>>ema>>user>>pass) {
        if (phone==phon) {
            use.username=user;
            variable.close();
            return true;
        }
    }
    variable.close();
    return false;
}
//crucial for messaging
void addContacts() {
    if(contactCount>MAXCONTACTS){
        cout<<"unable to store anymore contacts"<<endl;
    }
    arr[contactCount]=new Contact;
    cout<<"Enter contact name: ";
    cin.ignore();
    getline(cin, arr[contactCount]->name);
    do {
        cout << "Enter phone number: ";
        cin >> arr[contactCount]->phoneNumbers;
        if (checkIfpersonACC(arr[contactCount]->phoneNumbers)) {
            if (isPhoneNumberAlreadyStored(arr[contactCount]->phoneNumbers) ||
                isAlreadyStoredInFile(arr[contactCount]->phoneNumbers)) {
                cout << "Phone number already exists. Please enter a different phone number." << endl;
            }
        }else{
            cout<<"This phone number doesn't have an account on here"<<endl;
            return;
        }
    }
        while (isPhoneNumberAlreadyStored(arr[contactCount]->phoneNumbers));
    arr[contactCount]->emails=new string[EMAILS];
    cout << "Enter emails:\n";
    for (int i =0;i<EMAILS;i++) {
        cout<<"  Email " << i + 1<< ": ";
        cin>>arr[contactCount]->emails[i];
        emal++;
        if (!ask()) {
            break;
        }
    }
    arr[contactCount]->addresses = new string[ADDRESSES];
    cout << "Enter addresses:\n";
    for(int i=0;i<ADDRESSES;i++) {
        cout<< "  Address " << i + 1 << ": ";
        cin>>arr[contactCount]->addresses[i];
        adres++;
        if(!ask()) {
            break;
        }
    }
    contactCount++;
    save2file();
}
void displayContacts(){
    for (int i = 0; i < contactCount; i++) {
        cout << "Contact " << i + 1 << endl;
        cout << "Name: " << arr[i]->name << endl;
        cout << "Phone Numbers:"<<endl;
            cout << arr[i]->phoneNumbers<<endl;
        cout << "Emails:"<<endl;
        for (int j=0;j<emal; j++) {
            cout <<arr[i]->emails[j] << endl;
        }
        cout << "Addresses:"<<endl;
        for (int j=0;j<adres;j++) {
            cout <<arr[i]->addresses[j] << endl;
        }
        cout << endl;
    }
}
void save2file() {
    fstream outFile(new1.username + ".txt", ios::out | ios::app);
    int cnt=0;
    for (int i=saved; i < contactCount; i++) {
        cnt++;
        cout<<"Storing contact no. "<<i+1<<"  by the name "<<arr[i]->name<<" "<<endl;
        outFile<<i+1<<" "<< arr[i]->name << " "<< arr[i]->phoneNumbers<<endl;
        for (int j = 0; j < emal; j++) {
            outFile<<arr[i]->emails[j]<<" ";
        }
        outFile <<endl;
        for (int j = 0; j < adres; j++) {
            outFile<< arr[i]->addresses[j]<<" ";
        }
        outFile<<endl;
        outFile <<"recieved="<< endl;
        outFile<<"sent="<<endl;
    }
    saved+=cnt;
    outFile.close();
}
void displayInfo(int n, const string& name,const int& number, ifstream& infile) {
    cout<<endl;
    cout << "Displaying info for " << endl;
    cout << "Contact no. " <<n<< " named " <<name<<" with phone number: "<<number<<endl;
    string space;
    getline(infile, space);
    string email;
    getline(infile, email);
    cout<<"Email/s: "<<email<<endl;
    string address;
    getline(infile, address);
    cout<<"Address/es: "<<address<<endl;
}
bool recursiveSearch(ifstream& infile,const string& search) {
    int n;
    string name;
    string space;
    int number;
    if(infile>>n>>name>>number) {
        if(name==search) {
            displayInfo(n, search, number, infile);
            return true;
        }
        getline(infile,space);
        for(int i=0;i<maxlines;i++) {
            string dummy;
            getline(infile, dummy);
        }
        return recursiveSearch(infile, search);
    }
    return false;
}
void searchInfile() {
    ifstream infile(new1.username+".txt");
    if(!infile.is_open()) {
        cout<<"Unable to open file, or file doesn't exist" <<endl;
        return;
    }
    string search;
    cout<<"Enter the name you would like to search: ";
    cin.ignore();
    getline(cin, search);
    if (!recursiveSearch(infile, search)) {
        cout<<search<<"doesn't exist."<< endl;
    }
    infile.close();
}
void clearMemory() {
    for (int i = 0; i < contactCount; ++i) {
        delete arr[i];
        delete[] arr[i]->emails;
        delete[] arr[i]->addresses;
    }
    contactCount = 0;
}
void removeContact(){
    ifstream file(new1.username + ".txt");
    if (!file) {
        cout << "Unable to open file, or file doesn't exist" << endl;
        return;
    }
    string inputName;
    cout << "Please type in the name of the contact you would like to remove: " << endl;
    cin >> inputName;
    // Create a temporary file
    ofstream file2(new1.username + "_temp.txt");
    if (!file2) {
        cout << "Unable to create temporary file" << endl;
        return;
    }
    bool contactFound = false;
    int n;
    string name;
    int number;
    string space;
    while (file >> n >> name >>number) {
        if (name == inputName) {
            getline(file,space);
            //skip reading the associated data for the contact to be removed
            for (int i = 0; i < maxlines; i++) {
                string dum;
                getline(file, dum);
            }
            contactFound = true;
        } else {
            //write data for contacts other than the one to be removed
            file2 << n << " " << name <<" "<< number<<" "<<endl;
            getline(file,space);
            for (int i = 0; i < maxlines; i++) {
                string dummy;
                getline(file, dummy);
                file2 << dummy << endl;
            }
        }
    }
    file.close();
    file2.close();
    if (!contactFound) {
        cout << inputName << " doesn't exist." << endl;
        remove((new1.username + "_temp.txt").c_str());
        return;
    }
    string oldfile = new1.username + "_temp.txt";
    string newfile = new1.username + ".txt";
    if (rename(oldfile.c_str(), newfile.c_str()) != 0) {
        cout << "Error renaming file" << endl;
        return;
    }
    cout << "Contact " << inputName << " removed successfully." << endl;
}
//here starts the messaging module=
bool Ifsaved(int phone) {//check if person has the other persons contact info saved
    ifstream variable;
    variable.open(use.username + ".txt");
    if (!variable.is_open()) {
        cout << "Unable to open file: " << use.username + ".txt" << endl;
        return false;
    }
    int n;
    string line;
    string space;
    int number;
    while (variable >> n >> line >> number) {
        if (number == phone) {
            variable.close();
            return true;
        } else {
            getline(variable,space);
            for (int i = 0; i < maxlines; i++) {
                string dum;
                getline(variable, dum);
            }
        }
    }
    variable.close();
    return false;
}
void writeInOthers(int phone, string messageSent) {//write in others recieved line
    fstream variable, variable2;
    variable.open(use.username + ".txt", ios::in | ios::out);
    variable2.open(use.username + "_temp.txt", ios::out);
    bool contactFound = false;
    int n;
    int number;
    string name;
    string line2;
    string line3;
    string space;
    while (variable >> n >> name >> number) {
        if (phone == number) {
            getline(variable,space);
            string *dummy;
            dummy=new string[2];
            for (int i = 0; i < 2; i++) {
                getline(variable, dummy[i]);
            }
            getline(variable,line2);//here we are getting the recieved line
            getline(variable,line3);//here we are getting the sent line
            variable2 << n << " " << name << " "<<number<<" "<< endl;
            for (int i = 0; i < 2; i++) {
                variable2 << dummy[i] << endl;
            }
            variable2 <<line2<<" | "<<messageSent<< endl;
            variable2 <<line3 << endl;
            contactFound = true;
            delete[] dummy;
        } else {
            variable2 << n << " " << name <<" "<<number<<" "<< endl;
            getline(variable,space);
            for (int i = 0; i < maxlines; i++) {
                string dummy;
                getline(variable, dummy);
                variable2 << dummy << endl;
            }
        }
    }
    variable.close();
    variable2.close();
    if (!contactFound) {
        cout << "Phone number " << phone << " is not saved in the person's file." << endl;
        remove((use.username + "_temp.txt").c_str());
        return;
    }
    string oldfile = use.username + "_temp.txt";
    string newfile = use.username + ".txt";
    if (rename(oldfile.c_str(), newfile.c_str()) != 0) {
        cout << "Error renaming file" << endl;
    }
}
void writeInfile(int phone,string message) {//write in sent line
    fstream variable, variable2;
    variable.open(new1.username + ".txt", ios::in | ios::out);
    variable2.open(new1.username + "_temp.txt", ios::out);
    bool contactFound = false;
    int n;
    int number;
    string name;//first email then address then sent then recieved
    string line2;
    string changed;
    string space;
    while (variable >> n >> name>>number) {
        if (phone == number) {
            string *dummy;
            dummy=new string[3];
            getline(variable,space);
            for (int i = 0; i < 3; i++) {
                getline(variable, dummy[i]);
            }
            getline(variable,line2);//recieved
            variable2 << n << " " << name <<" "<<number<<" "<< endl;
            for (int i = 0; i < 3; i++) {
                variable2 << dummy[i] << endl;
            }
            variable2 << line2 << " | " << message << endl;
            contactFound = true;
            delete[] dummy;
        } else {
            variable2 << n << " " << name <<" "<<number<<" "<< endl;
            getline(variable,space);
            for (int i = 0; i < maxlines; i++) {
                string dummy;
                getline(variable, dummy);
                variable2 << dummy << endl;
            }
        }
    }
    variable.close();
    variable2.close();
    if (!contactFound) {
        cout << "phone number " << phone << " is wrong." << endl;
        remove((new1.username + "_temp.txt").c_str());
        return;
    }
    string oldfile = new1.username + "_temp.txt";
    string newfile = new1.username + ".txt";
    if (rename(oldfile.c_str(), newfile.c_str()) != 0) {
        cout << "Error renaming file" << endl;
    }
    cout << "message sent successfully" << endl;
}
void sendmessages() {//where everything is called
    ifstream variable;
    string name;
    cout << "Enter the contact name you would like to send a message to " << endl;
    cin>>name;
    cin.ignore();
    variable.open(new1.username + ".txt", ios::in);
    int n;
    string name1;
    int number;
    int cnt = 0;
    string space;
    bool contactFound = false;
    while (variable >> n >> name1 >>number) {
        if (name1 == name) {
            getline(variable,space);
            for (int i = 0; i < 4; i++) {//5 because its also reaing
                // in the line where number is written
                string dum;//change remove contact function
                getline(variable, dum);
            }
            cnt++;
            contactFound = true;
            cout<<"Contact found= "<<endl;
            displayInfo(n, name, number,variable);
        }else{
            getline(variable,space);
            for (int i = 0; i < 4; i++) {//5 because its also reaing
                // in the line where number is written
                string dum;//change remove contact function
                getline(variable, dum);
            }
        }
    }
    variable.close();
    if (cnt >= 2) {
        int selectedContact;
        cout << "Which one of the displayed contacts"
                " would you like to send a message to? "
                "Enter the phone no.: ";
        cin >> selectedContact;
        if (!checkIfpersonACC(selectedContact)) {
            cout << "This person does not have an account on here" << endl;
        } else if (!Ifsaved(new1.phone)) {
            cout << "Person does not have you saved on their account" << endl;
        } else {
                string message;
                cout << "Enter the message you want to send" << endl;
                getline(cin, message);
                writeInfile(selectedContact, message);
                writeInOthers(new1.phone, message);
            }
        }
    else{
        if (!checkIfpersonACC(number)) {
            cout << "This person does not have an account on here" << endl;
            return;
        } else if (!Ifsaved(new1.phone)) {
            cout << "Person does not have you saved on their account" << endl;
            return;
        }else {
            string message;
            cout << "Enter the message you want to send" << endl;
            getline(cin, message);
            writeInfile(number, message);
            writeInOthers(new1.phone, message);
        }
    }
    if(!contactFound){
        cout<<"unable to find contact by that name"<<endl;
    }
}
void VIEWmessages() {
    fstream variable;
    int n, number;
    string name;
    string lines;
    string sent;
    string space;
    string received;
    variable.open(new1.username + ".txt");
    if (!variable.is_open()) {
        cout << "Unable to open the file." << endl;
        return;
    }
    while (variable >> n >> name >> number) {
        getline(variable, space);
        for (int i = 0; i < 2; i++) {
            getline(variable, lines);
        }
        getline(variable, received);
        getline(variable, sent);
        cout << "Message history with " << name << endl;
        cout << received << endl;
        cout << sent << endl;
        cout<<endl;
    }
    variable.close();
}
