#pragma once

#include "STP.h"
#include "Heuristic.h"
#include <iostream>
#include <unordered_map>


template <typename T> struct NODE
{
	int f, g;
	bool OPEN;
	T parent;

	NODE()
	{
		f = g = INT_MAX;
		OPEN = true;
		parent = kNone;
	}

	NODE(int f, int g, T parent)
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




template <typename PUZZLE = STP, typename STATE = STPState, typename OPERATOR = STPSlideDir>
class AStar
{
	typedef std::pair<STATE, NODE<OPERATOR>> STATE_NODE;

public:

	std::vector<OPERATOR> GetPath(STATE &start, STATE &goal, Heuristic &heuristic)
	{
		LIST.clear();
		PUZZLE puzzle;

		// struct NODE contains information about predecessors, g cost, and f cost
		// initialize an PUZZLE environment and a cursor pointing to the current node (a curr-sor?)
		// the first node is OPEN, its g cost is 0, and so its f cost is just the h cost
		if constexpr (std::is_same_v<PUZZLE, GridMap>)
		{
			std::cout << "GridMap detected\n";
			puzzle = g;
		}
		
		NODE<OPERATOR> root(heuristic.h(start), 0, kNone);
		LIST.insert(STATE_NODE(start, root));

		if (!root.OPEN) std::cout << "Whoa there.\n";

		// while we still have nodes on the OPEN list (or until we find a solution)
		while (!OPEN_EMPTY())
		{
			STATE curr = GET_BEST();

			if (curr == goal)
			{
				std::cout << std::endl;
				std::cout << "Path found\n";
				return RECONSTRUCT_PATH(puzzle, curr);
			}

			std::vector<OPERATOR> operators;
			if (!operators.empty()) std::cout << "ERROR 1\n";
			puzzle.GetOperators(curr, operators);
			for (auto o : operators)
			{
				STATE neighbor = curr;
				puzzle.ApplyOperator(neighbor, o);
				if (DUPLICATE_CHECK_C(neighbor))
				{
					continue;
				}
				if (!DUPLICATE_CHECK_O(neighbor))
				{
					LIST.insert(STATE_NODE(neighbor, NODE<OPERATOR>()));
				}
				int temp = LIST.at(curr).g + 1;
				if (temp >= LIST.at(neighbor).g) continue;
				LIST.at(neighbor).parent = o;
				LIST.at(neighbor).g = temp;
				LIST.at(neighbor).f = temp + heuristic.h(neighbor);
			}
		}

		std::cout << "Path not found\n";
		return std::vector<OPERATOR>();
	}

	void SetMap(GridMap &g)
	{
		this->g = g;
	}

private:

	std::unordered_map<STATE, NODE<OPERATOR>> LIST;
	GridMap g;

	bool DUPLICATE_CHECK_O(STATE &s)
	{
		if (LIST.find(s) != LIST.end())
		{
			return LIST.at(s).OPEN;
		}
		else return false;
	}

	bool DUPLICATE_CHECK_C(STATE &s)
	{
		if (LIST.find(s) != LIST.end())
		{
			return !LIST.at(s).OPEN;
		}
		else return false;
	}

	bool OPEN_EMPTY()
	{
		for (auto i : LIST)
		{
			if (i.second.OPEN) return false;
		}
		return true;
	}

	STATE GET_BEST()
	{
		int lowest = INT_MAX;
		STATE cursor;

		for (auto &i : LIST)
		{
			if (i.second.OPEN)
			{
				if (i.second.f < lowest)
				{
					i.second.close();
					lowest = i.second.f;
					cursor = i.first;
				}
			}
		}

		return cursor;
	}

	std::vector<OPERATOR> RECONSTRUCT_PATH(PUZZLE &puzzle, STATE curr)
	{
		std::vector<OPERATOR> path;
		path.push_back(LIST.at(curr).parent);

		while (LIST.at(curr).parent != kNone)
		{
			puzzle.UndoOperator(curr, LIST.at(curr).parent);
			path.push_back(LIST.at(curr).parent);
		}

		return path;
	}
};