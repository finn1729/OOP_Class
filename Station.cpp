// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
namespace sdds{

size_t Station::m_widthField=0;
int Station::id_generator=0;



Station::Station(const std::string& st){
    Utilities util;
    station_id=0;
    serial=0;
    num=0;
    bool more = true;
    size_t pos = 0;
    item_name = util.extractToken(st, pos, more);
    serial = std::stoi(util.extractToken(st,pos,more));
    num = std::stoi(util.extractToken(st,pos,more));
    if(m_widthField < util.getFieldWidth()){
        m_widthField =util.getFieldWidth();
    }
    description = util.extractToken(st,pos,more);
    id_generator += 1;
    station_id = id_generator;
    
    
}
const std::string& Station::getItemName() const{
    return item_name;
}
size_t Station::getNextSerialNumber(){
    return serial++;
}
size_t Station::getQuantity() const{
    return num;
}
void Station::updateQuantity(){
    if(num<=1){
        num =0;
    } else{
        num -= 1;
    }
}
void Station::display(std::ostream& os, bool full) const{
    os <<"[" << std::setw(3) << std::setfill('0') << std::right << station_id <<"] " << "Item: " << std::setfill(' ') << std::setw(m_widthField) << std::left << item_name<< " [" << std::setw(6) << std::setfill('0') << std::right << serial << "]" <<  std::setfill(' ');
    if(full){
        os << " Quantity: " <<std::setw(m_widthField) << std::left << num << " Description: "<< description;
    }
    os <<std::endl;
}
}
