//
//  ManhattanDistance.h
//  HW #3
//

#ifndef ManhattanDistance_h
#define ManhattanDistance_h

#include <stdio.h>
#include "Heuristic.h"
#include "GridMap.h"

class ManhattanDistance : public Heuristic {
public:
	int h(const STPState &s);
	int h(const GMState &s);
	void SetGoal(const GMState &s);

private:
	GMState goal;
};


#endif /* ManhattanDistance_h */
