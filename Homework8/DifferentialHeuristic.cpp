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

OptimizedDH::OptimizedDH(const char *filename)
{
	std::vector<float> Q;
	std::vector<GridState> s;
	std::vector<DifferentialHeuristic> PIVOTS;

	for (int i = 0; i < 20; ++i)
	{
		Q.push_back(0);
		s.push_back(RANDOM_POINT(filename));
		PIVOTS.push_back(DifferentialHeuristic(filename));
	}

	std::vector<float>::iterator q = Q.begin(); // Q and PIVOTS must always have the same number of elements
	for (std::vector<GridState>::iterator i = s.begin(); i != s.end(); ++i)
	{
		for (std::vector<GridState>::iterator j(i); j != s.end(); ++j)
		{
			if (i == j) continue;
			for (std::vector<DifferentialHeuristic>::iterator k = PIVOTS.begin(); k != PIVOTS.end(); ++k)
			{
				*q += k->h(*i, *j);
				++q;
			}
		}
	}

	// pick the 5 most optimal DH
	for (int c = 0; c < 5; ++c)
	{
		float GREATEST = 0;
		std::vector<DifferentialHeuristic>::iterator p = PIVOTS.begin();
		std::vector<float>::iterator tmp_Q = Q.begin();
		std::vector<DifferentialHeuristic>::iterator tmp_P = PIVOTS.begin();

		for (q = Q.begin(); q != Q.end(); ++q)
		{
			if (*q > GREATEST)
			{
				tmp_Q = q;
				tmp_P = p;
			}
			++p;
		}

		dh.AddHeuristic(&*tmp_P); // ewwwwwwwww
		Q.erase(tmp_Q);
		PIVOTS.erase(tmp_P);
	}
}

float OptimizedDH::h(const GridState &s1, const GridState &s2)
{
	return dh.h(s1, s2);
}

GridState OptimizedDH::RANDOM_POINT(const char *filename)
{
	Grid env(filename);
	GridState tmp(rand() % env.GetWidth(), rand() % env.GetHeight());
	while (env.Blocked(tmp))
	{
		tmp.x = rand() % env.GetWidth();
		tmp.y = rand() % env.GetHeight();
	}
	return tmp;
}