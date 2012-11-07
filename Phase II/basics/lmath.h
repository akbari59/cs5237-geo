#ifndef LMATHH
#define LMATHH

#include "li.h"
#include <array>


// return 1 as positive, -1 as negative, 0 as zero of the determinant

int signDet(LongInt& x1, LongInt& y1, LongInt& w1,
			LongInt& x2, LongInt& y2, LongInt& w2,
			LongInt& x3, LongInt& y3, LongInt& w3);


int signDet(LongInt x[3][3]) ;

int getside( array<LongInt, 3>& p2, array<LongInt, 3>& p3, array<LongInt, 3>& p);
void getPlaneNorm( array<LongInt, 3>& p1, array<LongInt, 3>& p2, array<LongInt, 3>& p3, array<LongInt, 3>& norm);

bool checkEdge(const LongInt& x1, const LongInt& y1, const LongInt& w1, const LongInt& x2, const LongInt& y2, const LongInt& w2, const LongInt& alpha);
bool checkTri(const LongInt& x1, const LongInt& y1, const LongInt& w1, const LongInt& x2, const LongInt& y2, const LongInt& w2, const LongInt& x3, const LongInt& y3, const LongInt& w3, const LongInt& alpha);

#endif