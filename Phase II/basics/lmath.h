#ifndef LMATHH
#define LMATHH

#include "li.h"
#include <array>


// return 1 as positive, -1 as negative, 0 as zero of the determinant

int signDet(const LongInt& x1, const LongInt& y1, const LongInt& w1,
			const LongInt& x2, const LongInt& y2, const LongInt& w2,
			const LongInt& x3, const LongInt& y3, const LongInt& w3);
LongInt Det( LongInt const& a1,  LongInt const& a2,
			 LongInt const& b1,  LongInt const& b2 );

int signDet(LongInt x[3][3]) ;

int getside(const array<LongInt, 4>& p2, const array<LongInt, 4>& p3, const array<LongInt, 4>& p);
int getsideRational(const array<LongInt, 4>& p2, const array<LongInt, 4>& p3, const LongInt& x, const LongInt& y, const LongInt& denominator);


void getPlaneNorm(const array<LongInt, 4>& p1, const array<LongInt, 4>& p2, const array<LongInt, 4>& p3, array<LongInt, 3>& norm);

bool checkEdge(const LongInt& x1, const LongInt& y1, const LongInt& w1, const LongInt& x2, const LongInt& y2, const LongInt& w2, const LongInt& alphaSquare);
bool checkTri(const LongInt& x1, const LongInt& y1, const LongInt& w1, const LongInt& x2, const LongInt& y2, const LongInt& w2, const LongInt& x3, const LongInt& y3, const LongInt& w3, const LongInt& alpha);

LongInt projectZ(const LongInt& x, const LongInt& y, const LongInt& w);
#endif