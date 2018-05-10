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
	int h(const GMState &s)
	{
		return 0;
	}
private:
	std::vector<Heuristic *> heuristics;
};


#endif /* MaxHeuristic_h */
