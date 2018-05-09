#pragma once

#include "STP.h"
#include "Heuristic.h"
#include <iostream>
#include <unordered_map>


struct NODE
{
	int f, g;
	bool OPEN;
	STPSlideDir parent;

	NODE()
	{
		f = g = INT_MAX;
		OPEN = true;
		parent = kNone;
	}

	NODE(int f, int g, STPSlideDir parent)
	{
		this->f = f;
		this->g = g;
		this->parent = parent;
		OPEN = true;
	}

	bool equals(const NODE &other)
	{
		return this->f == other.f
			&& this->g == other.g
			&& this->OPEN == other.OPEN
			&& this->parent == other.parent;
	}

	void close()
	{
		OPEN = false;
	}
};

typedef std::pair<STPState, NODE> STATE_NODE;


class AStar
{
public:

	std::vector<STPSlideDir> GetPath(STPState &start, STPState &goal, Heuristic &h);

private:

	std::unordered_map<STPState, NODE> LIST;

	bool DUPLICATE_CHECK_O(STPState &s);
	bool DUPLICATE_CHECK_C(STPState &s);
	bool OPEN_EMPTY();
	STPState& GET_BEST();

	std::vector<STPSlideDir> RECONSTRUCT_PATH(STP &puzzle, STPState curr);
};