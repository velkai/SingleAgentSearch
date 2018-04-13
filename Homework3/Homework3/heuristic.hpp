//
//  heuristic.hpp
//  Homework3
//
//  Created by Kai Velagapudi on 4/10/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#ifndef heuristic_hpp
#define heuristic_hpp

#include <stdio.h>

#include "STP.h"

// Ask : Do we keep thraxk of the heuristic as a spertae class or just function?
class Heuristic{

public:

    virtual int getFcost();
    virtual int setGcost(int c);
    virtual int getHcost(STPState s);


private:

    int fcost;
    int gcost;
    int hcost;

};

#endif /* heuristic_hpp */

