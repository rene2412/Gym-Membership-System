#include <iostream>
#include "membership.h"
using namespace std;

// todo
/*
string create_key() {
system.database[key.GetMemberShipId()] = person;

}
*/
int main() {
System system;

system.load_file("database.txt");
int choice = 0;
while (true) {
cout << "What do you want to today?\n";
cout << "1) Add a person\n2) Remove a person\n3) Search for a Person\n4) Show All\n5) Quit\n";
cin >> choice;
cin.ignore();
if (!cin or (choice < 1 or choice > 5)) {
	cout << "BAD INPUT" << endl;
	exit(1);
 	}
if (choice == 1) {
string id;
cout << "Enter an ID: " << endl;
getline(cin, id);

string name;
cout << "Enter a Name: " << endl;
getline(cin, name);

int age = 0;
cout << "Enter an Age: " << endl;
cin >> age;
cin.ignore();

cout << "Enter a Phone-Number" << endl;
string phone_number;
getline(cin, phone_number);

bool account = false;
cout << "Account status is active!" << endl;
account = true;
cin.ignore();

Person newPerson(id, name, age, phone_number, account);
system.AddPerson(newPerson);
system.PrintDataBase();
system.save_file("database.txt");
}
if (choice == 2) {	
//todo
string key;
cout << "Enter an ID to remove a person" << endl;
getline(cin, key);
system.remove(key);
system.save_file("database.txt");
}
if (choice == 3) {
string key;
cout << "Enter an ID to search for a person" << endl;
getline(cin, key);
system.search(key);
}
if (choice == 4) {
system.PrintDataBase();
}
if (choice == 5) {
system.save_file("database.txt");
break;
}

}

}

