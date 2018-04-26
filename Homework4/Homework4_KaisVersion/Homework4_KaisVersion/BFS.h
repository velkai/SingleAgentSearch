#pragma once

#ifndef BFS_hpp
#define BFS_hpp

#include <stdio.h>
#include "STP.h"

class BFS {
public:
	uint8_t GetPath(STP &stp, STPState start, STPState &goal);
	uint64_t GetNodesExpanded();
private:
	struct BFSNode {
		STPState s;
		STPSlideDir forbidden;
		int depth;
	};
	uint64_t expansions;
};

#endif /* BFS_h */
