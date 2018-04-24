#include "heuristic.h"

void print1(STPState &s);

heuristic::heuristic()
{
	FCOST = GCOST = HCOST = 0;
}

ManhattanDistance::ManhattanDistance() : heuristic()
{

}

void ManhattanDistance::updateFCost(STPState &s, std::deque<STPState> &path)
{
	updateGCost(path);
	updateHCost(s);
	FCOST = GCOST + HCOST;
}

void ManhattanDistance::updateGCost(std::deque<STPState> &path)
{
	GCOST = path.size();
}

void ManhattanDistance::updateHCost(STPState &s)
{
	HCOST = 0; // reset hcost back to 0
	for (int w = 0; w < 3; ++w)
	{
		for (int h = 0; h < 5; ++h)
		{
			if (s.tiles[w][h] != 0)
				HCOST += DISTANCE_FROM_GOAL(w, h, s.tiles[w][h]);
		}
	}
}

int ManhattanDistance::DISTANCE_FROM_GOAL(int x, int y, int value)
{
	int goal_x, goal_y;
	goal_x = value % 3;
	goal_y = value / 3;

	return abs(goal_x - x) + abs(goal_y - y);
}

PatternDatabase::PatternDatabase()
{
	A = new uint8_t[3603600];
	B = new uint8_t[32432400];
	ASize = BSize = 0;
	INITIALIZE_ARRAYS();

	FCOST = GCOST = HCOST = 0;

	std::cout << "Building A... ";
	BUILD_PDB_A();
	std::cout << "Complete\n";
	std::cout << "Building B... ";
	BUILD_PDB_B();
	std::cout << "Complete\n";

	std::cout << "Success\n";
}

bool PatternDatabase::CONTAINED(char c, uint64_t rank)
{
	if (c == 'A')
	{
		if (A[rank] != 255) return true;
	}
	else if (c == 'B')
	{
		if (B[rank] != 255) return true;
	}
	return false;
}
void PatternDatabase::updateFCost(STPState &s, std::deque<STPState> &path)
{

}

void PatternDatabase::updateGCost(std::deque<STPState> &path)
{

}

void PatternDatabase::updateHCost(STPState &s)
{
	uint64_t *rank = r.GetPDBRank(s);
	bool A_LARGER = rank[0] >= rank[1];
	if (A_LARGER) HCOST = A[rank[0]];
	else HCOST = B[rank[1]];
}

void PatternDatabase::INITIALIZE_ARRAYS()
{
	for (int i = 0; i < 32432400; ++i)
	{
		if(i < 3603600) A[i] = 255;
		B[i] = 255;
	}
}

STPSlideDir PatternDatabase::OPPOSITE(STPSlideDir o)
{
	if (o == kUp)
	{
		return kDown;
	}
	if (o == kDown)
	{
		return kUp;
	}
	if (o == kLeft)
	{
		return kRight;
	}
	if (o == kRight)
	{
		return kLeft;
	}
	return kNone;
}

void PatternDatabase::BUILD_PDB_A()
{
	STP puzzle;
	uint64_t rank;

	std::deque<PDB_BUILD_NODE> q;

	// if a node is on the queue, it has been added to the pdb and is waiting for its children to be expanded

	PDB_BUILD_NODE GOAL; GOAL.s; GOAL.depth = 0;
	PDB_BUILD_NODE CURSOR;

	rank = r.GetPDBRank(GOAL.s)[0];
	A[rank] = GOAL.depth;
	q.push_back(GOAL);

	while (!q.empty())
	{
		CURSOR = q.front();
		q.pop_front();
		// force stuff to go out of scope so it isn't my fault when I run out of RAM
		{
			std::vector<STPSlideDir> operators;
			puzzle.GetOperators(CURSOR.s, operators);
			for (auto o : operators)
			{
				PDB_BUILD_NODE temp = CURSOR;

				puzzle.ApplyOperator(temp.s, o);
				++temp.depth;
				
				rank = r.GetPDBRank(temp.s)[0];
				if (!CONTAINED('A', rank))
				{
					q.push_back(temp);
					A[rank] = temp.depth;
				}
			}
		}
	}
}

void PatternDatabase::BUILD_PDB_B()
{
	STP puzzle;
	uint64_t rank;

	std::deque<PDB_BUILD_NODE> q;

	// if a node is on the queue, it has been added to the pdb and is waiting for its children to be expanded

	PDB_BUILD_NODE GOAL; GOAL.s; GOAL.depth = 0;
	PDB_BUILD_NODE CURSOR;

	rank = r.GetPDBRank(GOAL.s)[1];
	B[rank] = GOAL.depth;
	q.push_back(GOAL);

	while (!q.empty())
	{
		CURSOR = q.front();
		q.pop_front();
		// force stuff to go out of scope so it isn't my fault when I run out of RAM
		{
			std::vector<STPSlideDir> operators;
			puzzle.GetOperators(CURSOR.s, operators);
			for (auto o : operators)
			{
				PDB_BUILD_NODE temp = CURSOR;

				puzzle.ApplyOperator(temp.s, o);
				++temp.depth;

				rank = r.GetPDBRank(temp.s)[1];
				if (!CONTAINED('B', rank))
				{
					q.push_back(temp);
					B[rank] = temp.depth;
				}
			}
		}
	}
}

void print1(STPState &s)
{
	std::cout << " ___________ \n|           |\n";
	for (int h = 0; h < 5; ++h)
	{
		std::cout << "| ";
		for (int w = 0; w < 3; ++w)
		{
			std::cout << " ";
			if (s.tiles[w][h] > 9)
			{
				std::cout << s.tiles[w][h];
			}
			else std::cout << s.tiles[w][h] << " ";
		}
		std::cout << " |\n";
	}
	std::cout << "|___________|\n";
}