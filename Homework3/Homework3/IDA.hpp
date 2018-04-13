//
//  IDA.hpp
//  Homework3
//
//  Created by Kai Velagapudi on 4/10/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#ifndef IDA_hpp
#define IDA_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "STP.h"
#include "ManhattanDistance.h"

class IDA{

public:

    std::deque<STPState> GetPath(STP &s, STPState &start, STPState &goal, Heuristic h);

private:


    int IDASearch(STP &s, std::deque<STPState> &path, int g, int t, Heuristic h); // takes the path, g-value, and threshold as parameters
};

#endif /* IDA_hpp */
