//
//  IDA.cpp
//  Homework3
//
//  Created by Kai Velagapudi on 4/10/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#include "IDA.hpp"
#include "STP.h"

class IDA{
    
public:
    
    bool GetPath(STP s, STPState &start, STPState &goal);
    
private:
    
    
    bool IDASearch(STP s, STPState &start, STPState &goal , int d);
};


