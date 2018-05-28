//
//  Grid.cpp
//  HW6
//
//  Created by Nathan Sturtevant on 5/18/18.
//  Copyright © 2018 NS Software. All rights reserved.
//

#include "Grid.h"
#include <cassert>

bool operator==(const GridState &a, const GridState &b)
{
	return a.x == b.x && a.y == b.y;
}

std::ostream &operator<<(std::ostream &out, const GridState &s)
{
	out << "(" << s.x << ", " << s.y << ")";
	return out;
}

std::ostream &operator<<(std::ostream &out, const Grid &g)
{
	for (int y = 0; y < g.GetHeight(); y++)
	{
		for (int x = 0; x < g.GetWidth(); x++)
		{
			out << (g.Blocked({x, y})?"X":" ");
		}
		out << "\n";
	}
	return out;
}

Grid::Grid(const char *filename)
{
	FILE* f = fopen(filename, "r");
	if (f == 0)
	{
		assert(!"Can't open file in Grid class; aborting");
	}
	fscanf(f, "type octile\nheight %d\nwidth %d\nmap\n", &height, &width);
	grid.resize(height*width);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char next = fgetc(f);
			if (next == '\n')
			{
				x--;
				continue;
			}
			// Blocked if character is not '.'
			grid[GetIndex({x, y})] = (next != '.');
		}
	}
}

void Grid::GetSuccessors(GridState &s, std::vector<GridState> &states)
{
	static const GridAction acts[] = {kNorth,
		kSouth,
		kEast,
		kWest,
		kNorthEast,
		kNorthWest,
		kSouthEast,
		kSouthWest};
	states.resize(0);
	for (int a = 0; a < 8; a++)
	{
		if (Valid(s, acts[a]))
		{
			states.push_back(s);
			ApplyOperator(states.back(), acts[a]);
		}
	}
}

void Grid::GetOperators(GridState &s, std::vector<GridAction> &operators)
{
	static const GridAction acts[] = {kNorth,
		kSouth,
		kEast,
		kWest,
		kNorthEast,
		kNorthWest,
		kSouthEast,
		kSouthWest};
	operators.resize(0);
	for (int a = 0; a < 8; a++)
	{
		if (Valid(s, acts[a]))
		{
			operators.push_back(acts[a]);
		}
	}
}

void Grid::ApplyOperator(GridState &s, GridAction o)
{
	switch (o)
	{
		case kNorth: s.y--; break;
		case kSouth: s.y++; break;
		case kEast: s.x++; break;
		case kWest: s.x--; break;
		case kNorthEast: s.y--; s.x++; break;
		case kNorthWest: s.y--; s.x--; break;
		case kSouthEast: s.y++; s.x++; break;
		case kSouthWest: s.y++; s.x--; break;
	}
}

void Grid::UndoOperator(GridState &s, GridAction o)
{
	InvertOperator(o);
	ApplyOperator(s, o);
}

void Grid::InvertOperator(GridAction &o)
{
	switch (o)
	{
		case kNorth: o = kSouth; break;
		case kSouth: o = kNorth; break;
		case kEast: o = kWest; break;
		case kWest: o = kEast; break;
		case kNorthEast: o = kSouthWest; break;
		case kNorthWest: o = kSouthEast; break;
		case kSouthEast: o = kNorthWest; break;
		case kSouthWest: o = kNorthEast; break;
	}
}

bool Grid::Valid(const GridState &s)
{
	return (s.x >= 0 && s.x < width && s.y >= 0 && s.y < height && !Blocked(s));
}

bool Grid::Valid(const GridState &s, GridAction o)
{
	switch (o)
	{
		case kNorth:
			return Valid({s.x, s.y-1});
		case kSouth:
			return Valid({s.x, s.y+1});
		case kEast:
			return Valid({s.x+1, s.y});
		case kWest:
			return Valid({s.x-1, s.y});
		case kNorthEast:
			return Valid({s.x+1, s.y}) && Valid({s.x, s.y-1}) && Valid({s.x+1, s.y-1});
		case kNorthWest:
			return Valid({s.x-1, s.y}) && Valid({s.x, s.y-1}) && Valid({s.x-1, s.y-1});;
		case kSouthEast:
			return Valid({s.x+1, s.y}) && Valid({s.x, s.y+1}) && Valid({s.x+1, s.y+1});
		case kSouthWest:
			return Valid({s.x-1, s.y}) &&  Valid({s.x, s.y+1}) && Valid({s.x-1, s.y+1});
	}
}

bool Grid::Blocked(const GridState &s) const
{
	return grid[GetIndex(s)];
}

int Grid::GetIndex(const GridState &s) const
{
	return s.y*width+s.x;
}

float Grid::GetCost(GridAction o)
{
	switch (o)
	{
		case kNorth: return 1;
		case kSouth: return 1;
		case kEast: return 1;
		case kWest: return 1;
		case kNorthEast: return 1.4142135624;
		case kNorthWest: return 1.4142135624;
		case kSouthEast: return 1.4142135624;
		case kSouthWest: return 1.4142135624;
	}
}

float Grid::GetCost(const GridState &a, const GridState &b)
{
	if (a.x == b.x || a.y == b.y)
		return 1;
	return 1.4142135624;
}

