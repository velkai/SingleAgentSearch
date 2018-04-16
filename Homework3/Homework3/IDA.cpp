
#include "IDA.h"

IDA::IDA()
{

}

std::deque<STPState> IDA::GetPath(STP &s, STPState &start, STPState &goal, heuristic &h)
{
	h.updateHCost(start);
	int threshold = h.HCOST;
	std::deque<STPState> *path = new std::deque<STPState>();
	path->push_back(start);
	while (true)
	{
		int temp = IDASearch(s, *path, 0, threshold, h);
		if (temp == 0) return *path; // pseudocode says if t == FOUND, but I'm not sure what FOUND would be besides 0
		threshold += temp;
	}
}

int IDA::IDASearch(STP &s, std::deque<STPState> &path, int g, int t, heuristic &h)
{
	STPState curr = path.back();
	STPState GOAL;
	h.updateHCost(curr);
	int f = g + h.HCOST;
	if (f > t) return f; // if the f cost is greater than the threshold
	if (curr == GOAL) return 0;
	int minimum = INT_MAX;
	std::vector<STPState> successors;
	s.GetSuccessors(curr, successors);
	for (STPState succ : successors)
	{
		bool CONTAINED_IN_PATH = false;
		for (int i = 0; i < path.size(); ++i)
		{
			if (succ == path.at(i))
			{
				CONTAINED_IN_PATH = true;
				break;
			}
		}
		if (!CONTAINED_IN_PATH)
		{
			path.push_back(succ);
			int temp = IDASearch(s, path, g + 1, t, h);
			if (temp == 0) return 0;
			if (temp < minimum) minimum = temp;
			path.pop_back();
		}
	}
	return minimum;
}