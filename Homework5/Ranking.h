#pragma once

#include "STP.h"
#include <unordered_map>

class Ranking
{
public:

	Ranking();

	uint64_t GetRank(STPState &s);
	STPState *Unrank(uint64_t rank); // untested
	uint64_t *GetPDBRank(STPState &s);

private:

	uint64_t FACTORIAL(int n);
	int *COLLAPSE_STATE(STPState &s); // takes an STPState and returns its configuration as a linear array
	STPState *EXPAND_STATE(int *TILES); // does the opposite of above
	uint64_t *factorial;
};