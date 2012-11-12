#include "DenaulayTri.h"
int DenaulayTri::inTri(OrTri& tri, int p){
	int tri_p[3];
	int	o, edge = 1;
	int min=0;
	
	trist.getVertexIdx(tri, tri_p[0] , tri_p[1], tri_p[2]);
	if(tri_p[min]>tri_p[1])
		min=1;
	if(tri_p[min]>tri_p[2])
	    min=2;
	if(tri_p[min]>0){
		o=psa.inTri(tri_p[0],tri_p[1],tri_p[2], p,edge);
		if(o==0)
		 for (;edge>0;edge--)
			tri=trist.enext(tri);
		return o;
	}else{
		if(min>0){
		 for(;min>0;min--)
			tri=trist.enext(tri);
		 trist.getVertexIdx(tri, tri_p[0] , tri_p[1], tri_p[2]);
		}
		if(tri_p[1]>tri_p[2]){
			tri=trist.enext(trist.sym(tri));
			int temp=tri_p[1];
			tri_p[1]=tri_p[2];
			tri_p[2]=temp;
		}
		if(tri_p[2]<1)
			return 1;
		
		switch(tri_p[1]){
		   case 0:
			   o=psa.pNp0InTri(tri_p[0], tri_p[2], p);
			   if(o==0)
				   tri=trist.enext(tri);
			   return o;
		   case -1:
			   o=psa.pN2pN1InTri(tri_p[2],p);
			   return o;
		}
		switch(tri_p[0]){
			case 0:
				o=psa.p0InTri(tri_p[1], tri_p[2], p, edge);
				if(o==0)
		           for (;edge>0;edge--)
			           tri=trist.enext(tri);
		        return o;
			default:
				o=psa.pNInTri(tri_p[0], tri_p[1], tri_p[2], p);
				if(o==0)
					tri=trist.enext(tri);
				return o;
		}
	}
	
}

OrTri DenaulayTri::findPoint(int p, bool& boundary)
{

	
	int intri_result = -1;
	
	int  index= 0;
	
	//start from root
	TriRecord triRec=trist.triangles[0];
	OrTri ot = 0;

	//Search thorough tree untill we reach a leaf
	while(!triRec.isLeaf())
	{

		//check for every child and find the one that our point is inside it
		for(unsigned i = 0; i < triRec.childs.size(); i++)
		{
			ot = triRec.childs[i];
			
			
			intri_result=inTri(ot, p);
			// is inside triangles
			if(intri_result >=0)
			{
				triRec = trist.triangles[ot>>3];
				break;
			}/* The edge may have been destroyed, if the triangle is not a leaf.
			else if(intri_result == 0)	// is on the boundry
			{
				triRec = trist.triangles[ot>>3];
				boundary=true;
				
			}*/

		}

		
		
	}
	if(intri_result==0)
		boundary=true;
	else
		boundary=false;
	return ot;

}


bool DenaulayTri::checkLegal(OrTri tri) const{
	OrTri neighbour=trist.fnext(trist.enext(tri));
	
	if(neighbour>-1){
		/*int p1, p2, p3;
	    trist.getVertexIdx(tri, p1, p2, p3);
	    int p4=trist.dest(trist.enext(neighbour));
	    */
		
		int result=checkBelowPlane(trist.org(tri), neighbour);
		/*int result=psa.inCircle(p1,p2,p3,p4);*/
		return result<1;
	}else{
		return true;
	}
}

void DenaulayTri::legalizeEdge(OrTri tri)
{
	if(trist.isLeaf(tri)){
		if(trist.selfMerge(tri)){
			OrTri selfNeighbour=trist.fnext(trist.enext(trist.enext(tri)));
            OrTri opposite=trist.fnext(trist.enext(tri));
			OrTri oppositeNeighbour=trist.fnext(trist.enext(opposite));
			trist.checkSymmerge(selfNeighbour, oppositeNeighbour);
			//trist.addChild(oppositeNeighbour, tri);
			trist.addChild(opposite, tri);
		}else if(!checkLegal(tri))
	    {
		  int oflip_v=isObtuseFlip(tri);
		  if(oflip_v>-1){
		    OrTri tri1, tri2; //tri3;
		    //OrTri tri4=-1;
		    trist.obtuseflipEdge(tri, tri1, tri2);//may need special flip, tri1 cannot be add as child
		    tri1=trist.fnext(tri1);
			legalizeEdge(tri1);
			legalizeEdge(tri2);
		    /*vector<OrTri> newTriangle;
		    newTriangle.push_back(tri2);
		    while(!trist.selfMerge(tri1)){			 
		     flipEdge(tri1, tri3, tri4);
			 newTriangle.push_back(tri4);
		     tri1=tri3;		  
		   }
		  trist.addChild(tri2, tri1);
		  if(tri4>-1){
		  
		   trist.symMerge(trist.enext(trist.sym(tri4)), trist.enext(trist.sym(tri2)));
		  }else{
			 OrTri neighbour=trist.fnext(trist.enext(trist.sym(tri1)));
			 trist.symMerge(neighbour, trist.enext(trist.sym(tri2)));
		  }
		 
		 for(int i=0; i<newTriangle.size(); i++){
			 legalizeEdge(newTriangle[i]);
		 }*/
		 }else{
		  OrTri tri1, tri2;
		  flipEdge(tri, tri1, tri2);
		  legalizeEdge(tri1);
		  legalizeEdge(tri2);
		 }
	  }else{
	    setNorm(tri);
	  }
	}

}
int DenaulayTri::isObtuseFlip(OrTri& tri) const{
	OrTri neighbour=trist.fnext(trist.enext(tri));
	int p4=trist.dest(trist.enext(neighbour));
	int p1, p2, p3;
	trist.getVertexIdx(tri, p1, p2, p3);
	if(p2>0&&p3>0&&p4>0){
		LongInt p2Area=psa.getTriangeSide2TimesArea(p1, p4, p2);
		LongInt p3Area=psa.getTriangeSide2TimesArea(p1, p4, p3);
		int output=p2Area.sign()*p3Area.sign();
		if(output>-1){
			p2Area.takeAbs();
			p3Area.takeAbs();
			if(p2Area>p3Area)
				tri=trist.enext(trist.sym(tri));
		}
		return output;
	}else{
		return -1;
	}
}
void DenaulayTri::flipEdge(OrTri old_tri1,  OrTri& new_tri1, OrTri& new_tri2){
	trist.flipEdge(old_tri1, new_tri1, new_tri2);
}
                  
