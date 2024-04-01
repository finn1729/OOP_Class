// Name:Junweon Suh
// Seneca Student ID:153879176
// Seneca email: jsuh6@myseneca.ca
// Date of completion: December 3rd 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// I got help from professor and learning center especially constructor and linkStations

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"

namespace sdds{
LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
    m_cntCustomerOrder=0;
    m_firstStation=nullptr;
    
    std::ifstream f(file,std::ios::in|std::ios::out);
    Utilities util{};
    size_t t_nextPos = 0;
    bool t_more = true; 
    std::string line;
    std::string current;
    std::string next;
    
    Workstation* f_ws = nullptr;
    Workstation* c_ws = nullptr;
    Workstation* n_ws = nullptr;
    
    if(!f){
        throw "Not able to open";
        
    } else{
        
    
    
        while(std::getline(f,line)){
            t_nextPos = 0;
            t_more = true;
            current = util.extractToken(line, t_nextPos, t_more);
            
            c_ws = *std::find_if(stations.begin(),stations.end(),[&current](Workstation* ws){
                return ws->getItemName() == current;
            });
            
            activeLine.push_back(c_ws);
            
            if(t_more){
                next = util.extractToken(line, t_nextPos, t_more);
                n_ws = *std::find_if(stations.begin(),stations.end(),[&next](Workstation* ws){
                    return ws->getItemName() == next;
                });
                c_ws -> setNextStation(n_ws);
            } else{}
        }
        
        for_each(stations.begin(), stations.end(), [&](Workstation* t_first){
            f_ws = *std::find_if(stations.begin(),stations.end(),[&](Workstation* st){
                return st->getNextStation() == f_ws;
            });
        });
        m_firstStation = f_ws;
    }
    m_cntCustomerOrder = pending.size();
    f.close();
}
void LineManager::linkStations(){
    const Workstation* ws = m_firstStation;
    size_t i = 0;
    do {
        activeLine[i++] = const_cast<Workstation*>(ws);
        ws = ws -> getNextStation();
    } while(ws != nullptr);
}
bool LineManager::run(std::ostream& os){
    static size_t i = 1;
    os << "Line Manager Iteration: " << i++ << std::endl;
    if(!pending.empty()){
        *(m_firstStation) += std::move(pending.front());
        pending.pop_front();
    }
    
    try{
        std::for_each(activeLine.begin(),activeLine.end(),[&os](Workstation* ws){
            ws->fill(os);
        });
    }catch(const char* err){
        std::cout << "fill: " << err << std::endl;
     }
    try{
        std::for_each(activeLine.begin(),activeLine.end(),[](Workstation* ws){
            ws->attemptToMoveOrder();
        });
    } catch(const char* err){
        std::cout << "attempt: " << err << std::endl;
    }

    return m_cntCustomerOrder == completed.size() + incomplete.size();
}
void LineManager::display(std::ostream& os) const{
    for_each(activeLine.begin(), activeLine.end(), [&](const Workstation* ws){
        
        ws->display(os);
    });
}
}
