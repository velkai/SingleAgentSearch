#include <iostream>
#include "Timer.h"
#include "InefficientAStar.h"
#include "STP.h"
#include "PDB.h"
#include "MaxHeuristic.h"
#include "AStar.hpp"

int main() 
{
	ManhattanDistance h;
	//InefficientAStar a;
    AStar a;

	STP puzzle;
	STPState s;
	DoRandomWalkOperators(puzzle, s, 150);

	STPState goal;
	std::vector<STPSlideDir> path = a.GetPath(s, goal, h);

	std::cout << "GOAL - ";
	for (auto i : path)
	{
		if(i == 0) std::cout << "UP - ";
		else if (i == 1) std::cout << "DOWN - ";
		else if (i == 2) std::cout << "RIGHT - ";
		else if (i == 3) std::cout << "LEFT - ";
		else if (i == 4) std::cout << "ROOT\n";
	}
	std::cout << std::endl;

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
	mh.AddHeuristic(&h);
	mh.AddHeuristic(&h1);
	mh.AddHeuristic(&h2);


	path = a.GetPath(s, goal, mh);

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

	return 0;
}
