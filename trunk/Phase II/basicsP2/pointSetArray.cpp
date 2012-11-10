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