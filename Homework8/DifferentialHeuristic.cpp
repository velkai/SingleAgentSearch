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

	for (int i = 0; i < s.size(); ++i)
	{
		for (int j = i; j < s.size(); ++j)
		{
			if (i == j) continue;
			for (int k = 0; k < PIVOTS.size(); ++k)
			{
				Q.at(k) += PIVOTS.at(k).h(s.at(i), s.at(j));
			}
		}
	}

	// pick the 5 most optimal DH
	for (int c = 0; c < 5; ++c)
	{
		float GREATEST = 0;

		int p = 0;
		int tmp_Q = 0;
		int tmp_P = 0;

		for (int q = 0; q < Q.size(); ++q)
		{
			if (Q.at(q) > GREATEST)
			{
				tmp_Q = q;
				tmp_P = p;
			}
			++p;
		}

		dh.AddHeuristic(&PIVOTS.at(tmp_P));
		Q.assign(tmp_Q, -1);
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