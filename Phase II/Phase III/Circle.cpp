// Circle.cpp: implementation of the Circle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "MediSurf.h"
#include "Circle.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Circle::Circle()
{
	this->m_dRadius=-1;		// error checking 
}

Circle::~Circle()
{

}

Circle::Circle(double pt1x, double pt1y,double pt2x, double pt2y, double pt3x, double pt3y )
{
	this->m_dRadius=-1;		// error checking 

		
	
	if (!this->IsPerpendicular(pt1x, pt1y, pt2x, pt2y, pt3x, pt3y) )			this->CalcCircle(pt1x, pt1y, pt2x, pt2y, pt3x, pt3y);	
	else if (!this->IsPerpendicular(pt1x, pt1y, pt3x, pt3y, pt2x, pt2y) )		this->CalcCircle(pt1x, pt1y, pt3x, pt3y, pt2x, pt2y);	
	else if (!this->IsPerpendicular(pt2x, pt2y, pt1x, pt1y, pt3x, pt3y) )		this->CalcCircle(pt2x, pt2y, pt1x, pt1y, pt3x, pt3y);	
	else if (!this->IsPerpendicular(pt2x, pt2y, pt3x, pt3y, pt1x, pt1y) )		this->CalcCircle(pt2x, pt2y, pt3x, pt3y, pt1x, pt1y);	
	else if (!this->IsPerpendicular(pt3x, pt3y, pt2x, pt2y, pt1x, pt1y) )		this->CalcCircle(pt3x, pt3y, pt2x, pt2y, pt1x, pt1y);	
	else if (!this->IsPerpendicular(pt1x, pt3y, pt1x, pt1y, pt2x, pt2y) )		this->CalcCircle(pt1x, pt3y, pt1x, pt1y, pt2x, pt2y);	
	else { 
//		TRACE("\nThe three pts are perpendicular to axis\n");

		this->m_dRadius=-1;
		return ;
	}


}


bool Circle::IsPerpendicular(double pt1x, double pt1y,double pt2x, double pt2y, double pt3x, double pt3y )
// Check the given point are perpendicular to x or y axis 
{
	double yDelta_a= pt2y - pt1y;
	double xDelta_a= pt2x - pt1x;
	double yDelta_b= pt3y - pt2y;
	double xDelta_b= pt3x - pt2x;
	


	// checking whether the line of the two pts are vertical
	if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
//		TRACE("The points are pependicular and parallel to x-y axis\n");
		return false;
	}

	if (fabs(yDelta_a) <= 0.0000001){
//		TRACE(" A line of two point are perpendicular to x-axis 1\n");
		return true;
	}
	else if (fabs(yDelta_b) <= 0.0000001){
//		TRACE(" A line of two point are perpendicular to x-axis 2\n");
		return true;
	}
	else if (fabs(xDelta_a)<= 0.000000001){
//		TRACE(" A line of two point are perpendicular to y-axis 1\n");
		return true;
	}
	else if (fabs(xDelta_b)<= 0.000000001){
//		TRACE(" A line of two point are perpendicular to y-axis 2\n");
		return true;
	}
	else return false ;
}

double Circle::CalcCircle(double pt1x, double pt1y,double pt2x, double pt2y, double pt3x, double pt3y)
{



double f,g,m;
double c,d,h,e,k,r,s;

double x1 = pt1x;
double y1 = pt1y;

double x2 = pt2x;
double y2 = pt2y;

double x3 = pt3x;
double y3 = pt3y;



f = x3*x3-x3*x2-x1*x3+x1*x2+y3*y3-y3*y2-y1*y3+y1*y2; //formula
g = x3*y1-x3*y2+x1*y2-x1*y3+x2*y3-x2*y1;

if(g==0)
m = 0;
else
m = (f/g);

c = (m*y2)-x2-x1-(m*y1); //formula
d = (m*x1)-y1-y2-(x2*m);
e = (x1*x2)+(y1*y2)-(m*x1*y2)+(m*x2*y1);

h = (c/2); //formula
k = (d/2);
s = (((h)*(h))+((k)*(k))-e);
r = pow(s,.5);

this->m_Center_x=h;
this->m_Center_y=k;
this->m_dRadius = r;

return this->m_dRadius;

}
/*
double Circle::CalcCircle(double pt1x, double pt1y,double pt2x, double pt2y, double pt3x, double pt3y)
{
	double yDelta_a= pt2y - pt1y;
	double xDelta_a= pt2x - pt1x;
	double yDelta_b= pt3y - pt2y;
	double xDelta_b= pt3x - pt2x;
	
	if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
//		TRACE("Calc cirlce \n");
		this->m_Center_x= 0.5*(pt2->x() + pt3->x());
		this->m_Center_y= 0.5*(pt1->y() + pt2->y());
		this->m_Center.m_z= pt1->z();
		this->m_dRadius= length(&m_Center,pt1);		// calc. radius
//		TRACE(" Center: %f %f %f\n", m_Center.x(), m_Center.y(), m_Center.z());
//		TRACE(" radius: %f %f %f\n", length(&m_Center,pt1), length(&m_Center,pt2),length(&m_Center,pt3));

		return this->m_dRadius;
	}
	
	// IsPerpendicular() assure that xDelta(s) are not zero
	double aSlope=yDelta_a/xDelta_a; // 
	double bSlope=yDelta_b/xDelta_b;
	if (fabs(aSlope-bSlope) <= 0.000000001){	// checking whether the given points are colinear. 	
		TRACE("The three pts are colinear\n");
		return -1;
	}

	// calc center
	this->m_Center.m_x= (aSlope*bSlope*(pt1->m_y - pt3->m_y) + bSlope*(pt1->m_x + pt2 ->m_x)
		- aSlope*(pt2->m_x+pt3->m_x) )/(2* (bSlope-aSlope) );
	this->m_Center.m_y = -1*(m_Center.x() - (pt1->x()+pt2->x())/2)/aSlope +  (pt1->y()+pt2->y())/2;
	this->m_Center.m_z= pt1->m_z;

	this->m_dRadius= length(&m_Center,pt1);		// calc. radius
//	TRACE(" Center: %f %f %f\n", m_Center.x(), m_Center.y(), m_Center.z());
//	TRACE(" radius: %f %f %f\n", length(&m_Center,pt1), length(&m_Center,pt2),length(&m_Center,pt3));
	return this->m_dRadius;
}
*/
/*
Point* Circle::GetCenter()
{
	return &this->m_Center;

}
*/
double Circle::GetRadius()
{
	return this->m_dRadius;
}
