#ifndef TBIRTHTIME
#define TBIRTHTIME
#include "..\basics\li.h"
class TriangleBirthTime{
public:
	LongInt birthP, p2;
	
	void setBirthParameter(const LongInt& x0, const LongInt& y0, const LongInt& p, const LongInt& x1, const LongInt& y1, const LongInt& w1);
	bool compareBirthTime(const LongInt& alphaSquare) const{
		return alphaSquare*p2<birthP;
	};

};
#endif