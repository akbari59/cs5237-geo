#include "trist.h"


Trist::Trist()
{
	en_[0] = 1;
	en_[1] = 2;
	en_[2] = 0;
	en_[3] = 5;
	en_[4] = 3;
	en_[5] = 4;

	v_[0] = 12;
	v_[1] = 120;
	v_[2] = 201;
	v_[3] = 102;
	v_[4] = 210;
	v_[5] = 21;
}

int Trist::noTri(){
	return Trist::triangles.size();
}

int Trist::makeTri(int pIndex1,int pIndex2,int pIndex3,bool autoMerge){
	TriRecord record;
	record.vi_[0] = pIndex1;
	record.vi_[1] = pIndex2;
	record.vi_[2] = pIndex3;
	if(autoMerge){
	}
	int index = triangles.size();
	triangles.push_back(record);
	return index;
}

void Trist::delTri(OrTri ef){
	int index = ef >> 3;
	triangles.erase(triangles.begin()+index);
	//triangles.at(index).isEmpty = true;
}

void Trist::delAllTri()
{
	triangles.clear();
	

}

OrTri Trist::enext(OrTri ef){
	int version = ef && 7;
	int index = ef >> 3;
	if(triangles.at(index).isEmpty){
		return -1;
	} else{
		return (index<<3) | Trist::en_[version];
	}
}

OrTri Trist::sym(OrTri ef){
	int version = ef && 7;
	int index = ef >> 3;
	if(triangles.at(index).isEmpty){
		return -1;
	} else{
		if(version<3){
			return (index<<3) | version+3;
		} else{
			return (index<<3) | version-3;
		}
	}
}

void Trist::getVertexIdx(OrTri ef, int& pIdx1,int& pIdx2,int& pIdx3){
	int index = ef >> 3;
	int version = ef && 7;
	TriRecord record = Trist::triangles.at(index);
	/*if(record.isEmpty){
		pIdx1=-1;
		pIdx2=-1;
		pIdx3=-1;
	} else {*/
		pIdx1=record.vi_[v_[version]/100];
		pIdx2=record.vi_[v_[version]%100/10];
		pIdx3=record.vi_[v_[version]%10];
	/*}*/
}

int Trist::org(OrTri ef){
	int version = ef && 7;
	int index = ef >> 3;
	TriRecord record = Trist::triangles.at(index);
	if(!record.isEmpty){
		return record.vi_[v_[version]/100];
	} else {
		return -1;
	}
}

int Trist::dest(OrTri ef){
	int version = ef && 7;
	int index = ef >> 3;
	TriRecord record = Trist::triangles.at(index);
	if(!record.isEmpty){
		return record.vi_[v_[version]%10];
	} else {
		return -1;
	}
}


