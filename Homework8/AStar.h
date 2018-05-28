//
//  AStar.h
//  HW5
//
//  Created by Nathan Sturtevant on 5/11/18.
//  Copyright © 2018 NS Software. All rights reserved.
//

#ifndef AStar_h
#define AStar_h

#include <vector>
#include "AStarOpenList.h"

template <class environment, class state, class action>
class AStar {
public:
	void GetPath(environment *env, state start, state goal, Heuristic<state> *h, std::vector<state> &path);
	std::unordered_map<state, float> GetCosts(environment *env, state start, Heuristic<state> *h); // A* without a goal state; returns an hash table of state to g cost (float)
private:
	AStarOpenList<state> q;
	std::vector<action> acts;
};


template <class environment, class state, class action>
void AStar<environment, state, action>::GetPath(environment *env, state start, state goal,
												Heuristic<state> *h, std::vector<state> &path)
{
	int exp = 1;
	path.resize(0);
	q.Reset();
	q.Add(start, 0, h->h(start, goal));
	while (!q.Empty())
	{
		AStarData<state> next = q.GetNext();
		//std::cout << "Expanding " << next.state << "\n";
		if (next.state == goal)
		{
			q.GetPath(next.state, path);
			std::cout << exp << " nodes expanded\n";
			return;
		}
		env->GetOperators(next.state, acts);
		
		for (auto op : acts)
		{
			state tmp = next.state;
			env->ApplyOperator(tmp, op);
			//std::cout << "**Sucessor " << tmp << "\n";
			int size_i = q.Size();
			q.Add(tmp, next.g+env->GetCost(op), h->h(tmp, goal), next.state);
			int size_f = q.Size();
			if (size_i < size_f) ++exp;
		}
	}
	std::cout << exp << " nodes expanded\n";
}

template <class environment, class state, class action>
std::unordered_map<state, float> AStar<environment, state, action>::GetCosts(environment *env, state start,
	Heuristic<state> *h)
{
	state goal;

	q.Reset();
	q.Add(start, 0, h->h(start, goal));

	std::unordered_map<state, float> ret;
	ret.insert(std::pair<state, float>(start, 0));

	while (!q.Empty())
	{
		AStarData<state> next = q.GetNext();
		//std::cout << "Expanding " << next.state << "\n";
		env->GetOperators(next.state, acts);

		for (auto op : acts)
		{
			state tmp = next.state;
			env->ApplyOperator(tmp, op);
			//std::cout << "**Sucessor " << tmp << "\n";
			q.Add(tmp, next.g + env->GetCost(op), h->h(tmp, goal), next.state);

			if (ret.find(tmp) == ret.end())
			{
				ret.insert(std::pair<state, float>(tmp, next.g + env->GetCost(op)));
			}
			else
			{
				if (next.g + env->GetCost(op) < ret.at(tmp))
				{
					ret.at(tmp) = next.g + env->GetCost(op);
				}
			}
		}
	}

	return ret;
}


#endif /* AStar_h */
