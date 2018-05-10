#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "STP.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

// homework 5 will use STPSlideDir 
/*enum STPSlideDir
{
	kUp,
	kDown,
	kRight,
	kLeft,
	kUpRight,
	kUpLeft,
	kDownRight,
	kDownLeft,
	kNone
};*/

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
	void GetOperators(GMState &s, std::vector<STPSlideDir> &operators);
	void ApplyOperator(GMState &s, STPSlideDir o);
	void UndoOperator(GMState &s, STPSlideDir o);
	void InvertOperator(STPSlideDir &o);

private:
	std::vector<std::vector<bool>> grid;
};