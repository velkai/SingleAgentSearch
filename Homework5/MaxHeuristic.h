//
//  MaxHeuristic.h
//  HW4
//

#ifndef MaxHeuristic_h
#define MaxHeuristic_h

#include <stdio.h>

#include "Heuristic.h"

class MaxHeuristic : public Heuristic {
public:
	void AddHeuristic(Heuristic *);
	int h(const STPState &s);
private:
	std::vector<Heuristic *> heuristics;
};


#endif /* MaxHeuristic_h */
