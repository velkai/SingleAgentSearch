#include "heuristic.h"

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
	std::cout << "Building PDB...\n";

	A = new uint8_t[3603600];
	B = new uint8_t[32432400];
	ASize = BSize = 0;
	INITIALIZE_ARRAYS();

	Ranking *r = new Ranking();
	STPState *s = new STPState(), *GOAL = new STPState();
	STP *puzzle = new STP();
	//BFS *bfs;
	DFID *dfid;
	std::vector<STPSlideDir> *operators;
	STPSlideDir previous = kNone;

	uint64_t *temp = new uint64_t[2];

	while (ASize != 3603600 && BSize != 32432400)
	{
		// so I don't lose my mind waiting
		if (ASize == 720720) std::cout << "A at 20%\n";
		if (ASize == 1441440) std::cout << "A at 40%\n";
		if (ASize == 2162160) std::cout << "A at 60%\n";
		if (ASize == 2882880) std::cout << "A at 80%\n";
		if (ASize == 3603599) std::cout << "A at 100%\n";
		if (BSize == 6486480) std::cout << "B at 20%\n";
		if (BSize == 12972960) std::cout << "B at 40%\n";
		if (BSize == 19459440) std::cout << "B at 60%\n";
		if (BSize == 25945920) std::cout << "B at 80%\n";
		if (BSize == 32432399) std::cout << "B at 99%\n";

		operators = new std::vector<STPSlideDir>();
		//bfs = new BFS();
		dfid = new DFID();
		puzzle->GetOperators(*s, *operators);
		temp = r->GetPDBRank(*s);

		int index = rand() % operators->size();
		while (operators->at(index) == OPPOSITE(previous))
		{
			index = rand() % operators->size();
		}
		puzzle->ApplyOperator(*s, operators->at(index));

		bool a, b, c, d;
		a = ASize != 3603600;
		b = BSize != 32432400;
		c = !CONTAINED('A', temp[0]);
		d = !CONTAINED('B', temp[1]);

		if(a && c || b && d)
		{
			uint8_t depth = dfid->GetPath(*puzzle, *GOAL, *s);
			if (a && c)
			{
				std::cout << "A\n";
				A[temp[0]] = depth;
				++ASize;
			}
			if (b && d)
			{
				std::cout << "B\n";
				B[temp[1]] = depth;
				++BSize;
			}
		}

		delete[] temp;
		delete operators;
		//delete bfs;
		delete dfid;
	}

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