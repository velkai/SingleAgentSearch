//
//  PDB.h
//  HW4
//

#ifndef PDB_h
#define PDB_h

#include <stdio.h>
#include "heuristic.h"

class PDB : public Heuristic {
public:
	PDB(const std::vector<int> &tiles);
	int h(const STPState &s);
	void PrintDistribution();
private:
	struct BFSNode {
		STPState s;
		int depth;
	};

	void BuildPDB();
	uint64_t rank(const STPState &s);
	uint64_t factorial(int n);
	std::vector<uint8_t> pdb;
	std::vector<int> pattern;
	std::vector<int> dual;
	std::vector<int> patterndual;
};


#endif /* PDB_h */
