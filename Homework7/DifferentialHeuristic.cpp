#include "DifferentialHeuristic.h"

DifferentialHeuristic::DifferentialHeuristic(GridState &pivot)
{
	this->pivot = pivot;
	AStar<Grid, GridState, GridAction> a;
}