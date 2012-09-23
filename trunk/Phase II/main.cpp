
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
#include "GL\glut.h"
using namespace std;


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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();


	// draw your output here (erase the following 3 lines)
	drawTrist();

	glPopMatrix();
	glutSwapBuffers ();
}

void reshape (int w, int h)
{

	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,h,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


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
	ifstream inputFile("input.txt",ios::in);


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
				Sleep(delay*1000);*/
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
		}
		else{
			cerr << "Exception: Wrong input command" << endl;
		}
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
		int pIndex=psa.addPoint(x,y);
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
	cout<<"CS5237 Phase II"<< endl<< endl;
	cout << "Right mouse click: OT operation"<<endl;
	cout << "Q: Quit" <<endl;
	cout << "R: Read in control points from \"input.txt\"" <<endl;
	cout << "W: Write control points to \"input.txt\"" <<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1000, 700);
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
