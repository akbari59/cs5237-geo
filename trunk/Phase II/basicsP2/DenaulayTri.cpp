#include "DenaulayTri.h"
int DenaulayTri::inTri(OrTri& tri, int p){
	int tri_p[3];
	int	o, edge = 1;
	int min=0;
	
	trist.getVertexIdx(tri, tri_p[0] , tri_p[1], tri_p[2]);
	if(tri_p[min]<tri_p[1])
		min=1;
	if(tri_p[min]<tri_p[2])
	    min=2;
	if(tri_p[min]>0){
		o=psa.inTri(tri_p[0],tri_p[1],tri_p[2],edge);
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
			tri_p[2]=tri_p[1];
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
	return ot;

}
bool DenaulayTri::checkLegal(OrTri tri){
	OrTri neighbour=trist.fnext(trist.enext(tri));
	
	if(neighbour>-1){
		int p1, p2, p3;
	    trist.getVertexIdx(tri, p1, p2, p3);
	    int p4=trist.dest(trist.enext(neighbour));
		int result=psa.inCircle(p1,p2,p3,p4);
		return result<1;
	}else{
		return true;
	}
}

void DenaulayTri::legalizeEdge(OrTri tri)
{
	if(!checkLegal(tri))
	{
		OrTri tri1, tri2;
		flipEdge(tri,tri1, tri2);
		legalizeEdge(tri1);
		legalizeEdge(tri2);
	}

}

void DenaulayTri::flipEdge(OrTri old_tri1,  OrTri& new_tri1, OrTri& new_tri2){
	trist.flipEdge(old_tri1, new_tri1, new_tri2);
}
void DenaulayTri::insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3){
	trist.insertPoint(pIndex, tri, tri1, tri2, tri3);
}
void DenaulayTri::insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3, OrTri& tri4){
	trist.insertPoint(pIndex, tri, tri1, tri2, tri3, tri4);
}
DenaulayTri::DenaulayTri(){
	trist.makeTri(0, -1, -2);// 0 top; -1 right button; -2 left
}

