#ifndef DTRISTH
#define DTRISTH


#include "trist.h"

class DenaulayTri{
public:
	Trist trist;
	PointSetArray psa;
	
	
	DenaulayTri();
	int inTri(OrTri& tri, int p);
	OrTri findPoint(int pIndex, bool& boundary);
	void flipEdge(OrTri old_tri1,  OrTri& new_tri1, OrTri& new_tri2);//
	void insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3);//
	void insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3, OrTri& tri4);// 
	bool checkLegal(OrTri tri);
	void legalizeEdge(OrTri tri);
};


#endif