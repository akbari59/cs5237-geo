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

bool checkEdge( LongInt const& x1, LongInt const& y1, LongInt const& w1, LongInt const& x2, LongInt const& y2, LongInt const& w2, LongInt const& alphaSquare){
	
	// distance between the two weighted points
	LongInt distance = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2); //d^2
	LongInt FourDistance=distance*4;  //4d^2
	LongInt p_numerator=w1-w2+distance; //e1-e2+d^2
	LongInt p_numerator_square=p_numerator*p_numerator;
	LongInt LHS=p_numerator_square-FourDistance*w1;
	if(LHS.sign()<1)
		return true;
	else
	    return LHS<(alphaSquare*FourDistance);

	/*LongInt w = w1 + w2;
	LongInt alphaNew = alpha*alpha*4;
	LongInt D = distance-w1-w2;

	if((D*D - w1*w2*4)*(w*2 - distance) < 0){
		return true;
	}
	else{
		return !((alphaNew*(w*2 - distance)) < (D*D - w1*w2*4));
	}
	// Condition when the balls just touch each other, also just touch voronoi edge
	// LongInt birth = (d-w1-w2);
	//return !(alpha*alpha * 2 < birth);
	*/
}

bool checkTri( LongInt const& x1, LongInt const& y1, LongInt const& w1, LongInt const& x2, LongInt const& y2, LongInt const& w2, LongInt const& x3, LongInt const& y3, LongInt const& w3, LongInt const& alpha){
	LongInt p = (x1*(y3-y2)+x2*(y1-y3)+x3*(y2-y1))*2;
	LongInt p2 = p*p;
	
	LongInt x12 = x1*x1;
	LongInt y12 = y1*y1;
	LongInt x22 = x2*x2;
	LongInt y22 = y2*y2;
	LongInt x32 = x3*x3;
	LongInt y32 = y3*y3;
	
	LongInt x0 = (y1*(x22-x32+w3-w2))+(y2*(x32-x12+w1-w3))+(y3*(x12-x22+w2-w1))+(y1*y2*(y2-y1))+(y2*y3*(y3-y2))+(y1*y3*(y1-y3));
	LongInt y0 = (x1*(y32-y22+w2-w3))+(x2*(y12-y32+w3-w1))+(x3*(y22-y12+w1-w2))+(x1*x2*(x1-x2))+(x2*x3*(x2-x3))+(x1*x3*(x3-x1));
	
	LongInt birth1 = (x0-(p*x1));
	birth1 = birth1*birth1;
	LongInt birth2 = (y0-(p*y1));
	birth2 = birth2*birth2;
	
	LongInt birthP = birth1+birth2-(w1*p2);
	LongInt modifiedAlpha = alpha*alpha*p2;
	return !(modifiedAlpha<birthP);
}

void getPlaneNorm(const array<LongInt, 4>& p1, const array<LongInt, 4>& p2, const array<LongInt, 4>& p3, array<LongInt, 3>& norm){
	array<LongInt, 3> p1p2={p2[0]-p1[0], p2[1]-p1[1], p2[3]-p1[3]};
	array<LongInt, 3> p1p3={p3[0]-p1[0], p3[1]-p1[1], p3[3]-p1[3]};
	norm[0]=Det(p1p2[1],p1p2[2],p1p3[1],p1p3[2]); 
	norm[1]=-Det(p1p2[0],p1p2[2],p1p3[0],p1p3[2]);
	norm[2]=Det(p1p2[0],p1p2[1],p1p3[0],p1p3[1]);
	if(norm[2].sign()==1){
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
