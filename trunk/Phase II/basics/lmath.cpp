#include "lmath.h"
LongInt one(1);
int signDet(LongInt& a, LongInt& b, LongInt& c,
			LongInt& d, LongInt& e, LongInt& f,
			LongInt& g, LongInt& h, LongInt& i){
				return (a*(e*i-f*h)+b*(f*g-d*i)+c*(d*h-e*g)).sign();
				
}


int signDet(LongInt x[3][3]){
	return signDet(x[0][0], x[0][1], x[0][2],
			x[1][0], x[1][1], x[1][2],
			x[2][0], x[2][1], x[2][2]);
}

int getside( array<LongInt, 2>& p2, array<LongInt, 2>& p3, array<LongInt, 2>& p){
	return signDet(one, p2[0], p2[1],
		           one, p3[0], p3[1],
				   one, p[0], p[1]);
}

bool checkEdge(const LongInt& x1, const LongInt& y1, const LongInt& w1, const LongInt& x2, const LongInt& y2, const LongInt& w2, const LongInt& alpha){
  //do sth
	return false;
}
bool checkTri(const LongInt& x1, const LongInt& y1, const LongInt& w1, const LongInt& x2, const LongInt& y2, const LongInt& w2, const LongInt& x3, const LongInt& y3, const LongInt& w3, const LongInt& alpha){
	//do sth
	return false;
}
