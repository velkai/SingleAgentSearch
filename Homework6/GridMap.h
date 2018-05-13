#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "STP.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

const int CardCost = 1;
const double DiagCost = sqrt(2);
 
enum GMMoveDir
{
	gUp,
	gDown,
	gRight,
	gLeft,
	gNone,
	gUpRight,
	gUpLeft,
	gDownRight,
	gDownLeft
};

class GMState
{
public:
	GMState();   // Init to undefined state (-1, -1)
	GMState(int x, int y);
	int x, y;
	void operator=(const GMState &source);
};

std::ostream& operator<<(std::ostream& out, const GMState& s);
bool operator==(const GMState &s1, const GMState &s2);

namespace std
{
	template <>
	struct hash<GMState>
	{
		std::size_t operator()(const GMState& s) const
		{
			return std::hash<int>()(s.x) ^ std::hash<int>()(s.y);
		}
	};
}

class GridMap
{
public:
	void Import(const char *filename);
	void GetSuccessors(GMState &s, std::vector<GMState> &states);
	void GetOperators(GMState &s, std::vector<GMMoveDir> &operators);
	void ApplyOperator(GMState &s, GMMoveDir o);
	void UndoOperator(GMState &s, GMMoveDir o);
	void InvertOperator(GMMoveDir &o);

private:
	std::vector<std::vector<bool>> grid;
};