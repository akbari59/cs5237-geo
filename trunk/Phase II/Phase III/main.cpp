
#define WIN32

#include "math.h"
#include <iostream>
#include <fstream>

#include <cstdio>
#include <fstream>
#include <strstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "basicsP2\pointSetArray.h"
#include "basicsP2\trist.h"
#include "Circle.h"
#include "GL\glut.h"
#include <Windows.h>

using namespace std;

const double PI = 3.1415926536;
const double sqrt3 = 1.732050808F;

// Initial size of graphics window on your screen.
const int WIDTH  = 700; // in pixels
const int HEIGHT = 700; //

// Current size of window (will change when you resize window)
int width  = WIDTH;
int height = HEIGHT;

// Bounds of viewing frustum, maintain uniform scaling.
double viewWindowLeft =  -500;
double viewWindowRight  = 500;
double viewWindowBottom =  -350;
double viewWindowTop  = 350;

// increment for  zoom
const double ZoomSTEP = 100;
const double zoomFactor = 1.03;

const double PanSTEP = 10;


bool file_loaded = false;


//these structure store all points and triangles
Trist trist;
PointSetArray psa;
PointSetArray notinsidepsa;

Trist worksetTrist;
PointSetArray worksetPsa;

int circumcir1 = -1, circumcir2 = -1, circumcir3 = -1;
OrTri tempOriTri1= -1,tempOriTri2= -1,tempOriTri3 = -1;


void drawAPoint(double x,double y, float red = 0, float green = 0, float blue = 0, float opaque = 0)
{
	
	glPointSize(5);
	glBegin(GL_POINTS);
	//glColor3f(0,0,0);
	glColor4f(red,green,blue, opaque);
	glVertex2d(x,y);
	glEnd();
	glPointSize(1);
}



void drawALine(double x1,double y1, double x2, double y2)
{
		glPointSize(1);
		glBegin(GL_LINE_LOOP);
		//glColor3f(0,0,1);
		glColor4f(0,0,1, 0.80);
			glVertex2d(x1,y1);
			glVertex2d(x2,y2);
		glEnd();
		glPointSize(1);
}

void drawATriangle(double x1,double y1, double x2, double y2, double x3, double y3, float red = 0, float green = 0.5, float blue = 0, float opaque = 0)
{
		glBegin(GL_POLYGON);
		//glColor3f(0,0.5,0);
		glColor4f(red,green,blue, opaque);
			glVertex2d(x1,y1);
			glVertex2d(x2,y2);
			glVertex2d(x3,y3);
		glEnd();

}

void glCircle3i(GLint x, GLint y, GLint radius) { 
    
	float angle; 
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0,0.5,0);
	for(int i = 0; i < 100; i++) { 
        angle = i*2*PI/100; 
        glVertex2f(x + (cos(angle) * radius), y + (sin(angle) * radius)); 
    } 

	glEnd();

   
}  

void drawCircle(double x1,double y1, double x2, double y2, double x3, double y3)
{
	Circle circ(x1,y1, x2, y2, x3, y3);
	glCircle3i(circ.m_Center_x, circ.m_Center_y, circ.m_dRadius);

	
}

