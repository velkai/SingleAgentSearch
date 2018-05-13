#include <iostream>
#include "Timer.h"
#include "InefficientAStar.h"
#include "AStar.h"
#include "STP.h"
#include "PDB.h"
#include "MaxHeuristic.h"
#include "ManhattanDistance.h"
#include "GridMap.h"

void TEST_GMMOVEDIR_ENUM();

int main()
{
	TEST_GMMOVEDIR_ENUM();

	return 0;
}

void TEST_GMMOVEDIR_ENUM()
{
	GridMap environment;
	GMState s1(60, 0);
	GMState s2(60, 1);
	environment.Import("test.map");

	std::vector<GMMoveDir> operators;
	environment.GetOperators(s1, operators);
	std::cout << "s1 operators:\n";
	for (auto i : operators)
	{
		std::cout << i << "\n";
	}


	std::cout << "\ns2 operators:\n";
	operators.clear();
	environment.GetOperators(s2, operators);
	for (auto i : operators)
	{
		std::cout << i << "\n";
	}
}