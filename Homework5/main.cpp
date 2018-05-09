#include <iostream>
#include "Timer.h"
#include "InefficientAStar.h"
#include "AStar.h"
#include "STP.h"
#include "PDB.h"
#include "MaxHeuristic.h"
#include "ManhattanDistance.h"

void print_test(STPState &s);

void TEST_INEFFICIENT_A_STAR(int n);
void TEST_NODE_HASH();
void TEST_A_STAR(int n);

int main() 
{
	//TEST_INEFFICIENT_A_STAR(250);
	//TEST_NODE_HASH();
	TEST_A_STAR(400);

	return 0;
}

void TEST_INEFFICIENT_A_STAR(int n)
{
	ManhattanDistance h;
	InefficientAStar a;

	STP puzzle;
	STPState s;
	DoRandomWalkOperators(puzzle, s, n);

	STPState goal;
	std::vector<STPSlideDir> path = a.GetPath(s, goal, h);

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

void TEST_A_STAR(int n)
{
	ManhattanDistance h;
	AStar a;

	STP puzzle;
	STPState s;
	DoRandomWalkOperators(puzzle, s, n);

	STPState goal;
	std::vector<STPSlideDir> path = a.GetPath(s, goal, h);

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