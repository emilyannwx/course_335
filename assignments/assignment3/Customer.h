#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

class Customer{
    private:
        string name_;
        int service_time_ = 0;
        int priority_level_ = 0;
    public:

        // default constructor
        Customer() : name_("Unknown") {
            SetPriorityLevel();
        }

        Customer(const string& name): name_(name){
            cout << name << endl;
            SetPriorityLevel();
        }
        void SetPriorityLevel(){
            priority_level_ = rand() % 101;
        }
        void SetServiceTime(){
            service_time_ = rand() % 61;
        }
        
        string GetName() const {
            return name_;
        }
        
        bool operator> (const Customer& other) const{
            return priority_level_ > other.priority_level_;
        }
        bool operator< (const Customer& other) const{
            return priority_level_ < other.priority_level_;
        }

        int GetServiceTime() const {
            return service_time_;
        }

        int GetPriorityLevel() const {
            return priority_level_;
        }


};

#endif // CUSTOMER_H 