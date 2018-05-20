//
//  OctileDistance.h
//  HW #6
//

#ifndef OctileDistance_h
#define OctileDistance_h

#include <stdio.h>
#include <algorithm>
#include "Heuristic.h"
#include "Grid.h"

class OctileDistance : public Heuristic<GridState> {
public:
	float h(const GridState &s, const GridState &);
};


#endif /* ManhattanDistance_h */
