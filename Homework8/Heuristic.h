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

template <class state>
class Heuristic {
public:
	virtual ~Heuristic() {}
	virtual float h(const state &, const state &) = 0;
};

#endif /* Heuristic_h */
