#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <cstdlib>
using namespace std;

class Customer{
    private:
        string name_;
        int service_time;
        int priority_level_;
    public:
        Customer(const string& name): name_(name){
            SetPriorityLevel();
        }
        void SetPriorityLevel(){
            priority_level_ = rand() % 101;
        }
        void SetServiceTime(){
            service_time = rand() % 61;
        }

        bool operator> (const Customer& other) const{
            return priority_level_ > other.priority_level_;
        }
        bool operator< (const Customer& other) const{
            return priority_level_ < other.priority_level_;
        }



};

#endif // CUSTOMER_H 