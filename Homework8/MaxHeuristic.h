//
//  MaxHeuristic.h
//  HW4
//

#ifndef MaxHeuristic_h
#define MaxHeuristic_h

#include <stdio.h>

#include "Heuristic.h"

template <class state>
class MaxHeuristic : public Heuristic<state> {
public:
	void AddHeuristic(Heuristic<state> *);
	float h(const state &s1, const state &s2);
private:
	std::vector<Heuristic<state> *> heuristics;
};


template <class state>
void MaxHeuristic<state>::AddHeuristic(Heuristic<state> *h)
{
	heuristics.push_back(h);
}

template <class state>
float MaxHeuristic<state>::h(const state &s1, const state &s2)
{
	float hval = 0;
	for (auto h : heuristics)
	{
		hval = std::max(hval, h->h(s1, s2));
	}
	return hval;
}


#endif /* MaxHeuristic_h */
