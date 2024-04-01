// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// I got help from professor and learning center


#include "Workstation.h"

namespace sdds{


std::deque<CustomerOrder> pending{};
std::deque<CustomerOrder> completed{};
std::deque<CustomerOrder> incomplete{};

Workstation::Workstation(const std::string& str) : Station(str){
    m_pNextStation=nullptr;
}

void Workstation::fill(std::ostream& os){
    if(!m_orders.empty()){
        m_orders.front().fillItem(*this,os);
    }
}

bool Workstation::attemptToMoveOrder(){
    bool moved = false;
    if(!m_orders.empty()){
        if(m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0){
//            if(m_pNextStation==nullptr){
//                completed.push_back(m_orders.front());
//            } else{
//                *m_pNextStation += std::move(m_orders.front());
//                m_orders.pop_front();
//            }
            if(m_pNextStation==nullptr){
                if(m_orders.front().isFilled()){
                    completed.push_back(std::move(m_orders.front()));
                } else{
                    incomplete.push_back(std::move(m_orders.front()));
                }
            } else{
                *m_pNextStation += std::move(m_orders.front());
                
            }
            m_orders.pop_front();
            moved = true;
        }
    }
    return moved;
}

void Workstation::setNextStation(Workstation* station){
    if(m_pNextStation!=nullptr) delete m_pNextStation;
    m_pNextStation = station;
}

Workstation* Workstation::getNextStation() const{
    return m_pNextStation;
}

void Workstation::display(std::ostream& os) const{
    os << getItemName() << " --> ";
    if(m_pNextStation == nullptr){
        os << "End of Line" << std::endl;
    } else{
        os << m_pNextStation->getItemName() << std::endl;
    }
}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
    m_orders.push_back(std::move(newOrder));
    return *this;
}

}
