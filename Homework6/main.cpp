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
	GMState s1(62, 0);
	GMState s2(62, 3);
	environment.Import("test.map");

	environment.PrintState(s1);
	std::cout << "\n\n\n";
	environment.PrintState(s2);
	std::cout << "\n\n\n";

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

	std::vector<GMState> successors;
	environment.GetSuccessors(s2, successors);
	environment.PrintStates(successors);
}