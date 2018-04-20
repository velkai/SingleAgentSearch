#pragma once

#include "STP.h"

struct Dual
{
	int *n;
	int base;

	void typeA()
	{
		n = new int[6];
		for (int i = 0; i < 6; ++i)
		{
			n[i] = i;
		}
		base = 6;
	};
	void typeB()
	{
		n = new int[7];
		n[0] = 0;
		for (int i = 9; i < 15; ++i)
		{
			n[i - 8] = i;
		}
		base = 7;
	};
};

class Ranking
{
public:

	Ranking() {};

	uint64_t GetRank(STPState &s);
	//STPState *Unrank(uint64_t rank);
	uint64_t *GetPDBRank(STPState &s);

private:

	uint64_t FACTORIAL(int n);
	int *COLLAPSE_STATE(STPState &s); // takes an STPState and returns its configuration as a linear array
	STPState *EXPAND_STATE(int *TILES); // does the opposite of above
	Dual &GetDualA(STPState &s);
	Dual &GetDualB(STPState &s);
};