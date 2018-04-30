#pragma once
#include <deque>
#include <iostream>
#include <unordered_map>
#include "STP.h"
#include "heuristic.h"

#define COST_PAIR std::pair<STPState, int>
#define NODE_PAIR std::pair<STPState, STPSlideDir>

class InefficientAStar
{
public:

	InefficientAStar(heuristic &h);

	std::vector<STPSlideDir> GetPath(STPState &start, STPState &goal);


private:

	std::vector<STPState> OPEN;
	std::vector<STPState> CLOSED;
	heuristic h;
	
	bool DUPLICATE_CHECK_O(STPState &s);
	bool DUPLICATE_CHECK_C(STPState &s);
	void UPDATE_G_COST(std::unordered_map<STPState, int> &f, std::unordered_map<STPState, int> &g, STPState &s, int gCost);
	COST_PAIR GET_BEST(std::unordered_map<STPState, int> &f);
	void REMOVE(std::vector<STPState> &list, STPState &s);

	std::vector<STPSlideDir> RECONSTRUCT_PATH(STP &puzzle, std::unordered_map<STPState, STPSlideDir> &cameFrom, STPState &curr);

};