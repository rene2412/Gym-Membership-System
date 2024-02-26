#include <iostream>
#include <unordered_map>
class Membership {
private:
   float fee;
   float payment;
   bool account;
public:
   Membership(float f = 100, float p = 25, bool a = false) : fee(f), payment(p), account(a) {}

   float GetFee() const { return fee; }
   float GetPayment() const { return payment; }
   bool GetAccount() const { return account; }
 
   void SetAccount(bool &b) { account = b; }
};

class Person {
private:
   std::string membership_id; // will be the key
   std::string name;
   int age;
   std::string phone_number;
public:
    Person(std::string m = "", std::string n = "", int a = 0, std::string p = "") : membership_id(m), name(n), age(a), phone_number(p) {} 
    
    std::string GetMemberShipId() const { return membership_id; } 
    std::string GetName() const { return name; }
    int GetAge() const  { return age; }
    std::string GetPhoneNumber() const { return phone_number; } 

     void Set_MemberShipId(std::string &m) { membership_id = m; }
     void SetName(std::string &n) { name = n; } 
     void SetAge(int &a) { age = a; }
     void SetPhoneNumber(std::string &p) { phone_number = p; }

     bool operator(const std::string &a, const std::string &b) const {
     	return a < b;
     }

};

class System : public Membership, public Person {
private: 
     std::unordered_map<> database; // will hold the enite gym database
public:

};
