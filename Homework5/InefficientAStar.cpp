#include "InefficientAStar.h"

InefficientAStar::InefficientAStar(heuristic &h)
{
	this->h = h;
}

std::vector<STPSlideDir> InefficientAStar::GetPath(STPState &start, STPState &goal)
{
	// can't be too safe
	CLOSED.clear();
	OPEN.clear();

	// initialize g and f cost containers, as well as a container for a node's parent operators
	// also initialize an STP environment and a cursor pointing to the current node(curr-sor?)
	std::unordered_map<STPState, STPSlideDir> cameFrom; // v1 = state, v2 = (most efficient parent)
	std::unordered_map<STPState, int> g;
	std::unordered_map<STPState, int> f;
	STP puzzle;
	COST_PAIR curr;

	// put the first node on the OPEN list
	OPEN.push_back(start);

	// assign the first node a g cost of 0
	g.insert(COST_PAIR(start, 0));

	// for the first node, the f cost is simply the heuristic value, because the g cost is 0
	h.updateHCost(start);
	f.insert(COST_PAIR(start, h.HCOST));

	// make sure we know it's the root node by assigning its parent operator to kNone
	cameFrom.insert(NODE_PAIR(start, kNone));

	// while we still have nodes on the OPEN list (or until we find a solution)
	while (!OPEN.empty())
	{
		// set our currsor to the node with the lowest f cost
		// at the start, this will have to be the root node
		curr = GET_BEST(f);

		// if we've just found the solution, return the path
		if (curr.first == goal) return RECONSTRUCT_PATH(puzzle, cameFrom, curr.first);
		
		// move the currsor from OPEN to CLOSED
		REMOVE(OPEN, curr.first);
		CLOSED.push_back(curr.first);

		// get and examine the currsor's successors
		std::vector<STPSlideDir> operators;
		if (!operators.empty()) std::cout << "SCOPE ERROR WITH THE OPERATORS LIST\n";
		puzzle.GetOperators(curr.first, operators);
		for (auto o : operators)
		{
			// initialize some temp variables
			int CURR_GCOST = (*g.find(curr.first)).second;
			STPState CURR = curr.first;

			// use the currsor to examine successors
			// we will ALWAYS undo the operator before the end of an iteration
			puzzle.ApplyOperator(curr.first, o);

			// if this successor is on the CLOSED list then we ignore it
			if (DUPLICATE_CHECK_C(curr.first))
			{
				// reset the currsor
				puzzle.UndoOperator(curr.first, o);
				continue;
			}
			// add this successor to the OPEN list if we haven't already, and give it an entry in our f and g cost lists
			if (!DUPLICATE_CHECK_O(curr.first))
			{
				f.insert(COST_PAIR(curr.first, INT_MAX));
				g.insert(COST_PAIR(curr.first, INT_MAX));
				OPEN.push_back(STPState(curr.first));
			}

			// get this successor's potential g cost
			int temp = CURR_GCOST + 1;

			// if this is path costs more than the already explored path then we move on
			if (temp >= (*g.find(curr.first)).second)
			{
				// reset the currsor
				puzzle.UndoOperator(curr.first, o);
				continue;
			}

			// connect this successor to a path; assign its parent operator and assign its f and g costs
			if (CURR == curr.first) std::cout << "NON-SHALLOW COPY DETECTED - Will cause errors in pathfinding and cost data\n";
			(*cameFrom.find(curr.first)).second = o;
			(*g.find(curr.first)).second = temp;
			h.updateHCost(curr.first);
			(*f.find(curr.first)).second = temp + h.HCOST;

			// reset the currsor
			puzzle.UndoOperator(curr.first, o);
		}
	}

	// hopefully we never see this
	std::cout << "PATH NOT FOUND\n";
	return std::vector<STPSlideDir>();
}

std::vector<STPSlideDir> InefficientAStar::RECONSTRUCT_PATH(STP &puzzle, std::unordered_map<STPState, STPSlideDir> &cameFrom, STPState &curr)
{
	std::vector<STPSlideDir> path;
	path.push_back((*cameFrom.find(curr)).second);

	while ((*cameFrom.find(curr)).second != kNone)
	{
		puzzle.ApplyOperator(curr, (*cameFrom.find(curr)).second);
		path.push_back((*cameFrom.find(curr)).second);
	}

	return path;
}

bool InefficientAStar::DUPLICATE_CHECK_C(STPState &s)
{
	for (auto i : CLOSED)
	{
		if (i == s) return true;
	}
	return false;
}

bool InefficientAStar::DUPLICATE_CHECK_O(STPState &s)
{
	for (auto i : OPEN)
	{
		if (i == s) return true;
	}
	return false;
}

void InefficientAStar::UPDATE_G_COST(std::unordered_map<STPState, int> &f, std::unordered_map<STPState, int> &g, STPState &s, int gCost)
{
	for (auto i : g)
	{
		if (i.first == s)
		{
			for (auto j : f)
			{
				if (j.first == s)
				{
					// reevaluate the node's fCost
					j.second -= i.second;
					// reevaluate the node's gCost
					i.second = gCost;
					j.second += gCost;
					return;
				}
			}
		}
	}
}

COST_PAIR InefficientAStar::GET_BEST(std::unordered_map<STPState, int> &f)
{
	int lowest = -1;
	STPState key_val;

	for (auto i : f)
	{
		if (i.second < lowest)
		{
			lowest = i.second;
			key_val = i.first;
		}
	}

	return *f.find(key_val);
}

void InefficientAStar::REMOVE(std::vector<STPState> &list, STPState &s)
{
	for (std::vector<STPState>::iterator i = list.begin(); i != list.end(); ++i)
	{
		if (*i == s) list.erase(i);
	}
}