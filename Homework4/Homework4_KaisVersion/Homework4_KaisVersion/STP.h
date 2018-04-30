#pragma once

#include <cstdio>
#include <vector>
#include <random>

const int kMaxWidth = 3;
const int kMaxHeight = 5;

enum STPSlideDir {
	kUp,
	kDown,
	kRight,
	kLeft,
	kNone
};

class STPState {
public:
	STPState();   // Init to goal state - default constructor will copy
	void Reset(); // Reset to goal state
	int tiles[kMaxWidth][kMaxHeight];
	int blankx, blanky;
	void operator=(const STPState &source);

};

std::ostream& operator<<(std::ostream& out, const STPState& s);
bool operator==(const STPState &s1, const STPState &s2);

class STP {
public:
	void GetSuccessors(STPState &s, std::vector<STPState> &states);
	void GetOperators(STPState &s, std::vector<STPSlideDir> &operators);
	void ApplyOperator(STPState &s, STPSlideDir o);
	void UndoOperator(STPState &s, STPSlideDir o);
	void InvertOperator(STPSlideDir &o);
};

void DoRandomWalkSuccessors(STP &puzzle, STPState &s, int length);
void DoRandomWalkOperators(STP &puzzle, STPState &s, int length);
