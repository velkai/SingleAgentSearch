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
	DoRandomWalkOperators(puzzle, s, 10);

	STPState goal;
	std::vector<STPSlideDir> path = a.GetPath(s, goal, h);

	for (auto i : path)
	{
		if(i == 0) std::cout << "UP - ";
		else if (i == 1) std::cout << "DOWN - ";
		else if (i == 2) std::cout << "RIGHT - ";
		else if (i == 3) std::cout << "LEFT - ";
		else if (i == 4) std::cout << "ROOT\n";
	}
	std::cout << std::endl;

	return 0;
}