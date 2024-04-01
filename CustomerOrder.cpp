// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"

using namespace std;

namespace sdds{

size_t CustomerOrder::m_widthField=1;
//struct Item{
//    std::string m_itemName;
//    size_t m_serialNumber{0};
//    bool m_isFilled{false};
//
//    Item(const std::string& src) : m_itemName(src) {};
//};
//
//class CustomerOrder{
//private:
//    std::string m_name;
//    std::string m_product;
//    size_t m_cntItem;
//    Item** m_lstItem;
//    static size_t m_widthField;
//public:
CustomerOrder::CustomerOrder(){
    m_cntItem=0;
    m_lstItem=nullptr;
}
CustomerOrder::CustomerOrder(std::string& str){
    Utilities util{};
    size_t next_pos = 0;
    bool more = true;
    m_name = util.extractToken(str, next_pos, more); // extract name
    m_product = util.extractToken(str, next_pos, more); // extract product
    m_cntItem = count(str.begin(), str.end(), util.getDelimiter())-1; // num of delimiter = num of items
    m_lstItem = new Item*[m_cntItem];
    
    for(size_t i = 0; i<m_cntItem;i++){
        m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
    }
    if(CustomerOrder::m_widthField < util.getFieldWidth()){
        CustomerOrder::m_widthField = util.getFieldWidth();
    }
    
}

CustomerOrder::CustomerOrder(const CustomerOrder& cus){
    throw "COPY NOT ALLOWED";
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept{
    m_cntItem=0;
    m_lstItem=nullptr;
    *this = move(src);
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cus) noexcept{
    if(this != &cus){
        for(size_t i = 0; i<m_cntItem;i++){
            delete m_lstItem[i];
        }
//        for_each(m_lstItem, m_lstItem + m_cntItem, [](Item *item){
//            delete item;
//        });
        delete [] m_lstItem;
        m_lstItem = cus.m_lstItem;
        m_name = cus.m_name;
        m_product = cus.m_product;
        m_cntItem = cus.m_cntItem;
        
        cus.m_name = "";
        cus.m_product = "";
        cus.m_cntItem=0;
        cus.m_lstItem = nullptr;
    }
    return *this;
}
CustomerOrder::~CustomerOrder(){
    for_each(m_lstItem, m_lstItem+m_cntItem, [](Item *item){
        delete item;
    });
    delete [] m_lstItem;
}
bool CustomerOrder::isFilled() const{
    
    return all_of(m_lstItem, m_lstItem + m_cntItem,[](Item* item){
        return item->m_isFilled;
    });
    
}
bool CustomerOrder::isItemFilled(const std::string& itemName) const{
    bool filled = true;
    for(size_t i=0;i<m_cntItem && filled == true;i++){
        if(itemName == m_lstItem[i]->m_itemName){
            if(m_lstItem[i]->m_isFilled){
                filled = true;
            } else{
                filled = false;
            }
        }
    }
    return filled;
}
void CustomerOrder::fillItem(Station& station, std::ostream& os){
    for(size_t i = 0;i<m_cntItem;i++){
        if(m_lstItem[i]->m_itemName == station.getItemName()){
            if(station.getQuantity()>0){
                if(!m_lstItem[i]->m_isFilled){
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    os <<"    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                }
            }else{
                os << "    Unable to fill "<<m_name<<", "<<m_product<< " ["<< m_lstItem[i]->m_itemName <<"]" << endl;
            }
        }
    }
   
}
void CustomerOrder::display(std::ostream& os) const{
    os << m_name << " - " << m_product << endl;
    for_each(m_lstItem,m_lstItem+m_cntItem, [&os](Item* item){
        os << "[" << setfill('0') << setw(6) <<item->m_serialNumber << setfill(' ') << "] " << left <<setw(m_widthField) << item->m_itemName << " - " << right;
        if(item->m_isFilled){
            os << "FILLED";
        } else{
            os << "TO BE FILLED";
        }
        os << endl;
    });
    
    
}
    
}
