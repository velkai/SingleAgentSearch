//
// Created by Jimmy Holmes on 4/12/2018.
//

#include "ManhattanDistance.h"
#include "cmath"

int ManhattanDistance::getFcost(STPState &s, std::deque<STPState> &path)
{
    UPDATE_FCOST(s);
    UPDATE_GCOST(path);
    return gcost + hcost;
}

int ManhattanDistance::getGcost(std::deque<STPState> &path)
{
    UPDATE_GCOST(path);
    return gcost;
}

int ManhattanDistance::getHcost(STPState &s)
{
    UPDATE_HCOST(s);
    return hcost;
}

void ManhattanDistance::UPDATE_FCOST(STPState &s)
{
    fcost = gcost + getHcost(s);
}

void ManhattanDistance::UPDATE_GCOST(std::deque<STPState> &path)
{
    gcost = path.size();
}

void ManhattanDistance::UPDATE_HCOST(STPState &s)
{
    hcost = 0; // reset hcost back to 0
    for(int w = 0; w < 3; ++w)
    {
        for(int h = 0; h < 5; ++h)
        {
            hcost += DISTANCE_FROM_GOAL(w, h, s.tiles[w][h]);
        }
    }
}

int ManhattanDistance::DISTANCE_FROM_GOAL(int x, int y, int value)
{
    int goal_x, goal_y;
    goal_x = value % 3;
    goal_y = value / 3;

    return abs(goal_x-x) + abs(goal_y-y);
}