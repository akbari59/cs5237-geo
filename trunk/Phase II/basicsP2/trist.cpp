#include "trist.h"
#include "pointSetArray.h"


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
TriRecord::TriRecord(int p1, int p2, int p3):coordinate_available(false),birthtime_available(false){
    vi_[0] = p1;
	vi_[1] = p2;
	vi_[2] = p3;
	std::fill_n(fnext_, 6, -1);
	
}
int Trist::makeTri(int pIndex1,int pIndex2,int pIndex3){
	TriRecord record(pIndex1, pIndex2, pIndex3);
	
	
	int index = triangles.size();
	triangles.push_back(record);
	return index;
}

int Trist::makeTri(int pIndex1,int pIndex2,int pIndex3, const array<LongInt, 3>& norm){
	TriRecord record(pIndex1, pIndex2, pIndex3);
	record.setNorm(norm[0], norm[1], norm[2]);
	
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

OrTri Trist::enext(OrTri ef) const{
	int version = ef & 7;
	int index = ef >> 3;
	
		return (index<<3) | Trist::en_[version];
	
}

OrTri Trist::fnext(OrTri ef) const{
	int version = ef & 7;
	int index = ef >> 3;	
	return triangles[index].fnext_[version]; 	
}


OrTri Trist::sym(OrTri ef) const{
	int version = ef & 7;
	int index = ef >> 3;
	
		if(version<3){
			return (index<<3) | version+3;
		} else{
			return (index<<3) | version-3;
		}
	
}

bool Trist::getVertexIdx(OrTri ef, int& pIdx1,int& pIdx2,int& pIdx3) const{
	int index = ef >> 3;
	int version = ef & 7;
	const TriRecord& record = triangles.at(index);
	
		pIdx1=record.vi_[v_[version]/100];
		pIdx2=record.vi_[v_[version]%100/10];
		pIdx3=record.vi_[v_[version]%10];
	
		return record.isLeaf();
}

int Trist::org(OrTri ef) const{
	int version = ef & 7;
	int index = ef >> 3;
	const TriRecord& record = Trist::triangles.at(index);
	
	return record.vi_[v_[version]/100];
	
}

int Trist::dest(OrTri ef) const{
	int version = ef & 7;
	int index = ef >> 3;
	const TriRecord& record = triangles[index];
	
	return record.vi_[(v_[version]/10)%10];
	
}


void Trist::setNorm(OrTri ori, const array<LongInt, 3>& norm){
	int index = ori >> 3;
	TriRecord& tri=triangles[index];
	tri.setNorm(norm[0], norm[1], norm[2]);
}
array<LongInt, 3> Trist::getNorm(OrTri ori) const{
	int index = ori >> 3;
	const TriRecord& tri=triangles[index];
	array<LongInt, 3> output={tri.norm[0], tri.norm[1], tri.norm[2]};
	return output;
}
void Trist::insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3){
	int p1, p2, p3;
	int index=tri>>3;

	getVertexIdx(tri, p1, p2, p3);	
	tri1=makeTri(pIndex, p1, p2 )<<3;	
	tri2=makeTri(pIndex, p2, p3 )<<3;	
	tri3=makeTri(pIndex, p3, p1 )<<3;

	//set neigbours
	//links to neigbours tri
	OrTri neighbour=fnext(tri);
	
	checkSymmerge(enext(tri1), neighbour);
	tri=enext(tri);
	neighbour=fnext(tri);
	checkSymmerge(enext(tri2), neighbour);
	tri=enext(tri);
	neighbour=fnext(tri);
	checkSymmerge(enext(tri3), neighbour);
	
	//merge among tri1, tri2 & tri3
	symMerge(enext(enext(tri1)), sym(tri2));
	symMerge(enext(enext(tri2)), sym(tri3));
	symMerge(enext(enext(tri3)), sym(tri1));
	

	//add childs
	TriRecord& record=triangles[index];
	record.addChilds(tri1);
	record.addChilds(tri2);
	record.addChilds(tri3);

}//auto merge 3 new triangles to their neigbours. insert new triangle to the childs.

void Trist::checkSymmerge(OrTri abc, OrTri abd){
	if(abc!=-1 && abd!=-1 )
	  symMerge(abc, abd);
	
}

void Trist::symMerge(OrTri abc, OrTri abd){
	
	  fmerge(abc, abd);
	  fmerge(sym(abc), sym(abd));
	
}

void Trist::fmerge(OrTri abc, OrTri abd){
	int index1=abc>>3;
	int version1= abc & 7;
	int	index2=abd>>3;
	int	version2=abd & 7;
	triangles[index1].setFnext(version1, abd);
	triangles[index2].setFnext(version2, abc);
	
}

