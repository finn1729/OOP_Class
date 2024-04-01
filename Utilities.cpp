// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Utilities.h"


namespace sdds{

char Utilities::m_delimiter{};

Utilities::Utilities(){m_widthField=0;}

void Utilities::setFieldWidth(size_t newWidth){
    m_widthField = newWidth;
}
size_t Utilities::getFieldWidth() const{
    return m_widthField;
}
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
    
    std::string temp = "";
    if(more){
        size_t t_index = str.find(getDelimiter(), next_pos);
        if(t_index == std::string::npos){
            temp = str.substr(next_pos);
            if(m_widthField < temp.size()){
                setFieldWidth(temp.size());
            }
            more = false;
        } else if(t_index == next_pos){
            more = false;
            throw "Index is same.";
        } else{
            temp = str.substr(next_pos, t_index - next_pos);
            next_pos = t_index+1;
            
            if(m_widthField < temp.size()){
                setFieldWidth(temp.size());
            }
        }
    }
    return temp;
}
void Utilities::setDelimiter(char newDelimiter){
    m_delimiter = newDelimiter;
}
char Utilities::getDelimiter(){
    return m_delimiter;
}

}
