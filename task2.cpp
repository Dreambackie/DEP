#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Contact {
    private:
    string name;
    string phoneNumber;
public:
    Contact(string name, string phoneNumber){
        this->name = name;
        this->phoneNumber = phoneNumber;
    }
    string getName() const {
        return name;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

};

class ContactManager {
private:
    vector<Contact> contacts;
public:
    void addContact(const string& name, const string& phoneNumber) {
        contacts.emplace_back(name, phoneNumber);
    }

    void viewContacts() const {
        if (contacts.empty()) {
            cout << "No contacts available." << endl;
            return;
        }
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << i + 1 << ". Name: " << contacts[i].getName() << " - Phone Number: " << contacts[i].getPhoneNumber() << endl;
        }
    }

    void deleteContact(size_t index) {
        if (index < 1 || index > contacts.size()) {
            cout << "Invalid contact index." << endl;
            return;
        }
        contacts.erase(contacts.begin() + index - 1);
        cout << "Contact deleted successfully." << endl;
    }


};

void showMenu() {
    cout << "\nContact Management System\n";
    cout << "1. Add Contact\n";
    cout << "2. View Contacts\n";
    cout << "3. Delete Contact\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    ContactManager manager;
    int choice;
    string name, phoneNumber;
    size_t index;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter phone number: ";
            getline(cin, phoneNumber);
            manager.addContact(name, phoneNumber);
            cout << "Contact added successfully." << endl;
            break;

        case 2:
            manager.viewContacts();
            break;

        case 3:
            cout << "Enter the index of the contact to delete: ";
            cin >> index;
            manager.deleteContact(index);
            break;

        case 4:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