bool DenaulayTri::insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3){
	   if(checkBelowPlane(pIndex, tri, true)>-1){
	      trist.insertPoint(pIndex, tri, tri1, tri2, tri3);
	      setNorm(tri1);
	      setNorm(tri2);
	      setNorm(tri3);
	      return true;
	   }else{
		   return false;
	   }
}
void DenaulayTri::setNorm(OrTri tri){
	int p1, p2, p3;
	trist.getVertexIdx(tri, p1, p2, p3);
	if(p1>0&&p2>0&&p3>0){
		array<LongInt, 3> norm;
		psa.getPlaneNorm(p1, p2, p3, norm);
		trist.setNorm(tri, norm);
	}
}
int DenaulayTri::checkSymBelowPlane(int p1Idx, int p2Idx, int p3Idx, int pIdx) const{
	//p1Idx newly insert point
	if(pIdx<1){
		if(p2Idx>0&&p3Idx>0)
		  return -1;
		else if(pIdx<0&&(p2Idx==0||p3Idx==0))
			return 1;
		else
		    return -1;
	}
	else if(p2Idx<1){
		return psa.symInCircle(p1Idx, p3Idx, pIdx, p2Idx);
	}else{
		return psa.symInCircle(p1Idx, p2Idx, pIdx, p3Idx);
	}
}
int DenaulayTri::checkBelowPlane(int pIndex, OrTri tri, bool inTri) const{
	
	 int p1, p2, p3;	 
	 trist.getVertexIdx(tri, p1, p2, p3);

	 if(p1>0&&p2>0&&p3>0){
       array<LongInt, 3> norm=trist.getNorm(tri);
	   LongInt x, y, w, z, x1, y1, w1, z1;
	   psa.getPoint(pIndex, x, y, w, z);
	   psa.getPoint(p1, x1, y1, w1, z1);
	   LongInt vp[3]={x-x1, y-y1, z-z1};
	   LongInt dotproduct=vp[0]*norm[0]+ vp[1]*norm[1]+vp[2]*norm[2];
	   return dotproduct.sign();
	 }else{
		 if(inTri)
			 return 1;
		 else
		 return checkSymBelowPlane(pIndex, p1, p2, p3);
	 }
}
bool DenaulayTri::insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3, OrTri& tri4){
	if(checkBelowPlane(pIndex, tri, true)>-1){
	      trist.insertPoint(pIndex, tri, tri1, tri2, tri3, tri4);
	      setNorm(tri1);
	      setNorm(tri2);
	      setNorm(tri3);
		  setNorm(tri4);
	      return true;
	}else{
		   return false;
	}
	 
	 
}
DenaulayTri::DenaulayTri(){
	//trist.makeTri(0, -1, -2);// 0 top; -1 right button; -2 left
	init();
}

void DenaulayTri::init(){
	trist.makeTri(0, -1, -2);// 0 top; -1 right button; -2 left
}

int DenaulayTri::checkPointSideRational(OrTri tri, const LongInt& x, const LongInt& y, const LongInt& denominator) const{
	int p1, p2, p3;
	trist.getVertexIdx(tri, p1, p2, p3);
	int p3side=psa.getPointSide(p1,p2,p3);
	int pside=psa.getPointSideRational(p1, p2, x, y, denominator);
	return p3side*pside;
}
int DenaulayTri::checkVoronoiSideRational(OrTri tri){
	LongInt x, y, denominator;
	if(!trist.voronoiVertexAvailable(tri)){
		computeVoronoiVertex(tri);
	}
	trist.getVoronoiVertex(tri, x, y, denominator);
	return checkPointSideRational(tri, x, y, denominator); 
}
void DenaulayTri::computeVoronoiVertex(OrTri tri){
	int p1, p2, p3;
	trist.getVertexIdx(tri, p1, p2, p3);
	LongInt x, y, denominator;
	psa.computeVoronoiVertex(p1, p2, p3, x, y, denominator);
	trist.setVoronoiVertex(tri, x, y, denominator);

}
bool DenaulayTri::compareBirthTime(OrTri tri, const LongInt& AlphaSquare){
	
	if(!trist.birthTimeAvailable(tri)){
		int p1=trist.org(tri);
		if(!trist.voronoiVertexAvailable(tri)){
		   computeVoronoiVertex(tri);
	    }
		trist.setbirthTime(tri, psa.set[p1-1]);
	}
	return trist.compareBirthTime(tri, AlphaSquare);
}