#include "trist.h"


Trist::Trist()
{
	en_[0] = 1;
	en_[1] = 2;
	en_[2] = 0;
	en_[3] = 5;
	en_[4] = 3;
	en_[5] = 4;

	direction[0] = *new Direction(0,1);
	direction[1] = *new Direction(1,2);
	direction[2] = *new Direction(2,0);
	direction[3] = *new Direction(1,0);
	direction[4] = *new Direction(2,1);
	direction[5] = *new Direction(0,2);
}

int Trist::noTri(){
	return Trist::triangles.size();
}

int Trist::makeTri(int pIndex1,int pIndex2,int pIndex3,bool autoMerge = false){
	TriRecord *record = new TriRecord();
	(*record).vi_[0] = pIndex1;
	(*record).vi_[1] = pIndex2;
	(*record).vi_[2] = pIndex3;
	if(autoMerge){
	}
	triangles.push_back(record);
}

OrTri Trist::enext(OrTri ef){
	int version = ef && (0000111b);
	int index = ef >> 3;
	return (index<<3) | Trist::en_[version];
}

OrTri Trist::sym(OrTri ef){
	int version = ef && (0000111b);
	int index = ef >> 3;
	if(version<3){
		return (index<<3) | version+3;
	} else{
		return (index<<3) | version-3;
	}
}

void Trist::getVertexIdx(OrTri ef, int& pIdx1,int& pIdx2,int& pIdx3){
	int index = ef >> 3;
	TriRecord *record = Trist::triangles.at(index);
	pIdx1=(*record).vi_[1];
	pIdx2=(*record).vi_[2];
	pIdx3=(*record).vi_[3];
}

int Trist::org(OrTri ef){
	int version = ef && (0000111b);
	int index = ef >> 3;
	TriRecord *record = Trist::triangles.at(index);
	return (*record).vi_[direction[version].org];
}

int Trist::dest(OrTri ef){
	int version = ef && (0000111b);
	int index = ef >> 3;
	TriRecord *record = Trist::triangles.at(index);
	return (*record).vi_[direction[version].dest];
}


