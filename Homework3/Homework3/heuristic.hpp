//
//  heuristic.hpp
//  Homework3
//
//  Created by Kai Velagapudi on 4/10/18.
//  Last edited by Jimmy Holmes on 4/13/2018
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#ifndef heuristic_hpp
#define heuristic_hpp

#include <stdio.h>

#include "STP.h"
#include <deque>

// Ask : Do we keep thraxk of the heuristic as a spertae class or just function?
class Heuristic{

public:

    virtual int getFcost(STPState &s, std::deque<STPState> &path);
    virtual int getGcost(std::deque<STPState> &path);
    virtual int getHcost(STPState &s);


protected:

    virtual void UPDATE_FCOST(STPState &s);
    virtual void UPDATE_GCOST(std::deque<STPState> &path);
    virtual void UPDATE_HCOST(STPState &s);

    int fcost;
    int gcost;
    int hcost;

};

#endif /* heuristic_hpp */

