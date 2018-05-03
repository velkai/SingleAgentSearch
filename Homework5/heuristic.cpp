#include "heuristic.h"
#include "Timer.h"

void print1(STPState &s);

int ManhattanDistance::h(const STPState &s)
{
	int HCOST = 0;
	for (int w = 0; w < 3; ++w)
	{
		for (int h = 0; h < 5; ++h)
		{
			if (s.tiles[w][h] != 0)
				HCOST += DISTANCE_FROM_GOAL(w, h, s.tiles[w][h]);
		}
	}
	return HCOST;
}

int ManhattanDistance::DISTANCE_FROM_GOAL(int x, int y, int value)
{
	int goal_x, goal_y;
	goal_x = value % 3;
	goal_y = value / 3;

	return abs(goal_x - x) + abs(goal_y - y);
}

void print1(STPState &s)
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