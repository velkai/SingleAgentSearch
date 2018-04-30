#pragma once

#include <stdio.h>
#include "STP.h"

class DFID {
public:
	uint8_t GetPath(STP &stp, STPState start, STPState &goal);
	uint64_t GetNodesExpanded();
private:
	bool BoundedSearch(STP &stp, STPState &start, STPState &goal, int limit, STPSlideDir forbidden);
	uint64_t expansions;
};