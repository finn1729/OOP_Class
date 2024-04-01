// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <iostream>
#include <stdio.h>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds{
    extern std::deque<CustomerOrder> pending;
    extern std::deque<CustomerOrder> completed;
    extern std::deque<CustomerOrder> incomplete;

class Workstation:public Station{
private:
    std::deque<CustomerOrder> m_orders;
    Workstation* m_pNextStation;
public:
    Workstation(const std::string& str);
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station = nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
};
}


#endif /* Workstation_h */
