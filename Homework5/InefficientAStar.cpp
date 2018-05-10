#include "InefficientAStar.h"

std::vector<STPSlideDir> InefficientAStar::GetPath(STPState &start, STPState &goal, Heuristic &h)
{
	LIST.clear();

	// struct A_STAR_NODE contains information about predecessors, g cost, and f cost
	// initialize an STP environment and a cursor pointing to the current node (a curr-sor?)
	// the first node is OPEN, its g cost is 0, and so its f cost is just the h cost
	STP puzzle;
	A_STAR_NODE root(start, h.h(start), 0, kNone);
	LIST.push_back(root);

	if (!root.OPEN) std::cout << "Whoa there.\n";

	// while we still have nodes on the OPEN list (or until we find a solution)
	while (!OPEN_EMPTY())
	{
		A_STAR_NODE curr = GET_BEST();

		if (curr.s == goal)
		{
			std::cout << "Path found\n";
			return RECONSTRUCT_PATH(puzzle, curr);
		}

		std::vector<STPSlideDir> operators;
		if (!operators.empty()) std::cout << "ERROR 1\n";
		puzzle.GetOperators(curr.s, operators);

		for (auto o : operators)
		{
			A_STAR_NODE neighbor;
			neighbor.set(curr, puzzle, o);
			neighbor.open();

			if (DUPLICATE_CHECK_C(neighbor.s))
			{
				//print(neighbor.s); std::cout << "IS CLOSED\n";
				continue;
			}

			if (!DUPLICATE_CHECK_O(neighbor.s))
			{
				//print(neighbor.s); std::cout << "HAS BEEN EXPANDED\n";
				LIST.push_back(neighbor);
			}

			int temp = curr.g + 1;

			if (temp >= neighbor.g) continue;

			//std::cout << temp << " " << neighbor.g << "\n";

			UPDATE_NODE(neighbor, o, temp, temp + h.h(neighbor.s));
		}
	}

	std::cout << "Path not found\n";
	return std::vector<STPSlideDir>();
}

std::vector<STPSlideDir> InefficientAStar::RECONSTRUCT_PATH(STP &puzzle, A_STAR_NODE curr)
{
	std::vector<STPSlideDir> path;
	path.push_back(curr.parent);

	while (curr.parent != kNone)
	{
		puzzle.UndoOperator(curr.s, curr.parent);
		curr.parent = GET_PARENT(curr.s);
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
			if (i->f < lowest)
			{
				//std::cout << "LOWEST UPDATED\n:" << lowest << ": -> :" << i->f << ":\n";
				i->close();
				lowest = i->f;
				cursor = *i;
			}
			//else std::cout << "LOWEST NOT UPDATED\n:" << i->f << ":\n";
		}
	}

	//print(cursor.s);
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

void InefficientAStar::UPDATE_NODE(A_STAR_NODE &n, STPSlideDir parent, int g, int f) // n must be in LIST for this to be called
{

	for (std::vector<A_STAR_NODE>::iterator i = LIST.begin(); i != LIST.end(); ++i)
	{
		if (i->s == n.s)
		{
			//std::cout << "parent = " << i->parent << " g = " << i->g << " f = " << i->f << "\n";

			i->parent = parent;
			i->g = g;
			i->f = f;

			//std::cout << "parent -> " << i->parent << " g -> " << i->g << " f -> " << i->f << "\n";

			return;
		}
	}

	std::cout << "ERROR 2\n";
}

STPSlideDir InefficientAStar::GET_PARENT(STPState &s) // n must be in LIST for this to be called
{

	for (std::vector<A_STAR_NODE>::iterator i = LIST.begin(); i != LIST.end(); ++i)
	{
		if (i->s == s)
		{
			return i->parent;
		}
	}

	std::cout << "ERROR 4\n";
	return kNone;
}