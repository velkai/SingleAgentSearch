#pragma once

#include "STP.h"
#include "Heuristic.h"
#include <iostream>
#include <unordered_map>


template <typename T> struct NODE
{
	double f, g;
	bool OPEN;
	T parent;

	NODE()
	{
		f = g = INT_MAX;
		OPEN = true;
		parent = (T)4;
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




template <typename PUZZLE, typename STATE, typename OPERATOR>
class AStar
{
	typedef std::pair<STATE, NODE<OPERATOR>> STATE_NODE;

public:

	std::vector<OPERATOR> GetPath(STATE &start, STATE &goal, Heuristic &heuristic)
	{
		LIST.clear();
		PUZZLE puzzle;
		std::vector<OPERATOR> ret;
		bool GOAL_FOUND = false;

		// struct NODE contains information about predecessors, g cost, and f cost
		// initialize an PUZZLE environment and a cursor pointing to the current node (a curr-sor?)
		// the first node is OPEN, its g cost is 0, and so its f cost is just the h cost
		if constexpr (std::is_same_v<PUZZLE, GridMap>)
		{
			std::cout << "GridMap detected\n";
			puzzle = g;
		}
		
		NODE<OPERATOR> root(heuristic.h(start), 0, (OPERATOR)4);
		LIST.insert(STATE_NODE(start, root));

		// while we still have nodes on the OPEN list (or until we find a solution)
		while (!OPEN_EMPTY())
		{
			STATE curr = GET_BEST();

			//std::cout << curr << ":";
			//std::cout << LIST.find(curr)->second.g << "-" << LIST.find(curr)->second.f << "\n";

			if (curr == goal && !GOAL_FOUND)
			{
				GOAL_FOUND = true;
				std::cout << std::endl;
				std::cout << "Path found\n";
				ret = RECONSTRUCT_PATH(puzzle, curr);
			}

			std::vector<OPERATOR> operators;
			if (!operators.empty()) std::cout << "ERROR 1\n";
			puzzle.GetOperators(curr, operators);
			if (operators.size() == 0) std::cout << "ERROR 2 " << curr << "\n";
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
				if (LIST.find(neighbor) == LIST.end()) std::cout << "ERROR 3 " << neighbor << "\n";
				int temp = LIST.at(curr).g + puzzle.GetCost(o);
				if (temp >= LIST.at(neighbor).g) continue;
				LIST.at(neighbor).parent = o;
				LIST.at(neighbor).g = temp;
				LIST.at(neighbor).f = temp + heuristic.h(neighbor);
			}
		}

		std::vector<STATE> list;
		for (auto i : LIST)
		{
			list.push_back(i.first);
		}
		puzzle.PrintStates(list);

		std::cout << "\n";
		if(ret.empty()) std::cout << "Path not found\n";
		return ret;
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

		while ((int)(LIST.at(curr).parent) != 4) // for all Dir enums, assume 4 is kNone
		{
			puzzle.UndoOperator(curr, LIST.at(curr).parent);
			path.push_back(LIST.at(curr).parent);
		}

		return path;
	}
};