#pragma once
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
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
     std::vector<std::pair<std::string, Person>> database; // will hold the entire gym database
public:
  const std::vector<std::pair<std::string, Person>> &GetDatabase()  const { return database; }

     void PrintDataBase()  {
	    for (const auto& data : GetDatabase()) {
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
	   database.push_back({person.GetMemberShipId(), person});
	} 
void remove(const std::string &key) {
    auto iter = std::find_if(database.begin(), database.end(),
          [key](const auto &entry) { return entry.first == key; });

	if (iter != database.end()) {
	  database.erase(iter); 
	   std::cout << "Person erased" << std::endl;
	}
	else std::cout << "Person not found!" << std::endl; 
    } 

    bool search(const std::string &key) {
	for (const auto &pair : GetDatabase()) {
	     if (pair.first == key) {
		std::cout << "Person Found!" << std::endl;
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
		    std::getline(srs, name, '|'); 
		    std::getline(srs, age, '|');
		    std::getline(srs, phone_number, '\n'); 
		    try {
			new_age = std::stoi(age);
			} catch (...) {
  		  	continue; 
				}
		    Person newPerson(id, name, new_age, phone_number);
		    database.push_back({id, newPerson});
		     }
	        }
	        else std::cout << "Error opening" << std::endl;
  }

};
