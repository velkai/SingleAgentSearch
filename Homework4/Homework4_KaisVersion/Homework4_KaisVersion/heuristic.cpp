#include "heuristic.h"
#include "Timer.h"

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

void PatternDatabase::printTests()
{
	std::cout << "A\n";
	std::cout << 53 << " : " << (int)A[53] << "\n";
	std::cout << 78 << " : " << (int)A[78] << "\n";
	std::cout << 140 << " : " << (int)A[140] << "\n";
	std::cout << 3662 << " : " << (int)A[3662] << "\n";
	std::cout << 8412 << " : " << (int)A[8412] << "\n";
	std::cout << 13285 << " : " << (int)A[13285] << "\n"; 
	std::cout << 44669 << " : " << (int)A[44669] << "\n";
	std::cout << 51069 << " : " << (int)A[51069] << "\n";
	std::cout << 69998 << " : " << (int)A[69998] << "\n";
	std::cout << 108545 << " : " << (int)A[108545] << "\n";
	std::cout << 146533 << " : " << (int)A[146533] << "\n";
	std::cout << 184448 << " : " << (int)A[184448] << "\n";
	std::cout << 207344 << " : " << (int)A[207344] << "\n";
	std::cout << 208040 << " : " << (int)A[208040] << "\n";
	std::cout << 116888 << " : " << (int)A[116888] << "\n";
	std::cout << 40866 << " : " << (int)A[40866] << "\n";
	std::cout << 7331 << " : " << (int)A[7331] << "\n";
	std::cout << 62 << " : " << (int)A[62] << "\n";

	std::cout << "B\n";
	std::cout << 1 << " : " << (int)B[1] << "\n";
		std::cout << 54 << " : " << (int)B[54] << "\n";
		std::cout << 98 << " : " << (int)B[98] << "\n";
		std::cout << 184 << " : " << (int)B[184] << "\n";
		std::cout << 294 << " : " << (int)B[294] << "\n";
		std::cout << 17564 << " : " << (int)B[17564] << "\n";
		std::cout << 29623 << " : " << (int)B[29623] << "\n";
		std::cout << 41898 << " : " << (int)B[41898] << "\n";
		std::cout << 68189 << " : " << (int)B[68189] << "\n";
		std::cout << 266385 << " : " << (int)B[266385] << "\n";
		std::cout << 319689 << " : " << (int)B[319689] << "\n";
		std::cout << 789805 << " : " << (int)B[789805] << "\n";
		std::cout << 1062662 << " : " << (int)B[1062662] << "\n";
		std::cout << 1117571 << " : " << (int)B[1117571] << "\n";
		std::cout << 1453505 << " : " << (int)B[1453505] << "\n";
		std::cout << 1457091 << " : " << (int)B[1457091] << "\n";
		std::cout << 1820909 << " : " << (int)B[1820909] << "\n";
		std::cout << 1730218 << " : " << (int)B[1730218] << "\n";
		std::cout << 1644785 << " : " << (int)B[1644785] << "\n";
		std::cout << 167802 << " : " << (int)B[167802] << "\n";
		std::cout << 133293 << " : " << (int)B[133293] << "\n";
		std::cout << 68521 << " : " << (int)B[68521] << "\n";
		std::cout << 2605 << " : " << (int)B[2605] << "\n";
		std::cout << 508 << " : " << (int)B[508] << "\n";
		std::cout << 252 << " : " << (int)B[252] << "\n";

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