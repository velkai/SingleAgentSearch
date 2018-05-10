#pragma once

#include "STP.h"
#include "AStar.h"
#include <vector>
#include <iostream>

class NodePriorityHeap
{
public:

	void insert(NODE &s);
	NODE popBest();
	bool empty();

private:

	std::vector<NODE> QUEUE;

	void HEAPIFY(size_t i); // organizes QUEUE so that the last value has the highest priority
};