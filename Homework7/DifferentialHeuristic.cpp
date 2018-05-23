#include "DifferentialHeuristic.h"

DifferentialHeuristic::DifferentialHeuristic(const char *filename, GridState &pivot)
{
	Grid env(filename);
	this->pivot = pivot;
	AStar<Grid, GridState, GridAction> a;
	OctileDistance octile;
	dists = a.GetCosts(&env, pivot, &octile);
}

DifferentialHeuristic::DifferentialHeuristic(const char *filename)
{
	Grid env(filename);
	GridState tmp(rand()%env.GetWidth(), rand()%env.GetHeight());
	while (env.Blocked(tmp))
	{
		tmp.x = rand() % env.GetWidth();
		tmp.y = rand() % env.GetHeight();
	}
	this->pivot = tmp;
	AStar<Grid, GridState, GridAction> a;
	OctileDistance octile;
	dists = a.GetCosts(&env, this->pivot, &octile);
}

float DifferentialHeuristic::h(const GridState &s1, const GridState &s2)
{
	return abs(dists.at(s1) - dists.at(s2));
}