#include <numeric>
#include "pointSet.h"
using namespace std;

LongInt PointSet::l0(0);
int PointSet::addPoint(LongInt x1,LongInt y1){
	array<LongInt, 2> point={x1, y1};	
	set.push_back(point);
	return set.size();
}

int PointSet::inTri(int p1Idx, int p2Idx, int p3Idx, int pIdx){
	array<LongInt, 2> p1=set[p1Idx-1];
	array<LongInt, 2> p2=set[p2Idx-1];
	array<LongInt, 2> p3=set[p3Idx-1];
	array<LongInt, 2> p=set[pIdx-1];
	array<LongInt, 2> v0={p2[0]-p1[0],p2[1]-p1[1]};
	array<LongInt, 2> v1={p3[0]-p1[0],p3[1]-p1[1]};
	array<LongInt, 2> v={p[0]-p1[0],p[1]-p1[1]};
		
	LongInt dot00=inner_product(v0.begin(), v0.end(), v0.begin(), l0);
	LongInt dot01=inner_product(v0.begin(), v0.end(), v1.begin(), l0);
	LongInt dot0v=inner_product(v0.begin(), v0.end(), v.begin(), l0);
	LongInt dot11=inner_product(v1.begin(), v1.end(), v1.begin(), l0);
	LongInt dot1v=inner_product(v1.begin(), v1.end(), v.begin(), l0);

	LongInt denom=dot00 * dot11 - dot01 * dot01;
	LongInt u = dot11 * dot0v - dot01 * dot1v;
	LongInt w = dot00 * dot1v - dot01 * dot0v;

	int denomsign=denom.sign();
	int usign=u.sign();
	int wsign=w.sign();

	if(denomsign==usign&&denomsign==wsign){
		LongInt sum=u+w;
		if(denom<sum)
		   return -1;
		if(denom==sum)
			return 0;
		if(denom>sum)
			return 1;
	}
	if(usign==0){
		if(denomsign==wsign)
			if(denom>w)
				return 0;
			else
				return -1;
		else
			return -1;
	}
	if(wsign==0){
		if(denomsign==usign)
			if(denom>u)
				return 0;
			else
				return -1;
		else
			return -1;
	}
	return -1;
}

int PointSet::inCircle(int p1Idx, int p2Idx, int p3Idx, int pIdx){
	array<LongInt, 2> p1=set[p1Idx-1];
	array<LongInt, 2> p2=set[p2Idx-1];
	array<LongInt, 2> p3=set[p3Idx-1];
	array<LongInt, 2> p=set[pIdx-1];
	array<LongInt, 2> v0={p2[0]-p1[0],p2[1]-p1[1]};
	array<LongInt, 2> v1={p3[0]-p1[0],p3[1]-p1[1]};
	array<LongInt, 2> v ={p[0]-p1[0],p[1]-p1[1]};

	array<LongInt, 2> v1T={-v1[1], v1[0]};
	//centric=[v0(v0-v1)*v1T+v1]/(2*v1T*v0)
	LongInt denom=inner_product(v1T.begin(), v1T.end(), v0.begin(), l0); //coefficient 2 is ommitted here.
	
	array<LongInt, 2> v3={v0[0]-v1[0], v0[1]-v1[1]};
	LongInt coefficient=inner_product(v0.begin(), v0.end(), v3.begin(), l0);
	array<LongInt, 2> centric={coefficient*v1T[0]+v1[0], coefficient*v1T[1]+v1[1]};
	//dif(v, centric)
	array<LongInt, 2> dif={v[0]-centric[0], v[1]-centric[1]};
	LongInt dif2=inner_product(dif.begin(), dif.end(), dif.begin(), l0);
	LongInt r2=inner_product(centric.begin(), centric.end(), centric.begin(), l0);
	if(dif2>r2)
		return -1;
	else if(dif2<r2)
		return 1;
	else
		return 0;
}

