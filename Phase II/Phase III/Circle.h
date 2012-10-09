
#ifndef CIRCLEH
#define CIRCLEH

class Circle  
{
public:
	double GetRadius();
//	Point* GetCenter();
	Circle(double pt1x, double pt1y,double pt2x, double pt2y, double pt3x, double pt3y );	// p1, p2, p3 are co-planar
	Circle();
	virtual ~Circle();

private:
public:
	double CalcCircle(double pt1x, double pt1y,double pt2x, double pt2y, double pt3x, double pt3y);
	bool IsPerpendicular(double pt1x, double pt1y,double pt2x, double pt2y, double pt3x, double pt3y);
	double m_dRadius;
	double m_Center_x;
	double m_Center_y;
};

#endif // !defined(AFX_CIRCLE_H__1EC15131_4038_11D3_8404_00C04FCC7989__INCLUDED_)
