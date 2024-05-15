#pragma once
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
class Person {
private:
   std::string membership_id; // will be the key
   std::string name;
   int age;
   std::string phone_number;
public:
    Person(std::string m = "", std::string n = "", int a = 0, std::string p = "", bool b = false) : membership_id(m), name(n), age(a), phone_number(p) {} 
    
    std::string GetMemberShipId() const { return membership_id; } 
    std::string GetName() const { return name; }
    int GetAge() const  { return age; }
    std::string GetPhoneNumber() const { return phone_number; } 

     void Set_MemberShipId(std::string &m) { membership_id = m; }
     void SetName(std::string &n) { name = n; } 
     void SetAge(int &a) { age = a; }
     void SetPhoneNumber(std::string &p) { phone_number = p; }

};
 
class System : public Person {
private: 
     std::unordered_map<std::string, Person> database; // will hold the entire gym database
public:
   std::unordered_map<std::string, Person> &GetDatabase()  { return database; }

     void PrintDataBase()  {
	    for (const auto& data : database) {
		 const auto &pair = data.second;
		 std::cout << "Membership ID: " << data.first << " | Name: " << pair.GetName() << 
	     " | Age: " << pair.GetAge() << " | Phone Number: " << pair.GetPhoneNumber() << std::endl;
	     }
	    if (database.empty()) {
	    std::cout << "Database Empty\n";
	   }
	}
	
     //key
     void AddPerson(const Person &person) {
	   database.insert({person.GetMemberShipId(), person});
	} 
bool remove(const std::string &key) {
	bool found = search(key);
	char choice;
        if (!found) {
	 std::cout << "Person not found!" << std::endl; 
       	 return false;
	}
	else { 
	       auto iter = database.find(key);
	       if (iter != database.end()) {
		std:: cout << "Are you sure you want to delete " << iter->second.GetName() << " from the gym database? Type: Y(Yes)/N(No)\n";  
		std::cin >> choice;
                 if (choice == 'y' or choice == 'Y') {
			 std::cout << iter->second.GetName() << " has been removed" << std::endl;
			 database.erase(iter);
			 return true;
		 }
		 else if (choice == 'n' or choice == 'N') return false;
	       }
	   }  
	return false;
}
    bool search(const std::string &key) {
	for (const auto &pair : database) {
	     if (key == pair.first) {
		std::cout << "ID: " << pair.first << "| Name: " << pair.second.GetName() << 
	     " | Age: " << pair.second.GetAge() << " | Phone Number: " << pair.second.GetPhoneNumber() << std::endl;	
		return true;
	     }
	}	
		std::cout << "Error: Person Not Found\n";
		return false;
    }

    void save_file(const std::string &filename, const Person &newPerson) const {
	    std::ifstream checkFile(filename);
	    std::string line;
	    bool isDuplicate = false;
	    getline(checkFile, line); //throw away first header
	    while(std::getline(checkFile, line)) {
     		 if (line.find(newPerson.GetMemberShipId()) != std::string::npos) {
		   isDuplicate = true;
		   break; 
	        }
	    }
		checkFile.close();
	if (!isDuplicate) {
	std::ofstream file(filename, std::ios::app);
	if (file.is_open()) {
		file << newPerson.GetMemberShipId() << " | " << newPerson.GetName() <<
		" | " << newPerson.GetAge() << " | " << newPerson.GetPhoneNumber() << " " << std::endl;
	}

	else std::cout << "Error Opening File" << std::endl;
	}
    }
  
    void load_file(const std::string &filename) {
	    std::ifstream file(filename);
	    if (file.is_open()) {
		std::string line;
		getline(file, line); //throw away file header
		while(std::getline(file, line)) {
		    std::stringstream srs(line);
		    std::string id, name, age, phone_number;
		    int new_age = 0;
		    std::getline(srs, id, '|'); 
		    id.erase(id.find_last_not_of(" \t\r\n") + 1);
		    std::getline(srs, name, '|'); 
		    std::getline(srs, age, '|');
		    std::getline(srs, phone_number, '\n'); 
		    try {
			new_age = std::stoi(age);
			} catch (...) {
  		  	continue; 
				}
		    Person newPerson(id, name, new_age, phone_number);
		    database.insert({id, newPerson});
		     }
	        }
	        else std::cout << "Error opening" << std::endl;
  }

};
