#include "AStar.h"

std::vector<STPSlideDir> AStar::GetPath(STPState &start, STPState &goal, Heuristic &h)
{
	LIST.clear();

	// struct A_STAR_NODE contains information about predecessors, g cost, and f cost
	// initialize an STP environment and a cursor pointing to the current node (a curr-sor?)
	// the first node is OPEN, its g cost is 0, and so its f cost is just the h cost
	STP puzzle;
	NODE root(h.h(start), 0, kNone);
	LIST.insert(STATE_NODE(start, root));
	for (int w = 0; w < 3; ++w)
	{
		for (int h = 0; h < 5; ++h)
		{
			std::cout << start.tiles[w][h] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	if (!root.OPEN) std::cout << "Whoa there.\n";

	// while we still have nodes on the OPEN list (or until we find a solution)
	while (!OPEN_EMPTY())
	{
		STPState curr = GET_BEST();

		if (curr == goal)
		{
			for (int w = 0; w < 3; ++w)
			{
				for (int h = 0; h < 5; ++h)
				{
					std::cout << goal.tiles[w][h] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			std::cout << "Path found\n";
			return RECONSTRUCT_PATH(puzzle, curr);
		}

		std::vector<STPSlideDir> operators;
		if (!operators.empty()) std::cout << "ERROR 1\n";
		puzzle.GetOperators(curr, operators);
		for (auto o : operators)
		{
			STPState neighbor = curr;
			puzzle.ApplyOperator(neighbor, o);
			if (DUPLICATE_CHECK_C(neighbor))
			{
				continue;
			}
			if (!DUPLICATE_CHECK_O(neighbor))
			{
				LIST.insert(STATE_NODE(neighbor, NODE()));
			}
			int temp = LIST.at(curr).g + 1;
			if (temp >= LIST.at(neighbor).g) continue;
			LIST.at(neighbor).parent = o;
			LIST.at(neighbor).g = temp;
			LIST.at(neighbor).f = temp + h.h(neighbor);
		}
	}

	std::cout << "Path not found\n";
	return std::vector<STPSlideDir>();
}

bool AStar::DUPLICATE_CHECK_O(STPState &s)
{
	if (LIST.find(s) != LIST.end())
	{
		return LIST.at(s).OPEN;
	}
	else return false;
}

bool AStar::DUPLICATE_CHECK_C(STPState &s)
{
	if (LIST.find(s) != LIST.end())
	{
		return !LIST.at(s).OPEN;
	}
	else return false;
}

bool AStar::OPEN_EMPTY()
{
	for (auto i : LIST)
	{
		if (i.second.OPEN) return false;
	}
	return true;
}

STPState& AStar::GET_BEST()
{
	int lowest = INT_MAX;
	STPState cursor;

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

std::vector<STPSlideDir> AStar::RECONSTRUCT_PATH(STP &puzzle, STPState curr) // curr passed in by value on purpose
{
	std::vector<STPSlideDir> path;
	path.push_back(LIST.at(curr).parent);

	while (LIST.at(curr).parent != kNone)
	{
		puzzle.UndoOperator(curr, LIST.at(curr).parent);
		path.push_back(LIST.at(curr).parent);
	}

	return path;
}