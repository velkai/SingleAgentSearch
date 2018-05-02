#pragma once

#include "STP.h"
#include "heuristic.h"
#include <deque>
#include <iostream>
#include <unordered_map>

struct A_STAR_NODE
{
	STPState s;
	int f, g;
	STPSlideDir parent;
	bool OPEN;

	A_STAR_NODE()
	{
		f = INT_MAX;
		g = INT_MAX;
		parent = kNone;
		OPEN = true;
	}
	
	A_STAR_NODE(STPState &s, int f, int g, STPSlideDir parent)
	{
		this->s = s;
		this->f = f;
		this->g = g;
		this->parent = parent;
		OPEN = true;
	}

	void set(A_STAR_NODE &source)
	{
		this->s = source.s;
		this->f = source.f;
		this->g = source.g;
		this->parent = parent;
		this->OPEN = source.OPEN;
	}

	void open()
	{
		OPEN = true;
	}

	void close()
	{
		OPEN = false;
	}
};

class InefficientAStar
{
public:

	InefficientAStar();

	std::vector<STPSlideDir> GetPath(STPState &start, STPState &goal, heuristic &h);


private:

	std::vector<A_STAR_NODE> LIST;
	
	bool DUPLICATE_CHECK_O(STPState &s);
	bool DUPLICATE_CHECK_C(STPState &s);
	bool OPEN_EMPTY();
	A_STAR_NODE& GET_BEST();
	void UPDATE_NODE(A_STAR_NODE &n, STPSlideDir parent, int g, int f);

	std::vector<STPSlideDir> RECONSTRUCT_PATH(STP &puzzle, A_STAR_NODE &curr);

};