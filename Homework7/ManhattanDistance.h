//
//  ManhattanDistance.h
//  HW #3
//

#ifndef ManhattanDistance_h
#define ManhattanDistance_h

#include <stdio.h>
#include "Heuristic.h"

class ManhattanDistance : public Heuristic<STPState> {
public:
	float h(const STPState &s, const STPState &);
};


#endif /* ManhattanDistance_h */
