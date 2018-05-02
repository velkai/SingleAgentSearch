#include <deque>
#include "BFS.h"

// start is passed by value so we don't modify the state in the calling function
// modified to return the depth of the path
uint8_t BFS::GetPath(STP &stp, STPState start, STPState &goal)
{
	if (start == goal) return 0;

	expansions = 0;
	std::deque<BFSNode> q;
	std::vector<STPSlideDir> acts;
	q.push_back({ start, kNone, 0 });

	int currDepth = 0;
	uint64_t previousExpansions = 0;
	while (q.size() > 0)
	{
		BFSNode n = q.front();
		q.pop_front();

		if (n.depth != currDepth)
		{
			//printf("Depth %d complete; %llu total expansions (%llu new)\n", currDepth, expansions, expansions - previousExpansions);
			currDepth = n.depth;
			previousExpansions = expansions;
		}

		stp.GetOperators(n.s, acts);
		expansions++;
		for (auto act : acts)
		{
			if (act == n.forbidden)
				continue;

			stp.ApplyOperator(n.s, act);
			if (n.s == goal)
			{
				//printf("Goal found at depth %d; %llu nodes expanded\n", n.depth + 1, expansions);
				return n.depth+1;
			}
			stp.InvertOperator(act);
			q.push_back({ n.s, act, n.depth + 1 });
			stp.ApplyOperator(n.s, act);
		}
	}
	return 255;
}

uint64_t BFS::GetNodesExpanded()
{
	return expansions;
}
//struct BFSNode {
//	STPState s;
//	STPSlideDir forbidden;
//};

