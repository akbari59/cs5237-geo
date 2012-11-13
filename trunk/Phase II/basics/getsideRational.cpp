#include "lmath.h"
int getsideRational(const array<LongInt, 4>& p1, const array<LongInt, 4>& p2, const LongInt& x, const LongInt& y, const LongInt& denominator){
	LongInt p1p2[2]={p2[0]-p1[0], p2[1]-p1[1]};
	LongInt p1p[2]={x-denominator*p1[0], y-denominator*p1[1]};
	return (p1p2[0]*p1p[1]-p1p2[1]*p1p[0]).sign();
}