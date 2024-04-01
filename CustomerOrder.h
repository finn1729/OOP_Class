// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include <stdio.h>
#include "Station.h"
#include "Utilities.h"
namespace sdds{

struct Item{
    std::string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder{
private:
    std::string m_name;
    std::string m_product;
    size_t m_cntItem;
    Item** m_lstItem;
    static size_t m_widthField;
public:
    CustomerOrder();
    CustomerOrder(std::string& str);
    CustomerOrder(const CustomerOrder&);
    CustomerOrder& operator=(const CustomerOrder& cus) = delete;
    CustomerOrder(CustomerOrder&& src) noexcept;
    CustomerOrder& operator=(CustomerOrder&& cus) noexcept;
    ~CustomerOrder();
    bool isFilled() const;
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
    
};

}

#endif
