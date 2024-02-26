#include <iostream>
#include <unordered_map>
class Membership {
private:
   float fee;
   float payment;
public:
   Membership(float f = 100, float p = 25) : fee(f), payment(p) {}

   float GetFee() const { return fee; }
   float GetPayment() const { return payment; }
 
};

class Person {
private:
   std::string membership_id; // will be the key
   std::string name;
   int age;
   std::string phone_number;
   bool account;
public:
    Person(std::string m = "", std::string n = "", int a = 0, std::string p = "", bool a) : membership_id(m), name(n), age(a), phone_number(p) account(a) {} 
    
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

     bool operator< (const Person &other) const {
     	return name < other.name
     }

};
 
class System : public Membership, public Person {
private: 
     std::unordered_map<std::string key, Person> database; // will hold the enite gym database
public:
	
};
