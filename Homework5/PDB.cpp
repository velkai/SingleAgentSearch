//
//  PDB.cpp
//  HW4
//

#include "PDB.h"
#include <deque>
#include "Timer.h"

std::vector<uint8_t> pdb;

PDB::PDB(const std::vector<int> &tiles)
:pattern(tiles)
{
	BuildPDB();
}

int PDB::h(const STPState &s)
{
	return pdb[rank(s)];
}


uint64_t PDB::rank(const STPState &s)
{
	// 1. get dual (of all pieces)
	dual.resize(kMaxWidth*kMaxHeight);
	int loc = 0;
	for (int x = 0; x < kMaxWidth; x++)
	{
		for (int y = 0; y < kMaxHeight; y++)
		{
			dual[s.tiles[x][y]] = loc;
			loc++;
		}
	}

	// 1b. get dual (of pattern)
	patterndual.resize(0);
	for (int z = 0; z < pattern.size(); z++)
	{
		patterndual.push_back(dual[pattern[z]]);
	}

	// 2. convert to mixed radix
	for (int x = 0; x < patterndual.size(); x++)
	{
		for (int y = x+1; y < patterndual.size(); y++)
		{
			if (patterndual[y] > patterndual[x])
				patterndual[y]--;
		}
	}

	// 3. compute rank
	uint64_t rank = 0;
	for (int x = 0; x < patterndual.size(); x++)
	{
		rank *= kMaxHeight*kMaxWidth-x;
		rank += patterndual[x];
	}
	return rank;
}

uint64_t PDB::factorial(int n)
{
	static uint64_t table[21] =
	{ 1ll, 1ll, 2ll, 6ll, 24ll, 120ll, 720ll, 5040ll, 40320ll, 362880ll, 3628800ll, 39916800ll, 479001600ll,
		6227020800ll, 87178291200ll, 1307674368000ll, 20922789888000ll, 355687428096000ll,
		6402373705728000ll, 121645100408832000ll, 2432902008176640000ll };
	if (n > 20)
		return (uint64_t)-1;
	return table[n];

}

void PDB::BuildPDB()
{
	Timer t;
	STP stp;
	STPState goal;
	uint64_t written = 1;
	std::deque<BFSNode> q;
	std::vector<STPSlideDir> acts;

	t.StartTimer();
	q.push_back({goal, 0});
	pdb.resize(factorial(kMaxHeight*kMaxWidth)/factorial(kMaxHeight*kMaxWidth-pattern.size()), 255);
	pdb[rank(goal)] = 0;
	while (q.size() > 0)
	{
		// n already written into PDB
		BFSNode n = q.front();
		q.pop_front();

		stp.GetOperators(n.s, acts);
		for (auto act : acts)
		{
			stp.ApplyOperator(n.s, act);
			uint64_t r = rank(n.s);
			if (pdb[r] == 255)
			{
				written++;
				pdb[r] = n.depth+1;
				q.push_back({n.s, n.depth+1});
			}
			stp.UndoOperator(n.s, act);
		}
	}
	t.EndTimer();
	printf("PDB complete in %1.2fs; %llu of %lu entries written\n", t.GetElapsedTime(), written, pdb.size());
}

void PDB::PrintDistribution()
{
	std::vector<int> dist;
	for (uint8_t item : pdb)
	{
		if (item >= dist.size())
			dist.resize(item+1);
		dist[item]++;
	}
	printf("PDB Distribution\n");
	for (int x = 0; x < dist.size(); x++)
	{
		printf("%d : %d\n", x, dist[x]);
	}
}
