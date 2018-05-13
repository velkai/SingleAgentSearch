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
			ApplyOperator(s, gLeft);
			states.push_back(s);
			UndoOperator(s, gLeft);
		}
	}
	if (s.x != grid.at(0).size() - 1)
	{
		if (grid[s.y][s.x + 1])
		{
			ApplyOperator(s, gRight);
			states.push_back(s);
			UndoOperator(s, gRight);
		}
	}
	if (s.y != 0)
	{
		if (grid[s.y - 1][s.x])
		{
			ApplyOperator(s, gUp);
			states.push_back(s);
			UndoOperator(s, gUp);
		}
	}
	if (s.y != grid.size())
	{
		if (grid[s.y + 1][s.x])
		{
			ApplyOperator(s,gDown);
			states.push_back(s);
			UndoOperator(s, gDown);
		}
	}
}

void GridMap::GetOperators(GMState &s, std::vector<GMMoveDir> &operators)
{
	if (s.x != 0)
	{
		operators.push_back(gLeft);
	}
	if (s.x != grid.at(0).size() - 1)
	{
		operators.push_back(gRight);
	}
	if (s.y != 0)
	{
		operators.push_back(gUp);
	}
	if (s.y != grid.size())
	{
		operators.push_back(gDown);
	}
	if (s.x != 0 && s.y != 0)
	{
		operators.push_back(gUpLeft);
	}
	if (s.x != 0 && s.y != grid.size())
	{
		operators.push_back(gDownLeft);
	}
	if (s.x != grid.at(0).size() - 1 && s.y != 0)
	{
		operators.push_back(gUpRight);
	}
	if (s.x != grid.at(0).size() - 1 && s.y != grid.size())
	{
		operators.push_back(gDownRight);
	}
}

void GridMap::ApplyOperator(GMState &s, GMMoveDir o)
{
	switch (o)
	{
	case gUp: --s.y;
		break;
	case gDown: ++s.y;
		break;
	case gLeft: --s.x;
		break;
	case gRight: ++s.x;
		break;
	case gNone:
		break;
	}
}

void GridMap::UndoOperator(GMState &s, GMMoveDir o)
{
	switch (o)
	{
	case gUp: ApplyOperator(s, gDown);
		break;
	case gDown: ApplyOperator(s, gUp);
		break;
	case gLeft: ApplyOperator(s, gRight);
		break;
	case gRight: ApplyOperator(s, gLeft);
		break;
	case gNone:
		break;
	}
}

void GridMap::InvertOperator(GMMoveDir &o)
{
	switch (o)
	{
	case gUp: o = gDown;
		break;
	case gDown: o = gUp;
		break;
	case gLeft: o = gRight;
		break;
	case gRight: o = gLeft;
		break;
	case gNone:
		break;
	}
}