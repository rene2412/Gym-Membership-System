#include <iostream>
#include "membership.h"
#include <limits>
#include <algorithm>
#include <cctype>
#include <regex>
using namespace std;

System s;

bool isValidPhoneNumber(const std::string &phoneNumber) {
      regex pattern(R"(\d{3}-\d{3}-\d{4})");
      return regex_match(phoneNumber, pattern);
} 
bool isValidIDFormat(const std::string &id) {
     regex pattern(R"(\d{2}[A-Za-z]{2})");
     return regex_match(id, pattern);
}
bool CheckID_Duplicate(const std::string key) {
	for (const auto& pair : s.GetDatabase()) {
		cout << "Keys already in use: " << pair.first << " compared to wanted key: " << key << endl;
		if (pair.first == key)  {
		    cout << "ID is already taken, use a different one" << endl;
		    //continue;
		}
	}
	//cout << "ID good to go" << endl;
}

int main() {

System system;
system.load_file("database.txt");

int choice = 0;
while (true) {
cout << "What do you want to today?\n";
cout << "1) Add a person\n2) Remove a person\n3) Search for a Person\n4) Edit Information\n5) Show All In Database\n6) Quit\n";
cin >> choice;
cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
if (!cin or (choice < 1 or choice > 6)) {
	cout << "BAD INPUT" << endl;
	exit(1);
 	}
if (choice == 1) {
string id;
bool check = false;
cout << "Enter an ID: " << endl;
getline(cin, id);
if (isValidIDFormat(id)) {
     check = true;
} else {
  cout << "Error: Invalid ID" << endl; 
  continue;
}
CheckID_Duplicate(id);
string name;
cout << "Enter a Name: " << endl;
getline(cin, name);

int age = 0;
cout << "Enter an Age: " << endl;
cin >> age;
if (!cin or age < 5 or age > 120) {
     cout << "Invalid Age!" << endl;
     continue;
}
cin.ignore();

bool valid = false;
string phone_number;
while (!valid) {
cout << "Enter a Phone-Number" << endl;
getline(cin, phone_number);
 if (isValidPhoneNumber(phone_number)) {
	valid = true;
 } else {  
   std::cout << "Error: Invalid phone number format. Please use the format XXX-XXX-XXXX." << std::endl;
  }
}

Person newPerson(id, name, age, phone_number);
system.AddPerson(newPerson);
cout << name << " has been successfully added" << endl;
system.save_file("database.txt", newPerson);

}

if (choice == 2) {
string key;
cout << "Enter an ID to remove a person" << endl;
getline(cin, key);
system.remove(key);
//system.save_file("database.txt");
}

if (choice == 3) {
string key;
cout << "Enter an ID to search for a person" << endl;
getline(cin, key);
system.search(key);
}
	
if (choice == 4) {
string key;
cout << "Enter an ID to look up that person" << endl;
getline(cin, key);
// Check if the person exists in the database
    const auto& database = system.GetDatabase();
    auto iter = std::find_if(database.begin(), database.end(),
                             [&key](const auto& entry) { return entry.first == key; });

    if (iter != database.end()) {
        // Person found, prompt for editing information
        cout << "What do you want to edit?" << endl;
        cout << "1) Name\n2) Age\n3) Phone Number\n";
        cin >> choice;

        // Clear input buffer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (!cin or (choice < 1 or choice > 3)) {
            cout << "BAD INPUT" << endl;
            continue;
        }

        // Retrieve the person from the database
        auto& personToEdit = const_cast<Person&>(iter->second);
        // Edit the chosen information using setters
        switch (choice) {
            case 1:
                {
          string newName;
          cout << "Enter the new name: ";
          getline(cin, newName);
          personToEdit.SetName(newName);
          cout << "Name updated successfully!" << endl;
             }
                break;
            case 2:
                {
                    int newAge;
                cout << "Enter the new age: ";
                cin >> newAge;
                    if (cin && newAge >= 5 && newAge <= 120) {
                        personToEdit.SetAge(newAge);
                        cout << "Age updated successfully!" << endl;
                    } else {
                        cout << "Invalid Age!" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                break;
            case 3:
                {
                    bool valid = false;
                    string newPhoneNumber;
                    while (!valid) {
                        cout << "Enter the new phone number: ";
                        getline(cin, newPhoneNumber);
                        if (isValidPhoneNumber(newPhoneNumber)) {
                            personToEdit.SetPhoneNumber(newPhoneNumber);
                            valid = true;
                            cout << "Phone number updated successfully!" << endl;
                        } else {
                            cout << "Error: Invalid phone number format. Please use the format XXX-XXX-XXXX." << endl;
                        }
                    }
                }
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    } else {
        cout << "Person not found!" << endl;
    }
   }


if (choice == 5) {
system.PrintDataBase();
}
if (choice == 6) {
//system.save_file("database.txt");
break;
}

}

}