void drawCircumscribeCircleForTriangle(OrTri t)
{

	if ( t == -1) return;

		int tmppi1,tmppi2, tmppi3;
		trist.getVertexIdx(t,tmppi1,tmppi2,tmppi3);
		LongInt x1,y1,x2,y2,x3,y3;
		psa.getPoint(tmppi1,x1,y1);
		psa.getPoint(tmppi2,x2,y2);
		psa.getPoint(tmppi3,x3,y3);

		drawCircle(x1.doubleValue(),y1.doubleValue(), x2.doubleValue(),y2.doubleValue(), x3.doubleValue(),y3.doubleValue());

}
void drawOriTri(OrTri t){
		
	if ( t == -1) return;

		int tmppi1,tmppi2, tmppi3;
		trist.getVertexIdx(t,tmppi1,tmppi2,tmppi3);
		LongInt x1,y1,x2,y2,x3,y3;
		psa.getPoint(tmppi1,x1,y1);
		psa.getPoint(tmppi2,x2,y2);
		psa.getPoint(tmppi3,x3,y3);
		drawATriangle(x1.doubleValue(),y1.doubleValue(), x2.doubleValue(),y2.doubleValue(), x3.doubleValue(),y3.doubleValue(), 0.5,0,0);
		//drawCircle(x1.doubleValue(),y1.doubleValue(), x2.doubleValue(),y2.doubleValue(), x3.doubleValue(),y3.doubleValue());
}
void drawTrist(){
	//contain all drawing code.
	//get data from global variables trist & psa
	/**/


	for(int i= 0; i<trist.noTri(); i++)
	{
		int pi1,pi2, pi3;
		trist.getVertexIdx(i * 8,pi1,pi2,pi3);
		LongInt x1,y1,x2,y2,x3,y3;
		psa.getPoint(pi1,x1,y1);
		psa.getPoint(pi2,x2,y2);
		psa.getPoint(pi3,x3,y3);

		drawATriangle(x1.doubleValue(),y1.doubleValue(), x2.doubleValue(),y2.doubleValue(), x3.doubleValue(),y3.doubleValue());
		
		////////////////////////////////////////////
		drawALine(x1.doubleValue(),y1.doubleValue(), x2.doubleValue(),y2.doubleValue());
		drawALine(x2.doubleValue(),y2.doubleValue(), x3.doubleValue(),y3.doubleValue());
		drawALine(x1.doubleValue(),y1.doubleValue(), x3.doubleValue(),y3.doubleValue());

//		drawCircle(x1.doubleValue(),y1.doubleValue(), x2.doubleValue(),y2.doubleValue(), x3.doubleValue(),y3.doubleValue());

		//DEBUG STUFF
		//cout<<"triangle at->"<<x1.doubleValue()<< " "<< y1.doubleValue()<< " "<< x2.doubleValue() << " " <<y2.doubleValue() << " " <<x3.doubleValue()<< " "<<y3.doubleValue()<< endl;
	}

	for(int i= 1; i<=psa.noPt(); i++)
	{
		LongInt x,y;
		psa.getPoint(i,x,y);
		double tx = x.doubleValue();
		double ty = y.doubleValue();
		drawAPoint(tx,ty, 0, 0, 0, 0.6);
		
		//just for debugging purpose
		//cout<<"point at->"<<tx<<"," <<ty<<endl;
	}

	for(int i= 1; i<=notinsidepsa.noPt(); i++)
	{
		LongInt x,y;
		notinsidepsa.getPoint(i,x,y);
		double tx = x.doubleValue();
		double ty = y.doubleValue();
		drawAPoint(tx,ty, 0.6, 0, 0, 0.7);

		//just for debugging purpose
		//cout<<"point at->"<<tx<<"," <<ty<<endl;
	}

	drawCircumscribeCircleForTriangle(circumcir1);
	drawCircumscribeCircleForTriangle(circumcir2);
	drawCircumscribeCircleForTriangle(circumcir3);

	glutSwapBuffers();
	
	drawOriTri(tempOriTri1);
	drawOriTri(tempOriTri2);
	drawOriTri(tempOriTri3);
	
	
	
}

void setView()
{

	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( viewWindowLeft, viewWindowRight, viewWindowBottom, viewWindowTop);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}


void display(void)
{

	setView();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();


	// draw your output here (erase the following 3 lines)
	drawTrist();
	//drawTristDeluany();

	glPopMatrix();
	glutSwapBuffers ();
}


void reshape (int w, int h)
{
	width = w;
	height = h;
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	
	/*glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,h,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/

}

void pan(unsigned char direction)
{
   // for zoom in reduces viewWindow size and for zoom out increases it.

	if (direction == 's') {	//move left
			viewWindowLeft -= PanSTEP; viewWindowRight -= PanSTEP;
						
		}
		else if (direction == 'd') {
			viewWindowLeft += PanSTEP; viewWindowRight += PanSTEP;
						
		}
		else if (direction == 'x') {
			viewWindowBottom -= PanSTEP; viewWindowTop -= ZoomSTEP;
			
		}
		else if (direction == 'e') {
			viewWindowBottom += PanSTEP; viewWindowTop += PanSTEP;
			
		}

}

void zoom(unsigned char direction)
{
   // for zoom in reduces viewWindow size and for zoom out increases it.

	

	if (direction == '+') {
		//if(viewWindowRight- viewWindowLeft <  3* ZoomSTEP) 	return;
			viewWindowLeft += ZoomSTEP; viewWindowRight -= ZoomSTEP;
			viewWindowBottom += ZoomSTEP; viewWindowTop -= ZoomSTEP;
			
		}
		else if (direction == '-') {
			viewWindowLeft -= ZoomSTEP; viewWindowRight += ZoomSTEP;
			viewWindowBottom -= ZoomSTEP; viewWindowTop += ZoomSTEP;
			
		}

}

void resetView()
{
	viewWindowLeft =  -500;
	viewWindowRight  = 500;
	viewWindowBottom =  -350;
	viewWindowTop  = 350;

}

/*
void zoom (double rate)
{

	
	width = width * rate;
	height = height * rate;

	 reshape (width , height );

	

}
*/

void GetOGLPos(int x, int y, int& wx, int& wy, int& wz)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
 
	wx = posX;
	wy = posY;
	wz = posZ;
    return;
}

