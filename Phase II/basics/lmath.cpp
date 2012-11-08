#include "lmath.h"
LongInt one(1);
int signDet(const LongInt& a, const LongInt& b, const LongInt& c,
			const LongInt& d, const LongInt& e, const LongInt& f,
			const LongInt& g, const LongInt& h, const LongInt& i){
				return (a*(e*i-f*h)+b*(f*g-d*i)+c*(d*h-e*g)).sign();
				
}


int signDet(LongInt x[3][3]){
	return signDet(x[0][0], x[0][1], x[0][2],
			x[1][0], x[1][1], x[1][2],
			x[2][0], x[2][1], x[2][2]);
}

int getside(const array<LongInt, 4>& p2, const array<LongInt, 4>& p3, const array<LongInt, 4>& p){
	return signDet(one, p2[0], p2[1],
		           one, p3[0], p3[1],
				   one, p[0], p[1]);
}

bool checkEdge( LongInt const& x1, LongInt const& y1, LongInt const& w1, LongInt const& x2, LongInt const& y2, LongInt const& w2, LongInt const& alpha){
  //do sth
	return false;
}
bool checkTri( LongInt const& x1, LongInt const& y1, LongInt const& w1, LongInt const& x2, LongInt const& y2, LongInt const& w2, LongInt const& x3, LongInt const& y3, LongInt const& w3, LongInt const& alpha){
	//do sth
	return false;
}

void getPlaneNorm(const array<LongInt, 4>& p1, const array<LongInt, 4>& p2, const array<LongInt, 4>& p3, array<LongInt, 3>& norm){
	array<LongInt, 3> p1p2={p2[0]-p1[0], p2[1]-p1[1], p2[3]-p1[3]};
	array<LongInt, 3> p1p3={p3[0]-p1[0], p3[1]-p1[1], p3[3]-p1[3]};
	norm[0]=Det(p1p2[1],p1p2[2],p1p3[1],p1p3[2]); 
	norm[1]=-Det(p1p2[0],p1p2[2],p1p3[0],p1p3[2]);
	norm[2]=Det(p1p2[0],p1p2[1],p1p3[0],p1p3[1]);
	if(norm[2].sign()==-1){
		norm[0].negateSign();
		norm[1].negateSign();
		norm[2].negateSign();
	}
}

LongInt projectZ(const LongInt& x, const LongInt& y, const LongInt& w){
	return x*x+y*y-w;
}


LongInt Det( LongInt const&  a1,  LongInt const&  a2,
			 LongInt const&  b1,  LongInt const&  b2 ){
				return a1*b2-a2*b1;
}
