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
	int index = triangles.size();
	triangles.push_back(record);
	if(autoMerge){
		for(int i = 0; i<index; i++){
			//sharePoint[3] is the index of the unsharedPoint. e.g. p0 = q0, p1 = q1, p2!= q2. sharePoint[2] = q2 but sharePoint[3] = 2.
			//sharePoint[3] = -1 means there is no shared edge.
			int sharePoint[4] = {-1, -1, -1, -1};
			checkShare(record, triangles.at(i), sharePoint);
			if(sharePoint[3] >=0){
				OrTri abc, abd;
				int targetDirection;
				switch(sharePoint[3]){
				case 0:
					abc = index<<3 | 1;
					targetDirection = sharePoint[1]*100 + sharePoint[2]*10 + sharePoint[0];
					break;
				case 1:
					abc = index<<3 | 5;
					targetDirection = sharePoint[0]*100 + sharePoint[2]*10 + sharePoint[1];
					break;
				case 2:
					abc = index<<3 | 0;
					targetDirection = sharePoint[0]*100 + sharePoint[1]*10 + sharePoint[2];
					break;
				}
				int version = getVersion(targetDirection);
				abd = i<<3 | version;
				fmerge(abc, abd);
				fmerge(sym(abc), sym(abd));
			}
		}
	}
	return index;
}

int Trist::getVersion(int direction){
	for(int j = 0; j<6; j++){
		if(v_[j]==direction){
			return j;
		}
	}
}

void Trist::checkShare(TriRecord record1, TriRecord record2, int sharePoints[]){
	bool taken[3];
	for(int j = 0; j < 3; j++){
		for(int k = 0; k <3 ; k++){
			if(record1.vi_[j] == record2.vi_[k]){
				sharePoints[j] = k;
				taken[k] = true;
				break;
			}
		}
		if(sharePoints[j]==-1){
			if(sharePoints[3]==-1){
				sharePoints[3] = j;
			} else{
				sharePoints[3] = -1;
				return;
			}
		}
	}
	if(sharePoints[3]>=0){
		for(int i = 0; i < 3; i++)
			if(!taken)
				sharePoints[sharePoints[3]] = i;
	}
}

void Trist::delTri(OrTri ef){
	int index = ef >> 3;
	triangles.erase(triangles.begin()+index);
	//triangles.at(index).isEmpty = true;
}

void Trist::eraseAll(){
	triangles.clear();
}

OrTri Trist::enext(OrTri ef){
	int version = ef & 7;
	int index = ef >> 3;
	if(triangles.at(index).isEmpty){
		return -1;
	} else{
		return (index<<3) | Trist::en_[version];
	}
}

OrTri Trist::sym(OrTri ef){
	int version = ef & 7;
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
	int version = ef & 7;
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

void Trist::fmerge(OrTri abc, OrTri abd){
	int index1 = abc >> 3;
	int index2 = abd >> 3;
	int version1 = abc & 7;
	int version2 = abd & 7;
	Trist::triangles.at(index1).fnext_[version1] = abd;
	triangles.at(index2).fnext_[version2] = abc;
}

void Trist::fdetach(OrTri abc){
	int index = abc >> 3;
	int version = abc & 7;
	Trist::triangles.at(index).fnext_[version] = 0;
}

OrTri Trist::fnext(OrTri ef){
	int version = ef & 7;
	int index = ef >> 3;
	return Trist::triangles.at(index).fnext_[version];
}

int Trist::org(OrTri ef){
	int version = ef & 7;
	int index = ef >> 3;
	TriRecord record = Trist::triangles.at(index);
	if(!record.isEmpty){
		return record.vi_[v_[version]/100];
	} else {
		return -1;
	}
}

int Trist::dest(OrTri ef){
	int version = ef & 7;
	int index = ef >> 3;
	TriRecord record = Trist::triangles.at(index);
	if(!record.isEmpty){
		return record.vi_[v_[version]%10];
	} else {
		return -1;
	}
}


