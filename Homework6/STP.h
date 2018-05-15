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

namespace std
{
	template <>
	struct hash<STPState>
	{
		std::size_t operator()(const STPState& s) const
		{
			// goal state should hash to (0)1234567891011121314 - NOT POSSIBLE UNLESS I MANAGE TO FIND A WAY TO COMPRESS
			/*using std::size_t;
			using std::hash;

			size_t ret = 0;
			int p = 1;

			for (int w = 0; w < 3; ++w)
			{
				for (int h = 0; h < 5; ++h)
				{
					if (s.tiles[w][h] > 9) p *= 10;
					ret += p * s.tiles[w][h];
					p *= 10;
				}
			}

			return ret;*/

			uint64_t factorial[15];
			factorial[0] = 1;
			for (int i = 1; i < 15; ++i)
			{
				factorial[i] = factorial[i-1] * i;
			}

			uint64_t rank = 0, NUM_GREATER;
			int n[15];

			for (int w = 0; w < 3; ++w)
			{
				for (int h = 0; h < 5; ++h)
				{
					n[w * 5 + h] = s.tiles[w][h];
				}
			}

			/*for (int i = 0; i < 15; ++i)
			{
				NUM_GREATER = 0;
				for (int j = i + 1; j < 15; ++j)
				{
					if (n[i] > n[j]) ++NUM_GREATER;
				}
				rank += NUM_GREATER * factorial[14 - i];
			}*/

			for (int i = 0; i < 15; ++i)
			{
				for (int j = i + 1; j < 15; ++j)
				{
					if (n[i] < n[j]) --n[j];
				}
				rank += n[i] * factorial[14 - i];
			}

			return rank;
		}
	};
}

class STP {
public:
	void GetSuccessors(STPState &s, std::vector<STPState> &states);
	void GetOperators(STPState &s, std::vector<STPSlideDir> &operators);
	void ApplyOperator(STPState &s, STPSlideDir o);
	void UndoOperator(STPState &s, STPSlideDir o);
	void InvertOperator(STPSlideDir &o);
	double GetCost(STPSlideDir o) { return 1; }
	void PrintStates(std::vector<STPState> &s) {};
};

void DoRandomWalkSuccessors(STP &puzzle, STPState &s, int length);
void DoRandomWalkOperators(STP &puzzle, STPState &s, int length);
