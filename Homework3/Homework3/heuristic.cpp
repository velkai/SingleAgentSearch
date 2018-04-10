//
//  heuristic.cpp
//  Homework3
//
//  Created by Kai Velagapudi on 4/10/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#include "heuristic.hpp"
#include "STP.h"

// Ask : Do we keep thraxk of the heuristic as a spertae class or just function? 
class Heuristic{
    
public:
    
   virtual int getFcost();
   virtual int setGcost(int c);
    
    
private:
    
    int fcost;
    int gcost;
    int hcost;
    
};
