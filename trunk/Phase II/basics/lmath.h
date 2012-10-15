#ifndef LMATHH
#define LMATHH

#include "li.h"
#include <array>


// return 1 as positive, -1 as negative, 0 as zero of the determinant

int signDet(LongInt& x1, LongInt& y1, LongInt& w1,
			LongInt& x2, LongInt& y2, LongInt& w2,
			LongInt& x3, LongInt& y3, LongInt& w3);


int signDet(LongInt x[3][3]) ;

int getside( array<LongInt, 2>& p2, array<LongInt, 2>& p3, array<LongInt, 2>& p);

#endif