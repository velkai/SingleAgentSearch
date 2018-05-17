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
void TEST_ASTAR();
void TEST_ASTAR_GRID();

int main()
{
	//TEST_GMMOVEDIR_ENUM();
	//TEST_ASTAR();
	TEST_ASTAR_GRID();

	return 0;
}

void TEST_GMMOVEDIR_ENUM()
{
	GridMap environment;
	GMState s1(57, 0);
	GMState s2(62, 3);
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

	std::vector<GMState> successors;
	environment.GetSuccessors(s1, successors);
	environment.GetSuccessors(s2, successors);
	environment.PrintStates(successors);
}

void TEST_ASTAR()
{
	AStar<STP, STPState, STPSlideDir> a;
	STP puzzle;
	STPState start, goal;
	DoRandomWalkOperators(puzzle, start, 15);
	ManhattanDistance h;

	a.GetPath(start, goal, h);
}

void TEST_ASTAR_GRID()
{
	AStar<GridMap, GMState, GMMoveDir> a;
	GridMap environment;
	environment.Import("test.map");
	GMState start(100, 5);
	GMState goal(91, 187);
	a.SetMap(environment);
	ManhattanDistance h;
	h.SetGoal(goal);
	//environment.PrintState(start);
	//environment.PrintState(goal);

	Timer t;
	t.StartTimer();
	std::vector<GMMoveDir> path = a.GetPath(start, goal, h);
	t.EndTimer();

	GMState s(91, 187);
	std::vector<GMState> p;
	p.push_back(s);
	for (auto i : path)
	{
		environment.UndoOperator(s, i);
		p.push_back(s);
	}
	//environment.PrintStates(p);
	std::cout << "Elapsed time: " << t.GetElapsedTime() << "s\n";
}