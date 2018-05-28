//
//  Grid.h
//  HW6
//
//  Created by Nathan Sturtevant on 5/18/18.
//  Copyright © 2018 NS Software. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS

#ifndef Grid_h
#define Grid_h

#include <stdio.h>
#include <vector>
#include <iostream>

// Directions are relative to a grid with (0,0) in the upper left corner
// with increasing values down and to the right
enum GridAction {
	kNorth,
	kSouth,
	kEast,
	kWest,
	kNorthEast,
	kNorthWest,
	kSouthEast,
	kSouthWest
};

struct GridState {
	GridState(int x=0, int y=0) :x(x), y(y) {}
	int x, y;
};

class Grid {
public:
	Grid(const char *filename);
	void GetSuccessors(GridState &s, std::vector<GridState> &states);
	void GetOperators(GridState &s, std::vector<GridAction> &operators);
	void ApplyOperator(GridState &s, GridAction o);
	void UndoOperator(GridState &s, GridAction o);
	void InvertOperator(GridAction &o);
	bool Valid(const GridState &s, GridAction o);
	bool Valid(const GridState &s);
	bool Blocked(const GridState &s) const;
	float GetCost(GridAction o);
	float GetCost(const GridState &a, const GridState &b);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
private:
	int width, height;
	int GetIndex(const GridState &s) const;
	std::vector<bool> grid;
};

bool operator==(const GridState &a, const GridState &b);
std::ostream &operator<<(std::ostream &, const GridState &s);
std::ostream &operator<<(std::ostream &, const Grid &g);

namespace std {
	template <>
	struct hash<GridState>
	{
		std::size_t operator()(const GridState& s) const
		{
			return (s.x<<16)|(s.y);
		}
	};
}


#endif /* Grid_h */
