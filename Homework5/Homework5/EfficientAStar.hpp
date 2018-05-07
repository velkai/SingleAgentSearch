//
//  EfficientAStar.hpp
//  Homework5
//
//  Created by Kai Velagapudi on 5/3/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#ifndef EfficientAStar_hpp
#define EfficientAStar_hpp

#include <stdio.h>
#include "STP.h"
#include "heuristic.h"
#include <vector>
#include "InefficientAStar.h"

class EfficientAStar{
public:
    
    EfficientAStar();
    
    std::vector<STPSlideDir> GetPath(STPState &start, STPState &goal, heuristi &h);
private:
    
    std::vector<A_STAR_NODE> LIST;
    
    bool DUPLICATE_CHECK_O(STPState &s);
    bool DUPLICATE_CHECK_C(STPState &s);
    bool OPEN_EMPTY();
    A_STAR_NODE& GET_BEST();
    void UPDATE_NODE(A_STAR_NODE &n, STPSlideDir parent, int g, int f);
    STPSlideDir GET_PARENT(STPState &s);
    
    std::vector<STPSlideDir> RECONSTRUCT_PATH(STP &puzzle, A_STAR_NODE curr);

};
#endif /* EfficientAStar_hpp */
