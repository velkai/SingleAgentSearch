#pragma once

#include "STP.h"
#include <iostream>
#include <deque>

class heuristic
{
public:

	heuristic();

	virtual void updateFCost(STPState &s, std::deque<STPState> &path) { std::cout << "WRONG\n"; };
	virtual void updateGCost(std::deque<STPState> &path) { std::cout << "WRONG\n"; };
	virtual void updateHCost(STPState &s) { std::cout << "WRONG\n"; };

	int FCOST;
	int GCOST;
	int HCOST;
};

class ManhattanDistance :public heuristic
{
public:

	ManhattanDistance();

	void updateFCost(STPState &s, std::deque<STPState> &path);
	void updateGCost(std::deque<STPState> &path);
	void updateHCost(STPState &s);

private:

	int DISTANCE_FROM_GOAL(int x, int y, int value);
};