#include "MaxHeap.h"
#include "Customer.h"
#include <iostream>
#include <algorithm>


#include <vector>

#include <ctime>


using namespace std;

int main(){
    srand(static_cast<unsigned int>(time(0)));
    MaxHeap<Customer> problemsStore;
    vector<Customer> customers;

   //adding customers 
    Customer c1("Maya");
    customers.push_back(c1);
    problemsStore.insert(c1);
    Customer c2("Carlos");
    customers.push_back(c2);
    problemsStore.insert(c2);
    Customer c3("Madina");
    customers.push_back(c3);
    problemsStore.insert(c3);
    Customer c4("Krip");
    customers.push_back(c4);
    problemsStore.insert(c4);

//print customers currently in store
    cout << "customers in store" << endl;
    for (const auto& customer : customers) {
        std::cout << "Customer: " << customer.GetName()
                  << ", Service Time: " << customer.GetServiceTime()
                  << ", Priority Level: " << customer.GetPriorityLevel() << endl;

    }
    cout << endl;

    vector<Customer> history; 
    while(!problemsStore.isEmpty()){
        Customer current_customer = problemsStore.deleteMax();
        current_customer.SetServiceTime();
        history.push_back(current_customer);

    }

    sort(history.begin(), history.end(), [](Customer & a, Customer & b){
        return a.GetServiceTime() < b.GetServiceTime();
    });

    // print the sorted history
    cout << "customers served"<<endl;
    for (const auto& customer : history) {
        std::cout << "Customer: " << customer.GetName()
                  << ", Service Time: " << customer.GetServiceTime()
                  << ", Priority Level: " << customer.GetPriorityLevel() << std::endl;
    }

    return 0;
}