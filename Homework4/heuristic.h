#pragma once

#include "STP.h"
#include "Ranking.h"
#include "BFS.h"
#include "DFID.h"
#include <iostream>
#include <cstdlib>
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

class ManhattanDistance : public heuristic
{
public:

	ManhattanDistance();

	void updateFCost(STPState &s, std::deque<STPState> &path);
	void updateGCost(std::deque<STPState> &path);
	void updateHCost(STPState &s);

private:

	int DISTANCE_FROM_GOAL(int x, int y, int value);
};

struct PDB_BUILD_NODE
{
	PDB_BUILD_NODE()
	{
		depth = 0;
	}

	STPState s;
	int depth;
};

class PatternDatabase : public heuristic
{
public:

	PatternDatabase();

	void updateFCost(STPState &s, std::deque<STPState> &path);
	void updateGCost(std::deque<STPState> &path);
	void updateHCost(STPState &s);
	

private:

	uint8_t *A, *B;
	int ASize, BSize;
	bool CONTAINED(char c, uint64_t rank); // c will either be 'A', or 'B'
	STPSlideDir OPPOSITE(STPSlideDir o);
	void INITIALIZE_ARRAYS();
	void BUILD_PDB_A();
	void BUILD_PDB_B();
	
};