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
	void flipEdge(OrTri old_tri1,  OrTri& new_tri1, OrTri& new_tri2);
	int checkBelowPlane(int pIndex, OrTri tri, bool inTri=false) const; //1 below, 0 on the plane, -1 above
	int checkSymBelowPlane(int pIndex, int p1, int p2, int p3) const;
	void setNorm(OrTri tri);
	bool insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3);//
	bool insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3, OrTri& tri4);// 
	bool checkLegal(OrTri tri) const;
	void addChild(OrTri parent, OrTri child);
	int isObtuseFlip(OrTri& tri) const; //-1 not, 0 point on edge, 1 yes
	//If it is not a Obtuse flip tri will not changed, else it will be rotate to so that dest(tri) is the obtuse vertex.
	void removePoint(int p1, OrTri removeTri, OrTri coverTri);
	void legalizeEdge(OrTri tri);
	void init();
};


#endif