// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <stdio.h>
#include <vector>
#include "Workstation.h"
namespace sdds{
class LineManager{
private:
    std::vector<Workstation*> activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void linkStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};

}

#endif /* LineManager_h */
