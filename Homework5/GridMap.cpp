#include "GridMap.h"

std::ostream& operator<<(std::ostream& out, const GMState& s)
{
	out << "(" << s.x << ", " << s.y << ")";
	return out;
}

bool operator==(const GMState &s1, const GMState &s2)
{
	return s1.x == s2.x && s1.y == s2.y;
}

GMState::GMState()
{
	x = y = -1;
}

GMState::GMState(int x, int y)
{
	this->x = x;
	this->y = y;
}

void GMState::operator=(const GMState &source)
{
	this->x = source.x;
	this->y = source.y;
}

void GridMap::Import(const char *filename)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
		std::cout << "FNF\n";
	}
	else std::cout << "Success\n";
	int temp = 0;
	while (temp < 4)
	{
		char c = fgetc(in);
		std::cout << (char)c;
		if (c == '\n') ++temp;
	}

	grid.push_back(std::vector<bool>());
	while (!feof(in))
	{
		char c = fgetc(in);
		if (c == '\n')
		{
			grid.push_back(std::vector<bool>());
		}
		else if (c == '@' || c == 'T')
		{
			grid.back().push_back(false);
		}
		else if (c == '.')
		{
			grid.back().push_back(true);
		}
	}

	fclose(in);
}

void GridMap::GetSuccessors(GMState &s, std::vector<GMState> &states)
{
	if (s.x != 0)
	{
		if (grid[s.y][s.x - 1])
		{
			ApplyOperator(s, kLeft);
			states.push_back(s);
			UndoOperator(s, kLeft);
		}
	}
	if (s.x != grid.at(0).size() - 1)
	{
		if (grid[s.y][s.x + 1])
		{
			ApplyOperator(s, kRight);
			states.push_back(s);
			UndoOperator(s, kRight);
		}
	}
	if (s.y != 0)
	{
		if (grid[s.y - 1][s.x])
		{
			ApplyOperator(s, kUp);
			states.push_back(s);
			UndoOperator(s, kUp);
		}
	}
	if (s.y != grid.size())
	{
		if (grid[s.y + 1][s.x])
		{
			ApplyOperator(s, kDown);
			states.push_back(s);
			UndoOperator(s, kDown);
		}
	}
}

void GridMap::GetOperators(GMState &s, std::vector<STPSlideDir> &operators)
{
	if (s.x != 0)
	{
		operators.push_back(kLeft);
	}
	if (s.x != grid.at(0).size() - 1)
	{
		operators.push_back(kRight);
	}
	if (s.y != 0)
	{
		operators.push_back(kUp);
	}
	if (s.y != grid.size())
	{
		operators.push_back(kDown);
	}
}

void GridMap::ApplyOperator(GMState &s, STPSlideDir o)
{
	switch (o)
	{
	case kUp: --s.y;
		break;
	case kDown: ++s.y;
		break;
	case kLeft: --s.x;
		break;
	case kRight: ++s.x;
		break;
	case kNone:
		break;
	}
}

void GridMap::UndoOperator(GMState &s, STPSlideDir o)
{
	switch (o)
	{
	case kUp: ApplyOperator(s, kDown);
		break;
	case kDown: ApplyOperator(s, kUp);
		break;
	case kLeft: ApplyOperator(s, kRight);
		break;
	case kRight: ApplyOperator(s, kLeft);
		break;
	case kNone:
		break;
	}
}

void GridMap::InvertOperator(STPSlideDir &o)
{
	switch (o)
	{
	case kUp: o = kDown;
		break;
	case kDown: o = kUp;
		break;
	case kLeft: o = kRight;
		break;
	case kRight: o = kLeft;
		break;
	case kNone:
		break;
	}
}