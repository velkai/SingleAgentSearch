#include "Ranking.h"
#include <iostream>

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
		std::cout << NUM_GREATER << " " << FACTORIAL(14 - i) << "\n";
		rank += NUM_GREATER*FACTORIAL(14-i);
	}

	return rank;
}

/*STPState *Ranking::Unrank(uint64_t rank)
{
	int *n = new int[15], *VALUE_BANK = new int[15], *TILES = new int[15];

	for (int i = 14; i >= 0; --i)
	{
		uint64_t fact = FACTORIAL(i);
		std::cout << rank << " " << fact << "\n";
		n[14-i] = rank / fact;
		rank = rank % fact;
		VALUE_BANK[14-i] = 14 - i;
	}

	for (int i = 0; i < 15; ++i) // FIX: Need to 'remove' values from VALUE_BANK array
	{
		std::cout << n[i] << " ";
		int j = n[i];
		while (VALUE_BANK[j] == -1)
		{
			++j;
		}
		for (int k = 0; k < 15; ++k)
		{
			std::cout << VALUE_BANK[k] << ",";
		}
		std::cout << std::endl;

		TILES[i] = VALUE_BANK[j];
		VALUE_BANK[j] = -1;
	}
	std::cout << "\n";

	return EXPAND_STATE(TILES);
}*/

/*
	---------------------------------------------------
	ASK ABOUT THE BELOW FUNCTION
	---------------------------------------------------
*/
uint64_t *Ranking::GetPDBRank(STPState &s) // returns a two-element uint64_t array, with index 0 being the rank for pattern A, and 1 being B's rank
{
	Dual a = GetDualA(s), b = GetDualB(s);

	int *aTemp = new int[6], *bTemp = new int[7];

	uint64_t *ret = new uint64_t[2];
	uint64_t temp = a.n[0];

	for (int i = 0; i < 6; ++i)
	{
		if (a.n[i] < temp)
		{
			--a.base;
		}
		aTemp[i] = a.n[i] * FACTORIAL(a.base);
	}
	temp = 0;
	for (int i = 0; i < 6; ++i)
	{
		aTemp[i] /= FACTORIAL(a.base);
		temp += aTemp[i];
	}
	ret[0] = temp;

	temp = b.n[0];
	for (int i = 0; i < 7; ++i)
	{
		if (b.n[i] < temp)
		{
			--b.base;
		}
		bTemp[i] = b.n[i] * FACTORIAL(b.base);
	}
	temp = 0;
	for (int i = 0; i < 7; ++i)
	{
		bTemp[i] /= FACTORIAL(b.base);
		temp += bTemp[i];
	}
	ret[1] = temp;

	return ret;
}

Dual &Ranking::GetDualA(STPState &s)
{
	Dual d;
	d.typeA();
	for (int i = 0; i < 15; ++i)
	{
		if (*s.tiles[i] < 6)
		{
			d.n[*s.tiles[i]] = i;
		}
	}
	return d;
}

Dual &Ranking::GetDualB(STPState &s)
{
	Dual d;
	d.typeB();
	for (int i = 0; i < 15; ++i)
	{
		if (*s.tiles[i] == 0)
		{
			d.n[0] = i;
		}
		else if (*s.tiles[i] >= 9 && *s.tiles[i] <= 14)
		{
			d.n[*s.tiles[i]-8] = i;
		}
	}
	return d;
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
