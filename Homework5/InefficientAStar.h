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

    // Struct
	A_STAR_NODE()
	{
        // Initialising to Max value
		f = INT_MAX;
		g = INT_MAX;
		parent = kNone;
		OPEN = true;
	}
	
	A_STAR_NODE(STPState &s, int f, int g, STPSlideDir parent) // this is only ever used to initialize the root
	{
		this->s = s;
		this->f = f;
		this->g = g;
		this->parent = parent;
		OPEN = true;
	}

	void set(A_STAR_NODE &source, STP &puzzle, STPSlideDir o)
	{
		for (int w = 0; w < 3; ++w)
		{
			for (int h = 0; h < 5; ++h)
			{
				this->s.tiles[w][h] = source.s.tiles[w][h];
			}
		}
		this->s.blankx = source.s.blankx;
		this->s.blanky = source.s.blanky;

		puzzle.ApplyOperator(this->s, o);
		this->parent = o;
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

	AStar();

	std::vector<STPSlideDir> GetPath(STPState &start, STPState &goal, Heuristic &h);


private:

    // Using an int as a key
	std::unordered_map<int, A_STAR_NODE> LIST;
	
	bool DUPLICATE_CHECK_O(STPState &s);
	bool DUPLICATE_CHECK_C(STPState &s);
	bool OPEN_EMPTY();
	A_STAR_NODE& GET_BEST();
	void UPDATE_NODE(A_STAR_NODE &n, STPSlideDir parent, int g, int f);
	STPSlideDir GET_PARENT(STPState &s);

	std::vector<STPSlideDir> RECONSTRUCT_PATH(STP &puzzle, A_STAR_NODE curr);

};
