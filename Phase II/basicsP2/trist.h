#ifndef TRISTH
#define TRISTH

#include <vector>
#include "pointSetArray.h"
/*

  For a triangle abc, if version 0 is abc

  version 0 abc     (v:012)
  version 1 bca		(v:120)
  version 2 cab		(v:201)
  version 3 bac		(v:102)
  version 4 cba		(v:210)
  version 5 acb		(v:021)

  enext cycles   0 > 1 > 2 > 0 ,  5 > 4 > 3 > 5
  sym cycles  i <> i + 3 % 6

  org  = ver < 3 ? v[ver] : v[(ver+1)%3]
  dest = ver < 3 ? v[(ver+1)%3] : v[ver-3] 

*/



typedef  int OrTri;  // The OrTri data structure for a triangle
typedef  int FIndex; // The index of a triangle Hint: NOT a triangle if it's negative
                     // You should be able to make all the triangle indices to be from 0 to n - 1 (n = number of triangles)

class Trist;

class TriRecord {
	protected:
		int vi_[3];
		OrTri fnext_[6];
    public:	
		TriRecord(int p1, int p2, int p3);
		std::vector<OrTri> childs;
		bool isLeaf(){return childs.empty();};
		void addChilds(OrTri tri){childs.push_back(tri);};
		void setFnext(int version, OrTri tri){fnext_[version]=tri;};
	friend Trist;
	friend ostream& operator<< (ostream& out, TriRecord i );
};

class Trist {

	protected:
		
		int en_[6];
		int v_[6];
	public:
		std::vector<TriRecord> triangles;
		Trist();
		int noTri(); // return the number of triangles
		int makeTri(int pIndex1,int pIndex2,int pIndex3,bool autoMerge = false); // Add a triangle into the Trist with the three point indices
		// Moreover, automatically establish the fnext pointers to its neigbhours if autoMerge = true

		void delTri(OrTri); // Delete a triangle, but you can assume that this is ONLY used by the IP operation
		                    // You may want to make sure all its neighbours are detached (below)
		void delAllTri();

		OrTri findPoint(int pIndex, bool& boundary, PointSetArray psa); 
		/*tranverse through the tree structure. Starting from the first one, which is the biggest triangle.
		Boundary indicates whether the point lies on the boundary, true for on the boundary, false for inside the triangle
		If  boundary=true, the point lies on the 1st edge of the return oriented triangle.
		That's let the return triangle be abc, then the point p is on edge ab.
													 */               
		
		void insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3);
		/*Let tri=abc, and pIndex=d, then tri1=dab, tri2=dbc, tri3=dca. */
		
		void insertPoint(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2, OrTri& tri3, OrTri& tri4); 
		void splitTri(int pIndex, OrTri tri, OrTri& tri1, OrTri& tri2);
		//use when pIndex is on the first edge of the oriented triangle tri. 
		
		void flipEdge(OrTri old_tri1,  OrTri& new_tri1, OrTri& new_tri2);/*It will get the old_tri2 via fnext(enext(old_tri1)). If fnext(enext(old_tri1)) does not exists (fnext(enext(old_tri1))==-1), error will be thrown.
          Let old_tri1=abc and  fnext(enext(old_tri1))=bcd, then new_tri1=abd & new_tri2=acd. 
          
          */

		OrTri enext(OrTri ef);
		OrTri sym(OrTri ef);
		OrTri fnext(OrTri ef);

		void getVertexIdx(OrTri, int& pIdx1,int& pIdx2,int& pIdx3); // return the three indices of the three vertices by OrTri

		int org(OrTri);  // the index of the first vertex of OrTri, e.g. org(bcd) => b
		int dest(OrTri); // the index of the second vertex of OrTri, e.g. org(bcd) => c

		void fmerge(OrTri abc, OrTri abd); // glue two neighbouring triangles, result abd = fnext(abc)
		void checkSymmerge(OrTri abc, OrTri abd);
		void symMerge(OrTri abc, OrTri abd);
		void fdetach(OrTri abc); // detach triangle abc with all its neighbours (undo fmerge)

		void incidentTriangles(int ptIndex,int& noOrTri, OrTri* otList); // A suggested function: you may want this function to return all the OrTri
		                                                                 // that are incident to this point
		                                                                 // Ignore this if you don't feel a need
		friend ostream& operator<< (ostream& out, Trist i );

};


ostream& operator<< (ostream& out, TriRecord i );
ostream& operator<< (ostream& out, Trist i );
#endif