//
//  Heuristic.h
//  HW #3
//
//  Created by Nathan Sturtevant on 4/15/18.
//  Copyright © 2018 NS Software. All rights reserved.
//

#ifndef Heuristic_h
#define Heuristic_h

#include "STP.h"
#include <iostream>

class Heuristic {
public:
	virtual ~Heuristic() {}
	virtual int h(const STPState &) = 0;
};

class ManhattanDistance : public Heuristic
{
public:

	int h(const STPState &);

private:

	int DISTANCE_FROM_GOAL(int x, int y, int value);
};
#endif /* Heuristic_h */
