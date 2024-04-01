// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
#include <stdio.h>
namespace sdds{
class Station{
private:
    int station_id;
    std::string item_name;
    std::string description;
    unsigned int serial;
    unsigned int num;
    static size_t m_widthField;
    static int id_generator;
public:
    Station(const std::string& st);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
};
}
#endif /* SDDS_STATION_H */
