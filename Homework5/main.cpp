#include <iostream>
#include "Timer.h"
#include "InefficientAStar.h"
#include "STP.h"

int main() 
{
	ManhattanDistance h;
	InefficientAStar a;

	STP puzzle;
	STPState s;
	DoRandomWalkOperators(puzzle, s, 5);

	STPState goal;
	std::vector<STPSlideDir> path = a.GetPath(s, goal, h);

	for (auto i : path)
	{
		std::cout << i << " - ";
	}
	std::cout << std::endl;

	return 0;
}