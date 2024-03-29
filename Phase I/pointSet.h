#ifndef POINTSETH
#define POINTSETH
#include <vector>
#include<array>
#include "li.h"

class PointSet {

public:
   std::vector<std::array<LongInt, 2>> set;
	static LongInt l0;
	int addPoint(LongInt x1,LongInt y1); 
	// add an ith(according to the adding sequence)  point (x1,y1), return i.

	int inTri(int p1Idx, int p2Idx, int p3Idx, int pIdx);
	// return 1 if the point p is inside the triangle p1p2p3, by reference of the indices, -1 if outside, 0 if degenerate

	int inCircle(int p1Idx, int p2Idx, int p3Idx, int pIdx);
	// return 1 if the point p is inside the circumcircle of p1p2p3
};

#endif