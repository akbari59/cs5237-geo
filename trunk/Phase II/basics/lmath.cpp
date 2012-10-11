#include "lmath.h"

int signDet(LongInt a, LongInt b, LongInt c,
			LongInt d, LongInt e, LongInt f,
			LongInt g, LongInt h, LongInt i){
				return (a*(e*i-f*h)+b*(f*g-d*i)+c*(d*h-e*g)).sign();
				
}


int signDet(LongInt x[3][3]){
	return signDet(x[0][0], x[0][1], x[0][2],
			x[1][0], x[1][1], x[1][2],
			x[2][0], x[2][1], x[2][2]);
}

int getside( array<LongInt, 2>& p2, array<LongInt, 2>& p3, array<LongInt, 2>& p){
	return signDet(1, p2[0], p2[1],
		           1, p3[0], p3[1],
				   1, p[0], p[1]);
}