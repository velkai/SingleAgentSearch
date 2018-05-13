//
//  MaxHeuristic.cpp
//  HW4
//

#include "MaxHeuristic.h"


void MaxHeuristic::AddHeuristic(Heuristic *h)
{
	heuristics.push_back(h);
}

int MaxHeuristic::h(const STPState &s)
{
	int hval = 0;
	for (auto h : heuristics)
	{
		hval = std::max(hval, h->h(s));
	}
	return hval;
}

