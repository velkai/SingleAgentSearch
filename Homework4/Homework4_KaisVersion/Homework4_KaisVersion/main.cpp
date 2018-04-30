#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "heuristic.h"
#include "Timer.h"
#include "STP.h"
#include "IDA.h"
#include "Ranking.h"

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

	/*for (int j = 0; j < 15; ++j)
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
	}*/

	/*Ranking *r = new Ranking();
	STPState *s = new STPState();
	STP *puzzle = new STP();
	uint64_t *test;

	for (int i = 0; i < 10; ++i)
	{
		DoRandomWalkSuccessors(*puzzle, *s, i);
		print(*s);
		std::cout << i << " : A-";
		test = r->GetPDBRank(*s);
		std::cout << test[0] << " B-" << test[1] << "\n";
	}*/

	/*STP puzzle;
	STPState s;
	Ranking r;

	DoRandomWalkOperators(puzzle, s, 6);
	print(s);
	std::cout << r.GetPDBRank(s)[0] << "\n";*/

	std::cout << "This program is a memory hog, but we're not sure how to fix this. Be careful of your memory when you run it\n";

	PatternDatabase h;
	h.printTests();

	std::cout << "\nNice.\n";

	return 0;
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