//
//  A.hpp
//  Homework5
//
//  Created by Kai Velagapudi on 4/26/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#ifndef A_hpp
#define A_hpp

#include <stdio.h>
#include "STP.h"
#include <vector>
#include <iostream>
class A{
    
public:
   
    A();
    
    // Open and closed lists of states
    std::vector<STPState> openList;
    std::vector<STPState> closedList;
    
    
    
    
private:
    
    //Take in a state and update its cost
    void updateCost(STPState s);
    
    // To check for duplictaes in the open and closed lists
    bool exists(STPState s);
    
};
#endif /* A_hpp */
