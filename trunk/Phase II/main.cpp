
#define WIN32

#include "math.h"
#include <iostream>
#include <fstream>


#include <cstdio>
#include <fstream>
#include <strstream>
#include <string>
#include <sstream>

#include "basicsP2\pointSetArray.h"
#include "basicsP2\trist.h"
#include "glut.h"
#include <Windows.h>

using namespace std;

// Initial size of graphics window on your screen.
const int WIDTH  = 600; // in pixels
const int HEIGHT = 600; //

// Current size of window (will change when you resize window)
int width  = WIDTH;
int height = HEIGHT;

// Bounds of viewing frustum, maintain uniform scaling.
double viewWindowLeft =  -300;
double viewWindowRight  = 300;
double viewWindowBottom =  -300;
double viewWindowTop  = 300;

// increment for  zoom
const double ZoomSTEP = 5;
const double zoomFactor = 1.03;

const double PanSTEP = 5;




// These three functions are for those who are not familiar with OpenGL, you can change these or even completely ignore them
	Trist trist;
	PointSetArray psa;
void drawAPoint(double x,double y)
{
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0,0,0);
			glVertex2d(x,y);
		glEnd();
		glPointSize(1);
}

void drawALine(double x1,double y1, double x2, double y2)
{
		glPointSize(1);
		glBegin(GL_LINE_LOOP);
		glColor3f(0,0,1);
			glVertex2d(x1,y1);
			glVertex2d(x2,y2);
		glEnd();
		glPointSize(1);
}

void drawATriangle(double x1,double y1, double x2, double y2, double x3, double y3)
{
		glBegin(GL_POLYGON);
		glColor3f(0,0.5,0);
			glVertex2d(x1,y1);
			glVertex2d(x2,y2);
			glVertex2d(x3,y3);
		glEnd();

}

void drawTrist(){
	//contain all drawing code.
	//get data from global variables trist & psa
	/**/
	for(int i= 1; i<=psa.noPt(); i++)
	{
		LongInt x,y;
		psa.getPoint(i,x,y);
		double tx = x.doubleValue();
		double ty = y.doubleValue();
		drawAPoint(tx,ty);
		cout<<"point at->"<<tx<<"," <<ty<<endl;
	}
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

		
		cout<<"triangle at->"<<x1.doubleValue()<< " "<< y1.doubleValue()<< " "<< x2.doubleValue() << " " <<y2.doubleValue() << " " <<x3.doubleValue()<< " "<<y3.doubleValue()<< endl;
	}

	
	
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
			viewWindowLeft += ZoomSTEP; viewWindowRight -= ZoomSTEP;
			viewWindowBottom += ZoomSTEP; viewWindowTop -= ZoomSTEP;
			
		}
		else if (direction == '-') {
			viewWindowLeft -= ZoomSTEP; viewWindowRight += ZoomSTEP;
			viewWindowBottom -= ZoomSTEP; viewWindowTop += ZoomSTEP;
			
		}

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
}



void readFile(){

	string line_noStr;

	string line;   // each line of the file
	string command;// the command of each line
	string numberStr; // for single LongInt operation
	string outputAns = "Answer of your computation"; // the answer you computed
	int delay=-1;
	ifstream inputFile("input2.txt",ios::in);


	if(inputFile.fail()){
		cerr << "Error: Cannot read input file \"" << "input.txt" << "\"";
		return;
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
			/*if(delay>0)
				d(delay*1000);*/
			trist.makeTri(p1,p2,p3);
			//drawTrist();
		} 
		else if(!command.compare("IP")){
			linestream >> numberStr;
			LongInt x(numberStr);
			linestream >> numberStr;
			LongInt y(numberStr);
			int pIndex=psa.addPoint(x,y);
			//remember to remove the triangle from the trist;
			/*if(delay>0)
				Sleep(delay*1000);*/
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

}



void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'r':
		case 'R':
			readFile();
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
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//zoom(2);
			zoom('-');
			glutPostRedisplay();
			break;

		case 'I':
		case 'i':
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			zoom('+');
			//zoom(0.5);
			glutPostRedisplay();
			break;

		case 'S':
		case 's':
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			pan('s');
			//zoom(0.5);
			glutPostRedisplay();
			break;
		case 'D':
		case 'd':
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			pan('d');
			//zoom(0.5);
			glutPostRedisplay();
			break;
		case 'E':
		case 'e':
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			pan('e');
			//zoom(0.5);
			glutPostRedisplay();
			break;
		case 'X':
		case 'x':
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			pan('x');
			//zoom(0.5);
			glutPostRedisplay();
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
					break;
				 }
				}
				
			}
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	width = 1000; height = 800;
	cout<<"CS5237 Phase II"<< endl<< endl;
	cout << "Right mouse click: OT operation"<<endl;
	cout << "Q: Quit" <<endl;
	cout << "R: Read in control points from \"input.txt\"" <<endl;
	cout << "W: Write control points to \"input.txt\"" <<endl;
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
