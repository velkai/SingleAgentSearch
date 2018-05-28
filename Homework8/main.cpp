//
//  main.cpp
//  HW1
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "STP.h"
#include "Timer.h"
#include "BFS.h"
#include "ManhattanDistance.h"
#include "MaxHeuristic.h"
#include "AStar.h"
#include "Grid.h"
#include "ScenarioLoader.h"
#include "OctileDistance.h"
#include "DifferentialHeuristic.h"

STPState GenerateInstance(int walkDepth)
{
	STPState start, goal;
	STP stp;
	ManhattanDistance md;
	DoRandomWalkOperators(stp, start, walkDepth);
	Timer t;
	std::vector<STPSlideDir> path;
	
	return start;
}

void Solve(STPState start, Heuristic<STPState> *h)
{
	STPState goal;
	STP stp;
	Timer t;
	AStar<STP, STPState, STPSlideDir> astar;
	std::vector<STPSlideDir> path;
	std::vector<STPState> statePath;

	printf("Starting A*:\n");
	t.StartTimer();
	astar.GetPath(&stp, start, goal, h, statePath);
	t.EndTimer();
	printf("%1.2fs elapsed; solution length %lu\n", t.GetElapsedTime(), statePath.size()-1);
}

void TestSTP()
{
	std::vector<STPState> instances;
	for (int x = 10; x < 200; x+=10)
	{
		instances.push_back(GenerateInstance(x));
	}
	instances.push_back(GenerateInstance(10000000));
	
	std::vector<int> pattern1 = {0, 1, 2, 3, 4, 5};
	std::vector<int> pattern2 = {0, 9, 10, 11, 12, 13, 14};
	
	ManhattanDistance md;
	
	for (auto s : instances)
	{
		printf("Solving with MD\n");
		Solve(s, &md);
	}
}

float GetPathCost(Grid &grid, const std::vector<GridState> &path)
{
	float result = 0;
	
	for (int x = 0; x+1 < path.size(); x++)
		result += grid.GetCost(path[x], path[x+1]);
	
	return result;
}

void TestGrid(const char *map, const char *scene)
{
	Grid grid(map);
	ScenarioLoader scenarios(scene);
	AStar<Grid, GridState, GridAction> astar;
	std::vector<GridState> path;
	OctileDistance octile;
	for (int x = 0; x < scenarios.GetNumExperiments(); x++)
	{
		GridState from(scenarios.GetNthExperiment(x).GetStartX(), scenarios.GetNthExperiment(x).GetStartY());
		GridState to(scenarios.GetNthExperiment(x).GetGoalX(), scenarios.GetNthExperiment(x).GetGoalY());
		std::cout << "Searching from " << from << " to " << to << "\n";
		astar.GetPath(&grid, from, to, &octile, path);
		printf("Optimal cost is %f; should be %f\n", GetPathCost(grid, path), scenarios.GetNthExperiment(x).GetDistance());
	}
}


int main(int argc, const char * argv[])
{
	//TestSTP();
	//TestGrid("lak303d.map", "lak303d.map.scen");
	Grid grid("lak303d.map");
	ScenarioLoader scenarios("lak303d.map.scen");
	AStar<Grid, GridState, GridAction> astar;
	std::vector<GridState> path;
	DifferentialHeuristic r1("lak303d.map");
	DifferentialHeuristic r2("lak303d.map");
	DifferentialHeuristic r3("lak303d.map");
	DifferentialHeuristic r4("lak303d.map");
	DifferentialHeuristic r5("lak303d.map");
	OctileDistance octile;
	MaxHeuristic<GridState> h;
	h.AddHeuristic(&octile);
	h.AddHeuristic(&r1);
	h.AddHeuristic(&r2);
	h.AddHeuristic(&r3);
	h.AddHeuristic(&r4);
	h.AddHeuristic(&r5);

	OptimizedDH test("lak303d.map");

	
	for (int x = 0; x < scenarios.GetNumExperiments(); x++)
	{
		GridState from(scenarios.GetNthExperiment(x).GetStartX(), scenarios.GetNthExperiment(x).GetStartY());
		GridState to(scenarios.GetNthExperiment(x).GetGoalX(), scenarios.GetNthExperiment(x).GetGoalY());
		std::cout << "Searching from " << from << " to " << to << "\n";
		std::cout << "Octile distance: ";
		astar.GetPath(&grid, from, to, &octile, path);
		std::cout << "Octile distance w/ random pivots: ";
		astar.GetPath(&grid, from, to, &h, path);
	}

	return 0;
}