void init(void)
{
	glClearColor (1.0,1.0,1.0, 1.0);
	glShadeModel(GL_FLAT);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//should be optimized
OrTri getCicumscribeTri(int p)
{

	OrTri result = -1;
	int intri_result;
	int isLeaf = 0;
	OrTri orindex= 0;
	int p1, p2, p3;


	for(int i=0; i<trist.noTri() ;i++)
	{
		int p1, p2, p3;
		OrTri orindex= i<<3;
		trist.getVertexIdx(orindex, p1, p2, p3);
		if(p1!=-1){
		intri_result=psa.inTri(p1, p2, p3, p);
		if (intri_result != -1) return orindex;
		}
	}

	cout<< "EROORRR";
	
	return result;

}
//should be optimized

bool CheckIsDelaunay(OrTri  t, int lastpoint, OrTri&  n)
{
		int p1, p2, p3;
		OrTri orindex= t;
		trist.getVertexIdx(orindex, p1, p2, p3);
		for(int i=1; i<=lastpoint;i++)
		{
			if ((i == p1) || (i==p2) || (i == p3)) continue;
			if ( psa.inCircle2(p1,p2,p3,i) == 1)
			{

				return false;
			}
		}
		return true;

}

bool CheckIsDelaunay2(OrTri  t)
{
	OrTri  neighborhood;
	neighborhood = trist.fnext(t);
	drawOriTri(neighborhood);
	Sleep(2000);
	return true;

}


//bool CheckIsDelaunay(OrTri  t, int p)
//{
//		int p1, p2, p3;
//		OrTri orindex= t<<3;
//		trist.getVertexIdx(orindex, p1, p2, p3);
//		if ( psa.inCircle2(p1,p2,p3,p) != 1)
//			return true;
//		return false;
//
//}

bool flipEdge(OrTri t, int p1, int p2)
{

	return false;
}

bool delaunayComputation()
{
	//if (psa.noPt() < 3) return false;	// nothing to handle

	// Determine the bounding box.
	LongInt xMin, yMin;

	int res = psa.getPoint(1, xMin, yMin);

	LongInt xMax = xMin;
	LongInt yMax = yMin;

	LongInt x;
	LongInt y;

	for(int i=1; i <= psa.noPt() ;i++)
	{
		res = psa.getPoint(i, x, y);
		if(x < xMin) xMin = x;
		if(y < yMin) yMin = y;
		
		if(x > xMax) xMax = x;
		if(y > yMax) yMax = y;
	}

	LongInt dx = xMax - xMin;
	LongInt dy = yMax - yMin;


	// Make the bounding box slightly bigger, just to feel safe.
	LongInt ddx = dx + 50;
	LongInt ddy = dy + 50;

	//LongInt temp = 2;

	//xMin = xMin - ddx;
	//xMax = xMax + ddx;
	//dx = dx + temp * ddx;

	//yMin = yMin - ddy;
	//yMax = yMax + ddy;
	//dy = dy + temp * ddy;

	//// Create a 'super triangle', encompassing all the vertices. We choose an equilateral triangle with horizontal base.
	//// We could have made the 'super triangle' simply very big. However, the algorithm is quite sensitive to
	//// rounding errors, so it's better to make the 'super triangle' just big enough, like we do here.

	//int p1 = psa.addPoint(xMin - dy * (sqrt3 / 3.0F) , yMin );
	//int p2 = psa.addPoint(xMax + dy * (sqrt3 / 3.0F) , yMin );
	//int p3 = psa.addPoint((xMin + xMax) * 0.5 , yMax + dx * sqrt3 * 0.5 );

	LongInt M;
	if(dx > dy ) M = dx; else M = dy; 
	LongInt temp = 3;
	
	int p1 = psa.addPoint(temp * M, 0);
	int p2 = psa.addPoint(0, temp * M);
	int p3 = psa.addPoint(- temp * M, -temp * M);


	trist.makeTri(p1,p2,p3);
	
	
	
//	width = xMax.doubleValue() - xMin.doubleValue();
//	height = yMax.doubleValue() - yMin.doubleValue();

	display();
	
		
	for(int i= 1; i <= psa.noPt()-3 ; i++)
	{

		//OrTri orindex = getCicumscribeTri(i);
		bool boundry;
		OrTri orindex = trist.findPoint(i,boundry,psa);;
		cout << "CicumscribeTri for point" << i <<"is  " << orindex << endl;
		
		int a, b, c;
		trist.getVertexIdx(orindex, a, b, c);

		
		OrTri t1, t2, t3; 
		trist.insertPoint(i,orindex,t1, t2, t3);
		

		circumcir1 = t1;
		circumcir2 = t2;
		circumcir3 = t3;
		
		display();
		Sleep(100);
		
			
		//MOST IMPORTANT PART
		//SHOULD IMPLEMENT AN TREEEEEEEEEEEEEEEEE

		//CheckIsDelaunay2(t1);
		tempOriTri1 = trist.fnext(t1);
		tempOriTri2 = trist.fnext(trist.enext(t1));
		tempOriTri3 = trist.fnext(trist.enext(trist.enext(t1)));
		Sleep(2000);
/*
		if(!CheckIsDelaunay(t1, c, i)  ){
			cout << "t1 is not delaunt" << endl;

					
		}
		if(!CheckIsDelaunay(t2, a, i)){
			cout << "t2 is not delaunt" << endl;
		
		}
		if(!CheckIsDelaunay(t3, b, i)){
			cout << "t3 is not delaunt" << endl;
		
		}

*/	


	}
			
	return false;

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




void readFile(){

	string line_noStr;

	string line;   // each line of the file
	string command;// the command of each line
	string numberStr; // for single LongInt operation
	string outputAns = "Answer of your computation"; // the answer you computed
	int delay=-1;
	ifstream inputFile("input.txt",ios::in);


	if(inputFile.fail()){
		cerr << "Error: Cannot read input file \"" << "input.txt" << "\"";
		return;
	}

	if(file_loaded)
	{
		//remove all points and triangles;
		psa.eraseAllPoints();
		trist.delAllTri();
	}

	

	while(inputFile.good()){

		getline(inputFile,line);
		if(line.empty()) {
			command = "";
			continue; 
		}// in case the line has nothing in it

		stringstream linestream(line);

		linestream >> line_noStr;
		linestream >> command;         // get the command

		if(!command.compare("AP")){
			linestream >> numberStr;
			LongInt x(numberStr);
			linestream >> numberStr;
		    LongInt y(numberStr);
			psa.addPoint(x,y);
			
		}
		else if(!command.compare("OT")){
			linestream >> numberStr;
			int p1=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p2=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p3=atoi(numberStr.c_str());
			trist.makeTri(p1,p2,p3);
			if(delay>0){
				Sleep(delay*1000);
				display();
			}
			//drawTrist();
		} 
		else if(!command.compare("IP")){
			linestream >> numberStr;
			LongInt x(numberStr);
			linestream >> numberStr;
			LongInt y(numberStr);
			int pIndex=psa.addPoint(x,y);
			//remember to remove the triangle from the trist;
			for(int i=0; i<trist.noTri();i++){
				int p1, p2, p3;
				OrTri orindex= i<<3;
				trist.getVertexIdx(orindex, p1, p2, p3);
				if(p1!=-1){
				 int intri_result=psa.inTri(p1, p2, p3, pIndex);
				 if(intri_result==1){
					trist.delTri(orindex);
					trist.makeTri(pIndex,p2,p3);
					trist.makeTri(p1,pIndex,p3);
					trist.makeTri(p1,p2,pIndex);
					if(delay>0){
				       Sleep(delay*1000);
				       display();
			        }
					break;
				 }
				}
				
			}

		}
		else if(!command.compare("DY")){
			linestream >> numberStr;
			delay=atoi(numberStr.c_str());
			if(delay>0)
				Sleep(delay * 1000);
		} else if (!command.compare("CD")){
			delaunayComputation();
		}
		else{
			cerr << "Exception: Wrong input command" << endl;
		}

		display();
	}

}




void writeFile()
{
	//write to  ¡°input.txt¡± get data from global variables trist & psa
	double instCount = 0; // Instruction count
	ofstream outputFile("input.txt",ios::out); // output file

	//outputFile<<instCount<<": DY 2"<<endl;
	instCount++;

	// obtain individual point data from psa and writing the AP command
	for(int i= 1; i<=psa.noPt(); i++)
	{
		LongInt x,y;
		psa.getPoint(i,x,y);
		double dx = x.doubleValue();
		double dy = y.doubleValue();
		outputFile<<std::setw(4) << std::setfill('0') << instCount << ": AP " << dx << " " << dy << endl;
		instCount++;
	}

	outputFile<<std::setw(4) << std::setfill('0') << instCount << ": CD " << endl;


	outputFile.close();
}



void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'r':
		case 'R':
			readFile();
			file_loaded = true;
		break;

		case 'w':
		case 'W':
			writeFile();
		break;

		case 'Q':
		case 'q':
			exit(0);
		break;

		case 'O':
		case 'o':
			zoom('-');
			//glutPostRedisplay();
			break;

		case 'I':
		case 'i':
			zoom('+');
			//glutPostRedisplay();
			break;

		case 'S':
		case 's':
			pan('s');
			//glutPostRedisplay();
			break;
		case 'D':
		case 'd':
			pan('d');
			//glutPostRedisplay();
			break;
		case 'E':
		case 'e':
			pan('e');
			//glutPostRedisplay();
			break;
		case 'X':
		case 'x':
			pan('x');
			//glutPostRedisplay();
			break;
		case 'N':
		case 'n':
			resetView();
			break;


		default:
		break;
	}

	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)//the point and triangles have to be inserted to the trist & psa
{
	/*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
        
	/*state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};

	if((button == MOUSE_RIGHT_BUTTON)&&(state == GLUT_UP))
	{
		int wx, wy, wz;
		GetOGLPos(x,y, wx, wy, wz);
		int pIndex=psa.addPoint(wx,wy);
		int intri_result = -1;
		bool outsidePoint = true;

	    for(int i=0; i<trist.noTri() && (intri_result == -1 );i++){
				int p1, p2, p3;
				OrTri orindex= i<<3;
				trist.getVertexIdx(orindex, p1, p2, p3);
				if(p1!=-1){
				 intri_result=psa.inTri(p1, p2, p3, pIndex);
				 switch (intri_result)
				 {
				 case 1:

					 trist.delTri(orindex);
					 trist.makeTri(pIndex,p2,p3);
					 trist.makeTri(p1,pIndex,p3);
					 trist.makeTri(p1,p2,pIndex);
					 outsidePoint = false;
					 break;
				 case 0:
					 cout << "degenerate case" << endl;
					 psa.removePoint(pIndex);
					 outsidePoint = false;
					 int pIndex2=notinsidepsa.addPoint(wx,wy);
					 break;
				 
				 }//switch
				} //if
				
			} // for
		if(outsidePoint == true)
		{
			//cout << "you have clicked outside any triangle. point was discarded." << endl;
			psa.removePoint(pIndex);
			int pIndex2=notinsidepsa.addPoint(wx,wy);
			
		}
	} //if((button == MOUSE_RIGHT_BUTTON)&&(state == GLUT_UP))

	glutPostRedisplay();
}

void generate_test_input(int num, int bound)
{
	
	//write to  ¡°input.txt¡± get data from global variables trist & psa
	double instCount = 0; // Instruction count
	ofstream outputFile("input.txt",ios::out); // output file

	
  /* initialize random seed: */
  srand ( time(NULL) );

  

  // obtain individual point data from psa and writing the AP command
	for(int i= 1; i<=num; i++)
	{
		double dx = -bound/2 + rand() % bound + 1;
		double dy = -bound/2 + rand() % bound + 1;
		outputFile<<std::setw(4) << std::setfill('0') << instCount << ": AP " << dx << " " << dy << endl;
		instCount++;
	}

	outputFile<<std::setw(4) << std::setfill('0') << instCount << ": CD " << endl;


	outputFile.close();
}


int main(int argc, char **argv)
{
	//generate_test_input(100, 400);
	//return 0;


	width = 1000; height = 800;
	cout<<"CS5237 Phase II"<< endl<< endl;
	cout << "Right mouse click: OT operation"<<endl;
	cout << "Q: Quit" <<endl;
	cout << "R: Read in control points from \"input.txt\"" <<endl;
	cout << "W: Write control points to \"input.txt\"" <<endl;
	cout << "Zoom Functions: I: Zoom in, O: Zoom Out" <<endl;
	cout << "E,S,D,X: Scroll Up, Left, Right, Down, Respectively." <<endl;
	cout << "N: Reset the view to the original position if you lost the direction." <<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (width, height);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS5237 Phase II");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
