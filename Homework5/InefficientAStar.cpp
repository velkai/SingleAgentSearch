#include "InefficientAStar.h"

void print(STPState &s);

InefficientAStar::InefficientAStar()
{
}

std::vector<STPSlideDir> InefficientAStar::GetPath(STPState &start, STPState &goal, heuristic &h)
{
	LIST.clear();

	// struct A_STAR_NODE contains information about predecessors, g cost, and f cost
	// initialize an STP environment and a cursor pointing to the current node (a curr-sor?)
	// the first node is OPEN, its g cost is 0, and so its f cost is just the h cost
	STP puzzle;
	h.updateHCost(start);
	A_STAR_NODE root(start, h.HCOST, 0, kNone);
	LIST.push_back(root);

	if (!root.OPEN) std::cout << "Whoa there.\n";

	// while we still have nodes on the OPEN list (or until we find a solution)
	while (!OPEN_EMPTY())
	{
		A_STAR_NODE curr = GET_BEST();

		if (curr.s == goal) return RECONSTRUCT_PATH(puzzle, curr);

		std::vector<STPSlideDir> operators;
		if (!operators.empty()) std::cout << "ERROR 1\n";
		puzzle.GetOperators(curr.s, operators);

		for (auto o : operators)
		{
			A_STAR_NODE neighbor;
			neighbor.set(curr);
			puzzle.ApplyOperator(neighbor.s, o);
			neighbor.open();
			print(neighbor.s);

			if (DUPLICATE_CHECK_C(neighbor.s))	continue;

			if (!DUPLICATE_CHECK_O(neighbor.s))	LIST.push_back(neighbor);

			int temp = curr.g + 1;

			if (temp >= neighbor.g) continue;

			h.updateHCost(neighbor.s);
			UPDATE_NODE(neighbor, o, temp, temp + h.HCOST);
		}
	}

	return std::vector<STPSlideDir>();
}

std::vector<STPSlideDir> InefficientAStar::RECONSTRUCT_PATH(STP &puzzle, A_STAR_NODE &curr)
{
	std::vector<STPSlideDir> path;
	path.push_back(curr.parent);

	while (curr.parent != kNone)
	{
		puzzle.ApplyOperator(curr.s, curr.parent);
		path.push_back(curr.parent);
	}

	return path;
}

// checks to see if a node is on the closed list
bool InefficientAStar::DUPLICATE_CHECK_C(STPState &s)
{
	for (auto i : LIST)
	{
		if (i.s == s)
		{
			if(i.OPEN == false) return true;
			else return false;
		}
	}
	return false;
}

bool InefficientAStar::DUPLICATE_CHECK_O(STPState &s)
{
	for (auto i : LIST)
	{
		if (i.s == s)
		{
			if(i.OPEN == true) return true;
			else return false;
		}
	}
	return false;
}

A_STAR_NODE& InefficientAStar::GET_BEST()
{
	int lowest = INT_MAX;
	A_STAR_NODE cursor;

	for (std::vector<A_STAR_NODE>::iterator i = LIST.begin(); i != LIST.end(); ++i)
	{
		if (i->OPEN)
		{
			//print(i.s);
			if (i->f < lowest)
			{
				i->close();
				lowest = i->f;
				cursor = *i;
			}
		}
	}

	print(cursor.s);
	return cursor;
}

bool InefficientAStar::OPEN_EMPTY()
{
	for (auto i : LIST)
	{
		if (i.OPEN) return false;
	}
	return true;
}

void print(STPState &s)
{
	std::cout << " ___________ \n|           |\n";
	for (int h = 0; h < 5; ++h)
	{
		std::cout << "| ";
		for (int w = 0; w < 3; ++w)
		{
			std::cout << " ";
			if (s.tiles[w][h] > 9)
			{
				std::cout << s.tiles[w][h];
			}
			else std::cout << s.tiles[w][h] << " ";
		}
		std::cout << " |\n";
	}
	std::cout << "|___________|\n";
}

void InefficientAStar::UPDATE_NODE(A_STAR_NODE &n, STPSlideDir parent, int g, int f) // n must be in LIST for this to be called
{
	for (auto i : LIST)
	{
		if (i.s == n.s)
		{
			i.parent = parent;
			i.g = g;
			i.f = f;

			return;
		}
	}

	std::cout << "ERROR 2\n";
}