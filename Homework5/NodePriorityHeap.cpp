#include "NodePriorityHeap.h"

void NodePriorityHeap::insert(NODE &n)
{
	for (std::vector<NODE>::iterator i = QUEUE.begin(); i != QUEUE.end(); ++i)
	{
		if (n.f > i->f)
		{
			QUEUE.insert(i, n);
			return;
		}
	}
	QUEUE.push_back(n);
}

NODE NodePriorityHeap::popBest()
{
	NODE ret = QUEUE.back();
	QUEUE.pop_back();
	return ret;
}

bool NodePriorityHeap::empty()
{
	return QUEUE.empty();
}