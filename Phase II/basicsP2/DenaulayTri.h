#ifndef DTRISTH
#define DTRISTH


#include "trist.h"

class DenaulayTri{
public:
	Trist trist;
	PointSetArray psa;
public:
	int inTri(OrTri& tri, int p);
	OrTri findPoint(int pIndex, bool& boundary);
	bool checkLegal(OrTri tri);
}


#endif