//
//  OctileDistance.cpp
//  HW #6
//

#include "OctileDistance.h"

float OctileDistance::h(const GridState &s, const GridState &g)
{
	int x = abs(s.x-g.x);
	int y = abs(s.y-g.y);
	float h = std::max(x, y)+std::min(x, y)*(0.4142135624);
	return h;
}
