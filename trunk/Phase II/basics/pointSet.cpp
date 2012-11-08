#include <numeric>
#include <iostream>
#include "pointSet.h"
using namespace std;

LongInt PointSet::l0(0);
int PointSet::addPoint(LongInt x1,LongInt y1, LongInt weight){
	array<LongInt, 4> point={x1, y1, weight, projectZ(x1, y1, weight)};	
	set.push_back(point);
	return set.size();
}

int PointSet::inTri(int p1Idx, int p2Idx, int p3Idx, int pIdx){
	
	const array<LongInt, 4>& p1=set[p1Idx-1];
	const array<LongInt, 4>& p2=set[p2Idx-1];
	const array<LongInt, 4>& p3=set[p3Idx-1];
	const array<LongInt, 4>& p=set[pIdx-1];

	if (((p[0] == p1[0]) && (p[1] == p1[1])) ||
		 ((p[0] == p2[0]) && (p[1] == p2[1])) ||
		  ((p[0] == p3[0]) && (p[1] == p3[1])) )
		  return 0;
		

	array<LongInt, 3> v0={p2[0]-p1[0],p2[1]-p1[1]};
	array<LongInt, 3> v1={p3[0]-p1[0],p3[1]-p1[1]};
	array<LongInt, 3> v={p[0]-p1[0],p[1]-p1[1]};
	/*cout<<"v1[0]:"<<endl<<v1[0]<<endl;
	cout<<"v1[1]:"<<endl<<v1[1]<<endl;
	cout<<"v[0]:"<<endl<<v[0]<<endl;
	cout<<"v[1]:"<<endl<<v[1]<<endl;*/
	
	if(v0[0]*v1[1]==v0[1]*v1[0])
		return 0;
	LongInt dot00=inner_product(v0.begin(), v0.end(), v0.begin(), l0);
	LongInt dot01=inner_product(v0.begin(), v0.end(), v1.begin(), l0);
	LongInt dot0v=inner_product(v0.begin(), v0.end(), v.begin(), l0);
	LongInt dot11=inner_product(v1.begin(), v1.end(), v1.begin(), l0);
	LongInt dot1v=inner_product(v1.begin(), v1.end(), v.begin(), l0);
	
	/*cout<<"dot00:"<<endl<<dot00<<endl;
	cout<<"dot01:"<<endl<<dot01<<endl;
	cout<<"dot0v:"<<endl<<dot0v<<endl;
	cout<<"dot11:"<<endl<<dot11<<endl;
	cout<<"dot1v:"<<endl<<dot1v<<endl;*/
	
	LongInt denom=dot00 * dot11 - dot01 * dot01;

	//cout<<"denom:"<<endl<<denom<<endl;

	if(denom.sign()==0)
		
		return 0;
	
	LongInt u = dot11 * dot0v - dot01 * dot1v;
	LongInt w = dot00 * dot1v - dot01 * dot0v;

	//cout<<u<<endl;
	//cout<<w<<endl;

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

int PointSet::pN2pN1InTri(int p3Idx, int pIdx){
	const array<LongInt, 4>& p3=set[p3Idx-1];
	const array<LongInt, 4>& p=set[pIdx-1];
	if(p3[1]>p[1])
		return 1;
	else
		return -1;
}

int PointSet::pNp0InTri(int pN, int p3Idx, int pIdx){
	const array<LongInt, 4>& p3=set[p3Idx-1];
	const array<LongInt, 4>& p=set[pIdx-1];
	if(p[1]<p3[1])
		return -1;
	if (p[0]==p3[0])
		return 0;
	if(pN==-1){
		if(p[0]>p3[0])
		  return 1;
		else
		  return -1;
	}else{
		if(p[0]<p3[0])
			return 1;
		else
			return -1;
	}
}


int PointSet::pNInTri(int sym, int p2Idx, int p3Idx, int pIdx){
	const array<LongInt, 4>& p2=set[p2Idx-1];
	const array<LongInt, 4>& p3=set[p3Idx-1];
	const array<LongInt, 4>& p=set[pIdx-1];
	if(p2[1]==p3[1]){
		if(p[1]==p2[1]&&((p2[0]<p[0]&&p[0]<p3[0])||(p2[0]>p[0]&&p[0]>p3[0]))){
			
			return 0;
		}else{
			return -1;
		}
	}

	
	int side;
	if (p2[1]>p3[1]){
		if(p[1]>p2[1]||p[1]==p2[1]||p[1]<p3[1]){
			return -1;
		}else{
		 side=getside(p2, p3, p);
		}
	}else{
		if(p[1]<p2[1]||p[1]>p3[1]||p[1]==p3[1]){
			return -1;
		}else{
		 side=getside(p3, p2, p);
		}
	}
	if(sym==-1)
		return side;
	else
	    return -side;
}

int PointSet::p0InTri( int p2Idx, int p3Idx, int pIdx, int& edge){
	array<LongInt, 4> const& p2=set[p2Idx-1];
	array<LongInt, 4> const& p3=set[p3Idx-1];
	array<LongInt, 4> const& p=set[pIdx-1];
	if((p[0]<p2[0]&&p[0]<p3[0])||(p[0]>p2[0]&&p[0]>p3[0])||(p[1]<p2[1]&&p[1]<p3[1]))
	  return -1;
	
	if(p[0]==p2[0]&&p[1]>p2[1]){
		edge=0;
		return 0;
	}
	if(p[0]==p3[0]&&p[1]>p3[1]){
		edge=2;
		return 0;
	}
	if((p[1]>p2[1]&&p[1]>p3[1]))
		return 1;
	int side;
	if(p2[0]<p3[0])
	  side=getside(p2, p3, p);
	else
      side=getside(p3, p2, p);
	if(side==0)
		edge=1;
	return side;
}

/*int PointSet::inTri(int p1Idx, int p2Idx, int p3Idx, int pIdx, int& edge){
	array<LongInt, 3> p1=set[p1Idx-1];
	array<LongInt, 3> p2=set[p2Idx-1];
	array<LongInt, 3> p3=set[p3Idx-1];
	array<LongInt, 3> p=set[pIdx-1];
	int correctside=getside(p1,p2,p3);
	
	int side=getside(p1,p2,p);
	bool onBoundary=false;
	if(side==0){
		edge=0;
		onBoundary=true;
	}else if(correctside!=side){
		return -1;
	}
	side=getside(p2,p3,p);
	if(side==0){
		edge=1;
		onBoundary=true;
	}else if(correctside!=side){
		return -1;
	}
	side=getside(p3,p1,p);
	if(side==0){
		edge=2;
		onBoundary=true;
	}else if(correctside!=side){
		return -1;
	}
	if(onBoundary)
		return 0;
	else
		return 1;
}*/



int PointSet::inTri(int p1Idx, int p2Idx, int p3Idx, int pIdx, int& edge){
	
	const array<LongInt, 4>& p1=set[p1Idx-1];
	const array<LongInt, 4>& p2=set[p2Idx-1];
	const array<LongInt, 4>& p3=set[p3Idx-1];
	const array<LongInt, 4>& p=set[pIdx-1];

	if ( ((p[0] == p1[0]) && (p[1] == p1[1])) ||
		 ((p[0] == p2[0]) && (p[1] == p2[1])) ||
		 ((p[0] == p3[0]) && (p[1] == p3[1])) ){
			  edge=-1;
			  return 0;
	}
		  
		

	array<LongInt, 3> v0={p2[0]-p1[0],p2[1]-p1[1]};
	array<LongInt, 3> v1={p3[0]-p1[0],p3[1]-p1[1]};
	array<LongInt, 3> v={p[0]-p1[0],p[1]-p1[1]};
	
	
	
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
		if(denom==sum){
			edge=1;
			return 0;
		}
		if(denom>sum)
			return 1;
	}
	if(usign==0){
		if(denomsign==wsign)
			if(denom>w){
				edge=2;
				return 0;
			}else
				return -1;
		else
			return -1;
	}
	if(wsign==0){
		if(denomsign==usign)
			if(denom>u){
				edge=0;
				return 0;
			}else
				return -1;
		else
			return -1;
	}
	return -1;
}
int PointSet::symInCircle(int p1Idx, int p2Idx, int p3Idx, int sym){
	array<LongInt, 4>& p1=set[p1Idx-1];
	array<LongInt, 4>& p2=set[p2Idx-1];
	array<LongInt, 4>& p3=set[p3Idx-1];
	int side=getside(p1, p2, p3);
	if(sym==0){
		if(p1[0]>p3[0])
			return -side;
		else
			return side;
	}
	if(sym==-1){
		if(p1[1]>p3[1])
			return side;
		else
			return -side;
	}else{
		if(p1[1]>p3[1])
			return -side;
		else
			return side;
	}
}
int PointSet::inCircle(int p1Idx, int p2Idx, int p3Idx, int pIdx){
	if(pIdx<1){
		if(p2Idx>0&&p3Idx>0)
		  return -1;
		else if(pIdx<0&&(p2Idx==0||p3Idx==0))
			return 1;
		else
		    return -1;
	}
	else if(p2Idx<1){
		return symInCircle(p1Idx, p3Idx, pIdx, p2Idx);
	}else if(p3Idx<1){
		return symInCircle(p1Idx, p2Idx, pIdx, p3Idx);
	}
	array<LongInt, 4>& p1=set[p1Idx-1];
	array<LongInt, 4>& p2=set[p2Idx-1];
	array<LongInt, 4>& p3=set[p3Idx-1];
	array<LongInt, 4>& p=set[pIdx-1];
	array<LongInt, 3> v0={p2[0]-p1[0],p2[1]-p1[1]};
	array<LongInt, 3> v1={p3[0]-p1[0],p3[1]-p1[1]};
	array<LongInt, 3> v ={p[0]-p1[0],p[1]-p1[1]};
	if(v0[0]*v1[1]==v0[1]*v1[0])
		return 0;
	array<LongInt, 3> v1T={-v1[1], v1[0]};
	//centric=[v0(v0-v1)*v1T+v1]/(2*v1T*v0)
	LongInt denom=inner_product(v1T.begin(), v1T.end(), v0.begin(), l0); //coefficient 2 is ommitted here.
	
	array<LongInt, 3> v3={v0[0]-v1[0], v0[1]-v1[1]};
	LongInt coefficient=inner_product(v0.begin(), v0.end(), v3.begin(), l0);
	array<LongInt, 3> centric={coefficient*v1T[0]+denom*v1[0], coefficient*v1T[1]+denom*v1[1]};
	//dif(v, centric)
	array<LongInt, 3> dif={denom*v[0]*2-centric[0], denom*v[1]*2-centric[1]};
	LongInt dif2=inner_product(dif.begin(), dif.end(), dif.begin(), l0);
	LongInt r2=inner_product(centric.begin(), centric.end(), centric.begin(), l0);
	if(dif2>r2)
		return -1;
	else if(dif2<r2)
		return 1;
	else
		return 0;
	
}

