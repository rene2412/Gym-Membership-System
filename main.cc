#include <iostream>
#include "membership.h"
#include <limits>
#include <algorithm>
#include <cctype>
#include <regex>
using namespace std;

bool isValidPhoneNumber(const std::string &phoneNumber) {
      regex pattern(R"(\d{3}-\d{3}-\d{4})");
      return regex_match(phoneNumber, pattern);
} 
bool isValidIDFormat(const std::string &id) {
     regex pattern(R"(\d{2}[A-Za-z]{2})");
     return regex_match(id, pattern);
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
string phone_number;
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
cout << "Enter an ID to search for a person" << endl;
getline(cin, key);
//bool find = system.search(key);
//if (find == false) cout << "Person not found!\n"; continue; 
//int choice = 0;

cout << "What do you want to edit?" << endl;
cout << "1) Name\n 2) Age\n 3) Phone Number\n";
cin >> choice;
if (!cin or (choice < 1 or choice > 3)) {
	cout << "BAD INPUT" << endl;
	continue;
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

