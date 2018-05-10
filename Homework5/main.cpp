#include <iostream>
#include "Timer.h"
#include "InefficientAStar.h"
#include "AStar.h"
#include "STP.h"
#include "PDB.h"
#include "MaxHeuristic.h"
#include "ManhattanDistance.h"
#include "GridMap.h"

void print_test(STPState &s);

void TEST_INEFFICIENT_A_STAR();
void TEST_NODE_HASH();
void TEST_A_STAR();
void TEST_GRID_MAP(const char *filename);
void TEST_GRID_MAP_A_STAR(const char *filename, int sx, int sy, int gx, int gy);

void GenerateInstance(int walkDepth)
{
	STPState start, goal;
	STP stp;
	AStar<STP, STPState, STPSlideDir> a;
	ManhattanDistance md;
	DoRandomWalkOperators(stp, start, walkDepth);
	Timer t;
	std::vector<STPSlideDir> path;

	std::cout << start << "\n";

	printf("Starting AStar (MD):\n");
	t.StartTimer();
	a.GetPath(start, goal, md);
	t.EndTimer();
	printf("%1.2fs elapsed\n", t.GetElapsedTime());

	printf("Starting AStar (PDB):\n");

	std::vector<int> PDB_TILES;
	PDB_TILES.push_back(0);
	PDB_TILES.push_back(1);
	PDB_TILES.push_back(2);
	PDB_TILES.push_back(3);
	PDB_TILES.push_back(4);
	PDB_TILES.push_back(5);
	PDB h1(PDB_TILES);

	PDB_TILES.clear();
	PDB_TILES.push_back(0);
	PDB_TILES.push_back(9);
	PDB_TILES.push_back(10);
	PDB_TILES.push_back(11);
	PDB_TILES.push_back(12);
	PDB_TILES.push_back(13);
	PDB_TILES.push_back(14);
	PDB h2(PDB_TILES);

	MaxHeuristic mh;
	mh.AddHeuristic(&md);
	mh.AddHeuristic(&h1);
	mh.AddHeuristic(&h2);


	path = a.GetPath(start, goal, mh);

	std::cout << "GOAL - ";
	for (auto i : path)
	{
		if (i == 0) std::cout << "UP - ";
		else if (i == 1) std::cout << "DOWN - ";
		else if (i == 2) std::cout << "RIGHT - ";
		else if (i == 3) std::cout << "LEFT - ";
		else if (i == 4) std::cout << "ROOT\n";
	}
	std::cout << std::endl;
}

void GenerateInefficientInstance(int walkDepth)
{
	STPState start, goal;
	STP stp;
	InefficientAStar a;
	ManhattanDistance md;
	DoRandomWalkOperators(stp, start, walkDepth);
	Timer t;
	std::vector<STPSlideDir> path;

	std::cout << start << "\n";

	printf("Starting AStar (MD):\n");
	t.StartTimer();
	a.GetPath(start, goal, md);
	t.EndTimer();
	printf("%1.2fs elapsed\n", t.GetElapsedTime());

	printf("Starting AStar (PDB):\n");
	std::vector<int> PDB_TILES;
	PDB_TILES.push_back(0);
	PDB_TILES.push_back(1);
	PDB_TILES.push_back(2);
	PDB_TILES.push_back(3);
	PDB_TILES.push_back(4);
	PDB_TILES.push_back(5);
	PDB h1(PDB_TILES);

	PDB_TILES.clear();
	PDB_TILES.push_back(0);
	PDB_TILES.push_back(9);
	PDB_TILES.push_back(10);
	PDB_TILES.push_back(11);
	PDB_TILES.push_back(12);
	PDB_TILES.push_back(13);
	PDB_TILES.push_back(14);
	PDB h2(PDB_TILES);

	MaxHeuristic mh;
	mh.AddHeuristic(&md);
	mh.AddHeuristic(&h1);
	mh.AddHeuristic(&h2);


	path = a.GetPath(start, goal, mh);

	std::cout << "GOAL - ";
	for (auto i : path)
	{
		if (i == 0) std::cout << "UP - ";
		else if (i == 1) std::cout << "DOWN - ";
		else if (i == 2) std::cout << "RIGHT - ";
		else if (i == 3) std::cout << "LEFT - ";
		else if (i == 4) std::cout << "ROOT\n";
	}
	std::cout << std::endl;
}

