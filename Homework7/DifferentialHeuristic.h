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
	DifferentialHeuristic(const char *filename, GridState &pivot);
	DifferentialHeuristic(const char *filename);
	float h(const GridState &, const GridState &);
private:
	GridState pivot;
	std::unordered_map<GridState, float> dists;
};