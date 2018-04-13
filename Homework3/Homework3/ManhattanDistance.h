//
// Created by Jimmy Holmes on 4/12/2018.
//

#ifndef SAS_MANHATTANDISTANCE_H
#define SAS_MANHATTANDISTANCE_H

#include "heuristic.hpp"
#include "STP.h"

class ManhattanDistance : public Heuristic
{
public:
    int getFcost(STPState &s, std::deque<STPState> &path);
    int getGcost(std::deque<STPState> &path);
    int getHcost(STPState &s);

private:
    void UPDATE_FCOST(STPState &s);
    void UPDATE_GCOST(std::deque<STPState> &path);
    void UPDATE_HCOST(STPState &s);
    int DISTANCE_FROM_GOAL(int x, int y, int value);
};

#endif //SAS_MANHATTANDISTANCE_H
