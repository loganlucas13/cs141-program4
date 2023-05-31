/* 
---------------
Project 4
Logan Lucas
CS 141
Fall 2023
Prof. Maratos 
---------------
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class Contact {
    private:
    char contactType;
    
    string firstName;
    string lastName;
    string streetName;
    string city;
    string state;
    string email;
    string dateOfBirth;
    
    int streetNumber;
    int postalCode;

    struct PhoneNumbers {
        string number;
        char phoneType;
    };

    vector<PhoneNumbers> numberList;
        
    public:
    // constructors
    Contact(char contactType, string firstName, string lastName);
    Contact(char contactType, string phoneNumber);

    bool operator<(Contact c);

    // all setters
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setContactType(char contactType);
    void setEmail(string email);
    void setDateOfBirth(string dateOfBirth);
    void setAddress(int streetNumber, string streetName, string city, string state, int postalCode);

    // all getters
    string getFirstName();
    string getLastName();
    string getState();
    string getEmail();
    string getDateOfBirth();
    string getName();
    string getAddress();

    char getContactType();

    // other functions
    string addPhone(char contactType, string number);
    string deletePhone(int index);
    string getAsString();
    string tester();
};

// constructor
Contact::Contact(char contactType, string firstName, string lastName) {
    this->contactType = contactType;
    this->firstName = firstName;
    this->lastName = lastName;
}

// constructor
Contact::Contact(char contactType, string phoneNumber) {
    this->contactType = contactType;
    addPhone(contactType, phoneNumber);
}

// all setters
void Contact::setFirstName(string firstName) {
    this->firstName = firstName;
}

void Contact::setLastName(string lastName) {
    this->lastName = lastName;
}

void Contact::setContactType(char contactType) {
    this->contactType = contactType;
}

void Contact::setEmail(string email) { 
    this->email = email; 
}

void Contact::setDateOfBirth(string dateOfBirth) {
    this->dateOfBirth = dateOfBirth;
}

void Contact::setAddress(int streetNumber, string streetName, string city, string state, int postalCode) {
    this->streetNumber = streetNumber;
    this->streetName = streetName;
    this->city = city;
    this->state = state;
    this->postalCode = postalCode;
}

// all getters
string Contact::getFirstName() {
    return firstName;
}

string Contact::getLastName() {
    return lastName;
}

string Contact::getState() {
    return state;
}

string Contact::getEmail() { 
    return email; 
}

string Contact::getDateOfBirth() {
    return dateOfBirth;
}

char Contact::getContactType() {
    return contactType;
}

string Contact::getName() {
    string output;
    output = lastName + ", " + firstName;
    return output;
}

string Contact::getAddress() {
    string output;
    
    output += to_string(streetNumber) + " ";
    output += streetName + ", ";
    output += city + ", ";
    output += state + " ";
    output += to_string(postalCode);
    
    return output;
}

// adds new phone to contact
string Contact::addPhone(char contactType, string phoneNumber) {
    string displayType;
    PhoneNumbers number;
    if (contactType == 'w' || contactType == 'W' ||
        contactType == 'p' || contactType == 'P' || 
        contactType == 'c' || contactType == 'C' ||
        contactType == 'h' || contactType == 'H') {
        number.number = phoneNumber;
        number.phoneType = contactType;
        if (contactType == 'w' || contactType == 'W')
            displayType = "Work";
        else if (contactType == 'p' || contactType == 'P')
            displayType = "Personal";
        else if (contactType == 'c' || contactType == 'C')
            displayType = "Cell";
        else if (contactType == 'h' || contactType == 'H')
            displayType = "Home";
        
        numberList.push_back(number);
        return "success: added number " + phoneNumber + " " + displayType;
    }
    return "failure: invalid phone type - " + string(1, contactType);
}

// deletes phone from contact
string Contact::deletePhone(int index) {
    if (index < numberList.size()) {
        numberList.erase(numberList.begin() + index);
        return "success: deleted phone " + to_string(index);
    }
    return "failure: unable to delete phone " + to_string(index);
}

// displays the contact as a string
string Contact::getAsString() {
    string fullContact;
    string displayType;
    string numberType;
    
    if (contactType == 'w' || contactType == 'W')
        displayType = "Work";
    else if (contactType == 'p' || contactType == 'P')
        displayType = "Personal";
    else if (contactType == 'c' || contactType == 'C')
        displayType = "Cell";
    else if (contactType == 'h' || contactType == 'H')
        displayType = "Home";
    
    fullContact += getName() + "\n";
    fullContact += displayType + "\n";
    fullContact += getAddress() + "\n";
    fullContact += dateOfBirth + "\n";
    fullContact += email + "\n";

    for (PhoneNumbers i : numberList) {
        if (i.phoneType == 'w' || i.phoneType == 'W')
            numberType = "Work";
        else if (i.phoneType == 'p' || i.phoneType == 'P')
            numberType = "Personal";
        else if (i.phoneType == 'c' || i.phoneType == 'C')
            numberType = "Cell";
        else if (i.phoneType == 'h' || i.phoneType == 'H')
            numberType = "Home";
        
        fullContact += numberType + ": " + i.number + "\n";
    }
    return fullContact;
}

// operator overload
bool Contact::operator<(Contact c) {
    if (getName() < c.getName())
        return true;
    return false;
}

class ContactList {
    private:
    vector<Contact> contacts;

    public:
    // getter
    int getCount();
    
    // additional functions
    void printContacts(vector<int> indices);

    string loadContactsFromFile(string filename);
    string deleteContact(int index);
    string addContact(Contact c);
    string sortContacts();

    vector<int> findContactsByName(string name);

    string tester();
};

string ContactList::loadContactsFromFile(string filename) {
    char type;
    string firstName;
    string lastName;
    string streetNum;
    string streetName;
    string city;
    string state;
    string postcode;
    string email;
    string dateOfBirth;
    string age;
    string phone;
    string cell;
    
    ifstream file;
    string temp;
    
    file.open(filename);
    
    //checks if file is open
    if (!file)
        return "failure: " + filename + " not found";
    getline(file, temp);
    for (string line; getline(file, line);) {
        stringstream ss(line);

        // adds information to each contact
        int numIter = 0;
        for (string contactLine; getline(ss, contactLine, ',');) {
            switch (numIter){
                case 0:
                    type = contactLine[0];
                    break;
                case 1:
                    firstName = contactLine;
                    break;
                case 2:
                    lastName = contactLine;
                    break;
                case 3:
                    streetNum = contactLine;
                    break;
                case 4:
                    streetName = contactLine;
                    break;
                case 5:
                    city = contactLine;
                    break;
                case 6:
                    state = contactLine;
                    break;
                case 7:
                    postcode = contactLine;
                    break;
                case 8:
                    email = contactLine;
                    break;
                case 9:
                    dateOfBirth = contactLine;
                    break;
                case 10:
                    age = contactLine;
                    break;
                case 11: 
                    phone = contactLine;
                    break;
                case 12:
                    cell = contactLine;
                    break;
            }
            numIter++;
        }
        Contact c(type, firstName, lastName);
        c.setEmail(email);
        c.setDateOfBirth(dateOfBirth);
        c.setAddress(stoi(streetNum), streetName, city, state, stoi(postcode));
        c.addPhone('H', phone);
        c.addPhone('C', cell);
        contacts.push_back(c);
    }
    return "success: " + to_string(contacts.size()) + " contacts added";
}

// deletes contact from vector
string ContactList::deleteContact(int index) {
    if (index < contacts.size()) {
        string name = contacts.at(index).getName();
        contacts.erase(contacts.begin() + index);
        return "success: deleted contact " + name;
    }
    return "failure: unable to delete contact " + to_string(index);
}

// adds contact to vector if the type is valid
string ContactList::addContact(Contact c) {
    if (c.getContactType() == 'w' || c.getContactType() == 'W' ||
        c.getContactType() == 'p' || c.getContactType() == 'P' || 
        c.getContactType() == 'c' || c.getContactType() == 'C' ||
        c.getContactType() == 'h' || c.getContactType() == 'H') {
        contacts.push_back(c);
        return "success: contact " + c.getName() + " added";
    }
    return "failure: unable to add contact";
}

// sorts contacts vector by alphabetical order of names
string ContactList::sortContacts() {    
    sort(contacts.begin(), contacts.end());
    
    // checks if sort was successful
    if (is_sorted(contacts.begin(), contacts.end()))
        return "success";
    return "failure";
}

// searches contacts vector by full name
vector<int> ContactList::findContactsByName(string name) {
    vector<int> matches;
    string nameLower = "";
    
    for (int i = 0; i < name.size(); i++)
        nameLower += tolower(name.at(i));
    
    for (int i = 0; i < contacts.size(); i++) {
        string nameToSearchLower = "";
        string nameToSearch = contacts.at(i).getName();
        for (int j = 0; j < nameToSearch.size(); j++)
            nameToSearchLower += tolower(nameToSearch.at(j));

        if (nameToSearchLower.find(nameLower) != -1)
            matches.push_back(i);
        }
    return matches;
}

// prints the contacts given their indices
void ContactList::printContacts(vector<int> indices) {
    for (int i: indices) {
        cout << "--------------------\n\n";
        cout << contacts.at(i).getAsString();
        cout << "\n";
    }
}

int ContactList::getCount() {
    return contacts.size();
}

int main() {
    ContactList myContacts;
  
    myContacts.loadContactsFromFile("contacts.csv");
  
    myContacts.sortContacts();
  
    vector<int> v = myContacts.findContactsByName("ra");
    
    myContacts.printContacts(v);
    
    return 0;
}