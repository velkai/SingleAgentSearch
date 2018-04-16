#pragma once

#include <deque>
#include "STP.h"
#include "heuristic.h"

class IDA 
{

public:

	IDA();
	std::deque<STPState> GetPath(STP &s, STPState &start, STPState &goal, heuristic &h);

private:

	int IDASearch(STP &s, std::deque<STPState> &path, int g, int t, heuristic &h); // takes the path, g-value, and threshold as parameters
};