#include "TriangleBirthTime.h"
void TriangleBirthTime::setBirthParameter(const LongInt& x0, const LongInt& y0, const LongInt& p, const LongInt& x1, const LongInt& y1, const LongInt& w1){
		p2=p*p;
		LongInt birth1 = (x0-(p*x1));
	    birth1 = birth1*birth1;
	    LongInt birth2 = (y0-(p*y1));
	    birth2 = birth2*birth2;	
	    LongInt birthP = birth1+birth2-(w1*p2);
	
};