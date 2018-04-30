#include "Ranking.h"
#include <iostream>

Ranking::Ranking()
{
	factorial = new uint64_t[15];
	for (int i = 0; i < 15; ++i)
	{
		factorial[i] = FACTORIAL(i);
	}
}

uint64_t Ranking::GetRank(STPState &s)
{
	uint64_t rank = 0, NUM_GREATER;
	int *n = COLLAPSE_STATE(s); // linear representation of STPState *s
	for (int i = 0; i < 15; ++i)
	{
		NUM_GREATER = 0;
		for (int j = i + 1; j < 15; ++j)
		{
			if (n[i] > n[j]) ++NUM_GREATER;
		}
		std::cout << NUM_GREATER << " " << factorial[14 - i] << "\n";
		rank += NUM_GREATER*factorial[14-i];
	}

	return rank;
}

STPState *Ranking::Unrank(uint64_t rank)
{
	int *n = new int[15], *TILES = new int[15];
	std::unordered_map<int, int> *VALUE_BANK = new std::unordered_map<int, int>();
	for (int i = 14; i >= 0; --i)
	{
		uint64_t fact = FACTORIAL(i);
		std::cout << rank << " " << fact << "\n";
		n[14-i] = rank / fact;
		rank = rank % fact;
		VALUE_BANK->insert({14-i, 14-i});
	}

	for (int i = 0; i < 15; ++i) // FIX: Need to 'remove' values from VALUE_BANK array
	{
		int j = n[i];
		TILES[i] = VALUE_BANK->at(j);
		VALUE_BANK->erase(j);
	}

	return EXPAND_STATE(TILES);
}

/*
	For PDB A: /9!
	For PDB B: /8!

	---------------------------------------------------
	ASK ABOUT THE BELOW FUNCTION - Done
	---------------------------------------------------

	PDB: (1, 3, 4)
	Dual: (2, 5, 3)
	Radix: (6, 5, 4)

	Dual: (2, 4, 3)
	Radix: (6, 5, 4)

	Dual: (2, 4, 2)
	Radix: (6, 5, 4)

	Rank = (2*5! + 4*4! + 2*3!) / (# unconsidered, for this example, 3!)
*/
uint64_t *Ranking::GetPDBRank(STPState &s)
{
	int *n = COLLAPSE_STATE(s);
	uint64_t *ret = new uint64_t[2];

	int *PDBA = new int[6], *DUALA = new int[6];
	PDBA[0] = 0;
	PDBA[1] = 1;
	PDBA[2] = 2;
	PDBA[3] = 3;
	PDBA[4] = 4;
	PDBA[5] = 5;
	

	int *PDBB = new int[7], *DUALB = new int[7];
	PDBB[0] = 0;
	PDBB[1] = 9;
	PDBB[2] = 10;
	PDBB[3] = 11;
	PDBB[4] = 12;
	PDBB[5] = 13;
	PDBB[6] = 14;

	// build duals
	for (int i = 0; i < 15; ++i)
	{
		if (n[i] < 6)
		{
			DUALA[n[i]] = i;
		}
		if (n[i] == 0)
		{
			DUALB[0] = i;
		}
		else if (n[i] >= 9 && n[i] < 15)
		{
			DUALB[n[i]-8] = i;
		}
	}

	// refine DUALA
	for (int i = 0; i < 6; ++i)
	{
		for (int j = i; j < 6; ++j)
		{
			if (DUALA[i] < DUALA[j])
			{
				--DUALA[j];
			}
		}
	}

	uint64_t rank = DUALA[0];
	for (int i = 1; i < 6; ++i)
	{
		rank *= 15 - i;
		rank += DUALA[i];
	}
	ret[0] = rank;

	// get rank for PDB A
	/*uint64_t rank = 0;
	for (int i = 0; i < 6; ++i)
	{
		rank += DUALA[i] * factorial[14-i];
	}
	rank /= factorial[9];
	ret[0] = rank;*/

	// refine DUALB
	for (int i = 0; i < 7; ++i)
	{
		for (int j = i; j < 7; ++j)
		{
			if (DUALB[i] < DUALB[j])
			{
				--DUALB[j];
			}
		}
	}

	rank = DUALB[0];
	for (int i = 1; i < 7; ++i)
	{
		rank *= 15 - i;
		rank += DUALB[i];
	}
	ret[1] = rank;

	// get rank for PDB B
	/*rank = 0;
	for (int i = 0; i < 7; ++i)
	{
		rank += DUALB[i] * factorial[14 - i];
	}
	rank /= factorial[8];
	ret[1] = rank;*/

	delete[] DUALA, DUALB, PDBA, PDBB;

	return ret;
}


uint64_t Ranking::FACTORIAL(int n)
{
	uint64_t fact = 1;
	for (int i = n; i > 0; --i)
	{
		fact *= i;
	}
	return fact;
}

int *Ranking::COLLAPSE_STATE(STPState &s)
{
	int *n = new int[15];
	for (int h = 0; h < 5; ++h)
	{
		for (int w = 0; w < 3; ++w)
		{
			n[h * 3 + w] = s.tiles[w][h];
		}
	}

	return n;
}

STPState *Ranking::EXPAND_STATE(int *TILES)
{
	STPState *s = new STPState();
	for (int h = 0; h < 5; ++h)
	{
		for (int w = 0; w < 3; ++w)
		{
			s->tiles[w][h] = TILES[h * 3 + w];
		}
	}

	return s;
}