int main() 
{
	std::cout << "---------------------------------------TESTING INEFFICIENT ASTAR-----------------------------------------\n";
	TEST_INEFFICIENT_A_STAR();
	//TEST_NODE_HASH();
	std::cout << "----------------------------------------TESTING EFFICIENT ASTAR----------------------------------------\n";
	TEST_A_STAR();
	//TEST_GRID_MAP("test.map");
	std::cout << "-----------------------------------------TESTING GRID MAP ASTAR---------------------------------------\n";
	TEST_GRID_MAP_A_STAR("test.map", 60, 4, 60, 20);

	return 0;
}

void TEST_INEFFICIENT_A_STAR()
{
	for (int x = 10; x < 200; x += 10)
	{
		GenerateInefficientInstance(x);
	}
	GenerateInefficientInstance(10000000);
}

void TEST_NODE_HASH()
{
	STP environment;
	STPState s;
	std::vector<size_t> hashes;
	std::vector<STPState> explored;
	std::unordered_map<std::size_t, STPState> originals;
	bool quit;

	while (sizeof(hashes) < 3000000000 && sizeof(explored) < 4000000000)
	{
		quit = false;
		std::vector<STPSlideDir> operators;
		environment.GetOperators(s, operators);
		environment.ApplyOperator(s, operators.at(rand()%operators.size()));
		for (auto i : explored)
		{
			if (s == i)
			{
				quit = true;
				break;
			}
		}
		if (quit) continue;
		explored.push_back(s);

		size_t temp = std::hash<STPState>()(s);
		std::cout << temp;
		for (auto i : hashes)
		{
			if (i == temp)
			{
				std::cout << ": ERROR\n";
				print_test(s);
				std::cout << "------------------------------------------------\n";
				print_test(originals.at(temp));
				continue;
			}
		}
		std::cout << std::endl;
		hashes.push_back(temp);
		originals.insert(std::pair<std::size_t, STPState>(temp, s));
	}
}

void TEST_A_STAR()
{
	for (int x = 10; x < 200; x += 10)
	{
		GenerateInstance(x);
	}
	GenerateInstance(10000000);
}

void TEST_GRID_MAP(const char *filename)
{
	GridMap g;
	g.Import(filename);
	GMState s1(60, 4);
	GMState s2(58, 10);

	std::vector<STPSlideDir> operators;
	g.GetOperators(s1, operators);
	for (auto i : operators)
	{
		std::cout << i << "\n";
	}

	ManhattanDistance h;
	h.SetGoal(s2);
	std::cout << h.h(s1) << "\n";
}

void TEST_GRID_MAP_A_STAR(const char *filename, int sx, int sy, int gx, int gy)
{
	GridMap g;
	GMState s1(sx, sy);
	GMState s2(gx, gy);
	ManhattanDistance h;
	h.SetGoal(s2);

	g.Import(filename);
	AStar<GridMap, GMState, STPSlideDir> a;

	a.SetMap(g);
	std::vector<STPSlideDir> path = a.GetPath(s1, s2, h);

	std::cout << "GOAL - ";
	for (auto i : path)
	{
		if (i == 0) std::cout << "UP - ";
		else if (i == 1) std::cout << "DOWN - ";
		else if (i == 2) std::cout << "RIGHT - ";
		else if (i == 3) std::cout << "LEFT - ";
		else if (i == 4) std::cout << "ROOT\n";
	}
	std::cout << std::endl;
}

void print_test(STPState &s)
{
	for (int w = 0; w < 3; ++w)
	{
		for (int h = 0; h < 5; ++h)
		{
			std::cout << s.tiles[w][h] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}