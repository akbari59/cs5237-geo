#include "lmath.h"

int signDet(LongInt a, LongInt b, LongInt c,
			LongInt d, LongInt e, LongInt f,
			LongInt g, LongInt h, LongInt i){
				return (a*e*i+b*f*g+c*d*h-c*e*g-b*d*i-a*f*h).sign();
}


int signDet(LongInt x[3][3]){
	return signDet(x[0][0], x[0][1], x[0][2],
			x[1][0], x[1][1], x[1][2],
			x[2][0], x[2][1], x[2][2]);
}