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
	std::vector<GMMoveDir> operators;
	GetOperators(s, operators);
	for (auto i : operators)
	{
		ApplyOperator(s, i);
		states.push_back(s);
		UndoOperator(s, i);
	}
}

void GridMap::GetOperators(GMState &s, std::vector<GMMoveDir> &operators)
{
	bool L = s.x != 0;
	bool R = s.x != grid.at(0).size() - 1;
	bool U = s.y != 0;
	bool D = s.y != grid.size()-1;

	if (L)
	{
		if(grid[s.y][s.x - 1]) operators.push_back(gLeft);
	}
	if (R)
	{
		if (grid[s.y][s.x + 1]) operators.push_back(gRight);
	}
	if (U)
	{
		if (grid[s.y - 1][s.x]) operators.push_back(gUp);
	}
	if (D)
	{
		if (grid[s.y + 1][s.x]) operators.push_back(gDown);
	}
	if (L && U)
	{
		if (grid[s.y - 1][s.x - 1]
			&& grid[s.y][s.x - 1]
			&& grid[s.y - 1][s.x]) operators.push_back(gUpLeft);
	}
	if (L && D)
	{
		if (grid[s.y + 1][s.x - 1] + 1
			&& grid[s.y][s.x - 1]
			&& grid[s.y + 1][s.x]) operators.push_back(gDownLeft);
	}
	if (R && U)
	{
		if (grid[s.y - 1][s.x + 1]
			&& grid[s.y][s.x + 1]
			&& grid[s.y - 1][s.x]) operators.push_back(gUpRight);
	}
	if (R && D)
	{
		if (grid[s.y + 1][s.x + 1]
			&& grid[s.y][s.x + 1]
			&& grid[s.y + 1][s.x]) operators.push_back(gDownRight);
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
	case gUpLeft: --s.y; --s.x;
		break;
	case gUpRight: --s.y; ++s.x;
		break;
	case gDownLeft: ++s.y; --s.x;
		break;
	case gDownRight: ++s.y; ++s.x;
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
	case gUpLeft: ApplyOperator(s, gDownRight);
		break;
	case gUpRight: ApplyOperator(s, gDownLeft);
		break;
	case gDownLeft: ApplyOperator(s, gUpRight);
		break;
	case gDownRight: ApplyOperator(s, gUpLeft);
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
	case gUpLeft: o = gDownRight;
		break;
	case gDownLeft: o = gUpRight;
		break;
	case gUpRight: o = gDownLeft;
		break;
	case gDownRight: o = gDownLeft;
		break;
	}
}

void GridMap::PrintState(GMState &s)
{
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			if (grid[i][j])
			{
				if (s.x == j && s.y == i) std::cout << "O";
				else std::cout << " ";
			}
			else
			{
				if (s.x == j && s.y == i) std::cout << "e";
				else std::cout << "X";
			}
		}
		std::cout << "\n";
	}
}

void GridMap::PrintStates(std::vector<GMState> &s)
{
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			if (grid[i][j])
			{
				bool found = false;
				for (auto state : s)
				{
					if (state.x == j && state.y == i)
					{
						found = true;
						break;
					}
				}
				if (found) std::cout << ".";
				else std::cout << " ";
			}
			else
			{
				bool found = false;
				for (auto state : s)
				{
					if (state.x == j && state.y == i)
					{
						found = true;
						break;
					}
				}
				if (found) std::cout << ".";
				else std::cout << "X";
			}
		}
		std::cout << "\n";
	}
}

double GridMap::GetCost(GMMoveDir o)
{
	if ((int)o == 4) return 0;
	if ((int)o > 4) return DiagCost;
	else return CardCost;
}