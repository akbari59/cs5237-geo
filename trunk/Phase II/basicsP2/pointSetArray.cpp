#include "pointSetArray.h"

int PointSetArray::getPoint (int pIndex, LongInt& x1,LongInt& y1){
	if(pIndex<=set.size()){
	 std::array<LongInt, 2> point=set[pIndex-1];
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