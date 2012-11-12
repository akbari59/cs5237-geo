#include "pointSetArray.h"

int PointSetArray::getPoint (unsigned pIndex, LongInt& x1,LongInt& y1, LongInt& weight, LongInt& z) const{
	if(pIndex <= set.size()){
	 const std::array<LongInt, 4>& point=set[pIndex-1];
	 x1=point[0];
	 y1=point[1];
	 weight=point[2];
	 z=point[3];
	 return 1;
	}else{
	 return -1;
	}
}

int PointSetArray::getPoint (unsigned pIndex, LongInt& x1,LongInt& y1){
	if(pIndex <= set.size()){
	 std::array<LongInt, 4>& point=set[pIndex-1];
	 x1=point[0];
	 y1=point[1];
	 
	 return 1;
	}else{
	 return -1;
	}
}

int PointSetArray::noPt(){
	return set.size();
}

void PointSetArray::eraseAllPoints(){
	set.clear();
}

//dangerous routine
int PointSetArray::removePoint (unsigned pIndex)
{
	if(pIndex<=set.size()){
		set.erase(set.begin() + pIndex -1);
		return 1;
	}

	return -1;

}

void PointSetArray::computeVoronoiVertex(int p1Idx, int p2Idx, int p3Idx, LongInt& x, LongInt& y, LongInt& denominator) const{
	LongInt temp;
	LongInt x1, y1, w1;
	getPoint(p1Idx, x1, y1, w1, temp);
	LongInt x2, y2, w2;
	getPoint(p1Idx, x2, y2, w2, temp);
	LongInt x3, y3, w3;
	getPoint(p1Idx, x3, y3, w3, temp);
	denominator = x1*(y3-y2)+x2*(y1-y3)+x3*(y2-y1)*2;
	x = (y1*((x2*x2)-(x3*x3)+w3-w2))+(y2*((x3*x3)-(x1*x1)+w1-w3))+(y3*((x1*x1)-(x2*x2)+w2-w1))+(y1*y2*(y2-y1))+(y2*y3*(y3-y2))+(y1*y3*(y1-y3));
	y = (x1*(w2-w3))+(x2*(w3-w1))+(x3*(w1-w2))+((x1-x2)*((y3*y3)+(x1*x2)))+((x2-x3)*((y1*y1)+(x2*x3)))+((x3-x1)*((y2*y2)+(x1*x3)));
	if (denominator.sign()<0){
		denominator.negateSign();
		x.negateSign();
		y.negateSign();
	}

}