void Trist::flipEdge(OrTri old_tri1, OrTri& new_tri1, OrTri& new_tri2){//auto merge 2 new triangles to their neigbour.
	OrTri old_tri2=fnext(enext(old_tri1));
	int p1, p2, p3;
	getVertexIdx(old_tri1, p1, p2, p3);
	int p4=dest(enext(old_tri2));

	new_tri1=makeTri(p1, p2, p4)<<3;	
	new_tri2=makeTri(p1, p3, p4)<<3;

	//glue the new 2 triangles with neighbours of old triangles
	OrTri neighbour=fnext(old_tri1);
	checkSymmerge(new_tri1, neighbour);
	
	neighbour=fnext(enext(sym(old_tri1)));
	checkSymmerge(new_tri2, neighbour);
	

	

	
	checkSymmerge(enext(new_tri1), fnext(enext(sym(old_tri2))));
	checkSymmerge(enext(new_tri2), fnext(enext(old_tri2)));

	
	

	//glue the two new triangle
	symMerge(enext(enext(new_tri1)), enext(enext(new_tri2)));
	

	int index1=old_tri1>>3;
	int index2=old_tri2>>3;
	TriRecord& record1=triangles[index1];
	record1.addChilds(new_tri1);
	record1.addChilds(new_tri2);
	TriRecord& record2=triangles[index2];
	record2.addChilds(new_tri1);
	record2.addChilds(new_tri2);
}
void Trist::obtuseflipEdge(OrTri old_tri1,  OrTri& new_tri1, OrTri& new_tri2){
		OrTri old_tri2=fnext(enext(old_tri1));
	int p1, p2, p3; 
	getVertexIdx(old_tri1, p1, p2, p3);
	int p4=dest(enext(old_tri2)); 

	new_tri1=makeTri(p1, p2, p4)<<3;	
	new_tri2=makeTri(p1, p3, p4)<<3;

	//glue the new 2 triangles with neighbours of old triangles
	OrTri neighbour=fnext(old_tri1);
	checkSymmerge(new_tri1, neighbour);
	
	neighbour=fnext(enext(sym(old_tri1)));
	checkSymmerge(new_tri2, neighbour);
	

	

	
	checkSymmerge(enext(new_tri1), fnext(enext(sym(old_tri2))));
	checkSymmerge(enext(new_tri2), fnext(enext(old_tri2)));

	
	

	//glue the two new triangle
	symMerge(enext(enext(new_tri1)), enext(enext(new_tri2)));
	

	int index1=old_tri1>>3;
	int index2=old_tri2>>3;
	TriRecord& record1=triangles[index1];
	record1.addChilds(new_tri2);
	TriRecord& record2=triangles[index2];
	record2.addChilds(new_tri2);
	TriRecord& newRecord1=triangles[new_tri1>>3];
	newRecord1.addChilds(new_tri2);
}
bool Trist::isLeaf(OrTri tri) const
{
	int index=tri >> 3;
	const TriRecord& triangleRecord=triangles[index];
	return triangleRecord.isLeaf();
}

ostream& operator<< (ostream& out, TriRecord i ){
	out<<"p1:"<<i.vi_[0]<<", p2:"<<i.vi_[1]<<", p3:"<<i.vi_[2]<<", n1:"<<(i.fnext_[0]>>3)<<", n2:"<<(i.fnext_[1]>>3)<<", n3:"<<(i.fnext_[2]>>3)<<", n4:"<<i.fnext_[3]<<", n5:"<<i.fnext_[4]<<", n6:"<<i.fnext_[5];
	out<<" childs:";
	for (vector<OrTri>::iterator it=i.childs.begin() ; it < i.childs.end(); it++ )
       out << " " << *it;
	return out;
}
bool Trist::selfMerge(OrTri tri) const{
	OrTri opposite=fnext(enext(tri));
	if(opposite>-1)
	    return dest(enext(opposite))==org(tri);
	else
		return false;
}
ostream& operator<< (ostream& out, Trist i ){
	int c=0;
	for (vector<TriRecord>::iterator it=i.triangles.begin() ; it < i.triangles.end(); it++ ){
       out<<c++<<*it<<endl;
	}
	return out;
}

/*
OrTri Trist::findPoint(int pIndex, bool& boundary, PointSetArray psa)
{

	
	int intri_result = -1;
	bool isLeaf = false;
	int  index= 0;
	int p1, p2, p3;
	//start from root
	TriRecord triRec=triangles[0];
	OrTri ot = 0;
	boundary = false;
	//Search thorough tree untill we reach a leaf
	while(!isLeaf)
	{

		//check for every child and find the one that our point is inside it
		for(int i = 0; i < triRec.childs.size(); i++)
		{
			ot = triRec.childs[i];
			this->getVertexIdx(ot, p1, p2, p3);
			intri_result=psa.inTri(p1, p2, p3, pIndex);
			// is inside triangles
			if(intri_result == 1)
			{
				triRec = triangles[ot>>3];

			}else if(intri_result == 0)	// is on the boundry
			{
				triRec = triangles[ot>>3];
				//should be fixed
				//FIXME:
				boundary = true;
			}

		}

		if (triRec.isLeaf()) isLeaf = true;
		
	}

	return ot;

}

*/
void Trist::insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3, OrTri& tri4){
	splitTri(pIndex, tri, tri1, tri2);
	//neighbour must exists, a point cannot lie on the imaginary boundary.
	OrTri neighbour=fnext(tri);


	splitTri(pIndex, neighbour, tri3, tri4);
	symMerge(tri1, tri3);	
	symMerge(tri2, tri4);
	

}
void Trist::splitTri(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2){
	int p1, p2, p3;
	int index=tri>>3;

	getVertexIdx(tri, p1, p2, p3);	
	tri1=makeTri(pIndex, p1, p3)<<3;	
	tri2=makeTri(pIndex, p2, p3)<<3;	
	checkSymmerge(enext(tri1), fnext(enext(sym(tri))));
	checkSymmerge(enext(tri2), fnext(enext(tri)));
	symMerge(enext(enext(tri1)),enext(enext(tri2)));

	TriRecord& record1=triangles[index];
	record1.addChilds(tri1);
	record1.addChilds(tri2);
}

void Trist::addChild(OrTri child, OrTri parent){
	int parentIdx=parent >> 3;
	TriRecord& pRecord=triangles[parentIdx];
	pRecord.addChilds(child);
}

