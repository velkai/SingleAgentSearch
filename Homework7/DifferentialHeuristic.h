#pragma once

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

class DifferentialHeuristic : public Heuristic<GridState>
{
public:
	DifferentialHeuristic(GridState &pivot);
	int GetDistance(GridState &index);

private:
	GridState pivot;
	std::unordered_map<GridState, float> dists;
};