#include "heuristic.h"

heuristic::heuristic()
{
	FCOST = GCOST = HCOST = 0;
}

ManhattanDistance::ManhattanDistance() : heuristic()
{

}

void ManhattanDistance::updateFCost(STPState &s, std::deque<STPState> &path)
{
	updateGCost(path);
	updateHCost(s);
	FCOST = GCOST + HCOST;
}

void ManhattanDistance::updateGCost(std::deque<STPState> &path)
{
	GCOST = path.size();
}

void ManhattanDistance::updateHCost(STPState &s)
{
	HCOST = 0; // reset hcost back to 0
	for (int w = 0; w < 3; ++w)
	{
		for (int h = 0; h < 5; ++h)
		{
			if (s.tiles[w][h] != 0)
				HCOST += DISTANCE_FROM_GOAL(w, h, s.tiles[w][h]);
		}
	}
}

int ManhattanDistance::DISTANCE_FROM_GOAL(int x, int y, int value)
{
	int goal_x, goal_y;
	goal_x = value % 3;
	goal_y = value / 3;

	return abs(goal_x - x) + abs(goal_y - y);
}