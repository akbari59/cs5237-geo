#ifndef POINTSETARRAYH
#define POINTSETARRAYH

#include "..\basics\pointSet.h"


class PointSetArray : public PointSet {

public:
	int getPoint (unsigned pIndex, LongInt& x1,LongInt& y1);
	int getPoint (unsigned pIndex, LongInt& x1,LongInt& y1, LongInt& weight, LongInt& z) const; // put the x,y values into x1,y1, and return 1 if the point pIndex exists
	int noPt();                                         // return the number of points
	void eraseAllPoints();                              // erase all points in this array
	int removePoint (unsigned pIndex); // remove the point with index PIndex from psa;
	void computeVoronoiVertex(int p1, int p2, int p3, LongInt& x, LongInt& y, LongInt& denominator) const;
};

#endif