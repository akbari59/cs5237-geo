#ifndef POINTSETH
#define POINTSETH
#include <vector>
#include<array>
#include "li.h"
#include "lmath.h"

class PointSet {

public:
   std::vector<std::array<LongInt, 3>> set;
	static LongInt l0;
	int addPoint(LongInt x1,LongInt y1, LongInt weight=0); 
	// add an ith(according to the adding sequence)  point (x1,y1), return i.

	int inTri(int p1Idx, int p2Idx, int p3Idx, int pIdx);
	// return 1 if the point p is inside the triangle p1p2p3, by reference of the indices, -1 if outside, 0 if degenerate
	int inTri(int p1, int p2, int p3, int p, int& edge);// if p is on the edge, edge indicates which edge it lies on. 0 for p1p2, 1 for p2p3, 2 for p3p1. 
	int p0InTri( int p2, int p3, int p, int& edge);//helper function for inTri, when the symblic vertex is p0, p2 & p3 are not symbolic
	int pNInTri(int sym, int p2, int p3, int p);//helper function for inTri, when the symblic vertex is p-1|p-2, p2 & p3 are not symbolic. If the point is on the boundary, it can only be on the edge p2p3.
	int pN2pN1InTri(int p3, int p);//one edge is the imaginery horizontal line, the point cannot lie on the edge. When it is called, p3 should be the lowest line so far.
	int pNp0InTri(int pN, int p3, int p); //If point p is on hte boundary, it must lie on the edge p0p3.
	int inCircle(int p1Idx, int p2Idx, int p3Idx, int pIdx);// return 1 if the point p is inside the circumcircle of p1p2p3
	int symInCircle(int p1Idx, int p2Idx, int p3Idx, int sym);// 
	
};

#endif