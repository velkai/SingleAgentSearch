//
//  main.cpp
//  HW1
//

#include <iostream>
#include "heuristic.h"
#include "Timer.h"
#include "STP.h"
#include "IDA.h"

void print(STPState &s);

int main(int argc, const char * argv[])
{
	
	/*for (int i = 0; i < 10; ++i)
	{	
		std::cout << i << ":\n";
		STP *puzzle = new STP();
		STPState *s = new STPState();
		DoRandomWalkSuccessors(*puzzle, *s, i);
		std::cout << s->blankx << " " << s->blanky << "\n";
		print(*s);

		heuristic *h = new ManhattanDistance();
		h->updateHCost(*s);
		std::cout << h->HCOST << "\n";

	}*/

	for (int j = 0; j < 15; ++j)
	{
		STP *puzzle = new STP();
		STPState *s = new STPState(), *GOAL = new STPState();
		heuristic *h = new ManhattanDistance();
		DoRandomWalkSuccessors(*puzzle, *s, j);

		IDA ida;
		std::deque<STPState> path = ida.GetPath(*puzzle, *s, *GOAL, *h);

		std::cout << "\n-------------\n\n";

		for (int i = 0; i < path.size(); ++i)
		{
			print(path.at(i));
		}
	}

	std::cout << "Nice.\n";

	return 0;
}

void print(STPState &s)
{
	std::cout << " _________________ \n|                 |\n";
	for (int w = 0; w < 3; ++w)
	{
		std::cout << "| ";
		for (int h = 0; h < 5; ++h)
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
	std::cout << "|_________________|\n";
}