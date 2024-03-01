#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
class Person {
private:
   std::string membership_id; // will be the key
   std::string name;
   int age;
   std::string phone_number;
   bool account;
public:
    Person(std::string m = "", std::string n = "", int a = 0, std::string p = "", bool b = false) : membership_id(m), name(n), age(a), phone_number(p), account(b) {} 
    
    std::string GetMemberShipId() const { return membership_id; } 
    std::string GetName() const { return name; }
    int GetAge() const  { return age; }
    std::string GetPhoneNumber() const { return phone_number; } 
    bool GetAccount() const { return account; }

     void Set_MemberShipId(std::string &m) { membership_id = m; }
     void SetName(std::string &n) { name = n; } 
     void SetAge(int &a) { age = a; }
     void SetPhoneNumber(std::string &p) { phone_number = p; }
     void SetAccount(bool &b) { account = b; }

};
 
class System : public Person {
private: 
     std::unordered_map<std::string, Person> database; // will hold the entire gym database
public:

     void PrintDataBase() const {
	    for (const auto& pair : database) {
	     std::cout << "Membership ID: " << pair.first << " | Name: " << pair.second.GetName() << 
	     " | Age: " << pair.second.GetAge() << " | Phone Number: " << pair.second.GetPhoneNumber() << 
	     " | Account Status: " << (pair.second.GetAccount() ? "Active" : "Inactive") << std::endl;
	     }
	    if (database.empty()) {
	    std::cout << "Database Empty\n";
	   }
	}
     //key
     void AddPerson(const Person &person) {
	   database[person.GetMemberShipId()] = person;
	} 

    void remove(const std::string &key) {
	auto iter = database.find(key);
	if (iter != database.end()) {
	  database.erase(iter); 
	}
	else std::cout << "Person not found!" << std::endl; 
    } 	
    
    bool search(const std::string &key) {
	auto iter = database.find(key);
	if (iter != database.end()) {
	const Person &found = iter->second;
	     std::cout << "Membership ID: " << found.GetMemberShipId() << " | Name: " 
	     << found.GetName() << " | Age: " << found.GetAge() <<
	     " | Phone Number: " << found.GetPhoneNumber() << " | Account Status: "
	     << (found.GetAccount() ? "Active" : "Inactive") << std::endl;
		return true;
	}
	else {
		std::cout << "Error: Person Not Found\n";
		return false;
	}
    }
   

    void save_file(const std::string &filename) const {
	std::ofstream file(filename, std::ios_base::app);
	if (file.is_open()) {
	    for (const auto& pair : database) {
		file << pair.first << " | " <<pair.second.GetName() <<
		" | " << pair.second.GetAge() << " | " << pair.second.GetPhoneNumber() << " | " << 
		 (pair.second.GetAccount() ? "Active" : "Inactive") << std::endl;
	    }
	}
	else std::cout << "Error Opening File" << std::endl;
	}
    
  void load_file(const std::string &filename) {
	    std::ifstream file(filename);
	    if (file.is_open()) {
		std::string line;
		getline(file, line); //throw away file header
		while(std::getline(file, line)) {
		   //if (!file) break;
		    std::stringstream srs(line);
		    std::string id, name, age, phone_number, account_str;
		    int new_age = 0;
		    bool account;
		    if (std::getline(srs, id, '|') and
		    std::getline(srs, name, '|') and
		    std::getline(srs, age, '|') and
		    std::getline(srs, phone_number, '|') and
		    std::getline(srs, account_str)) {
    
		    try {
			new_age = std::stoi(age);
			} catch (...) {
  		  	continue; // Skip the current line and continue with the next one
				}
             	    account = (account_str == "Active");
		    Person newPerson(id, name, new_age, phone_number, account);
		    database[id] = newPerson;
		  }	
		else std::cout << "Error Paring\n";
	       }
	    }
	        else std::cout << "Error opening" << std::endl;
  }

};
