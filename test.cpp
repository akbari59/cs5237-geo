/*

	For this file, it should be sufficient to modify the function "processFile()" only.

	*/


#include <iostream>
#include <cstdio>
#include <fstream>
#include <strstream>
#include <sstream>



#include "li.h"
#include "lmath.h"
#include "pointSet.h"
#include "stopWatch.h"
using namespace std;
static StopWatch globalSW;
static string groupName = "(Your one-line group name here)";

void processFile(char* ifilename, char* ofilename){

	string line_noStr;

	string line;   // each line of the file
	string command;// the command of each line
	string numberStr; // for single LongInt operation
	string outputAns = "Answer of your computation"; // the answer you computed

	ifstream inputFile(ifilename,ios::in);
	ofstream outputFile(ofilename,ios::out);
	LongInt x;
	PointSet ps;
	if(inputFile.fail()){
		cerr << "Error: Cannot read input file \"" << ifilename << "\"";
		exit(1);
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

		if(!command.compare("LX")){
			linestream >> numberStr;
			x=LongInt(numberStr);
			globalSW.pause();
			outputFile << line_noStr  << " " << x << endl;
			globalSW.resume();
		}
		else if(!command.compare("AD")){
			linestream >> numberStr;
			LongInt temp(numberStr);
			x=x+temp;
			
			globalSW.pause();
			outputFile << line_noStr  << " " << x << endl;
			globalSW.resume();
		}
		else if(!command.compare("SB")){
			linestream >> numberStr;
			LongInt temp(numberStr);
			x=x-temp;
			globalSW.pause();
			outputFile << line_noStr  << " " << x << endl;
			globalSW.resume();
		}
		else if(!command.compare("MU")){
			linestream >> numberStr;
			LongInt temp(numberStr);
			x=x*temp;
			globalSW.pause();
			outputFile << line_noStr  << " " << x << endl;
			globalSW.resume();
		}
		else if(!command.compare("NG")){
			linestream >> numberStr;
			x=-x;
			globalSW.pause();
			outputFile << line_noStr  << " " << x << endl;
			globalSW.resume();
		}
		else if(!command.compare("SD")){
			// you can assume that the three rows of matrix are in three seperate lines in the file
			linestream >> numberStr;
			getline(inputFile,line);
			//line1
			stringstream row1(line);
			row1>>numberStr;
			LongInt x00(numberStr);
			row1>>numberStr;
			LongInt x01(numberStr);
			row1>>numberStr;
			LongInt x02(numberStr);
			//line2
			getline(inputFile,line);
			stringstream row2(line);
			row2>>numberStr;
			LongInt x10(numberStr);
			row2>>numberStr;
			LongInt x11(numberStr);
			row2>>numberStr;
			LongInt x12(numberStr);
			//line3
			getline(inputFile,line);
			stringstream row3(line);
			row3>>numberStr;
			LongInt x20(numberStr);
			row3>>numberStr;
			LongInt x21(numberStr);
			row3>>numberStr;
			LongInt x22(numberStr);
			int r=signDet(x00,x01,x02,x10,x11,x12,x20,x21,x22);
			globalSW.pause();
			outputFile << line_noStr  << " " << r << endl;
			globalSW.resume();
		}
		else if(!command.compare("AP")){
			linestream >> numberStr;
			LongInt x(numberStr);
			linestream >> numberStr;
			LongInt y(numberStr);
			int r=ps.addPoint(x,y);
			globalSW.pause();
			outputFile << line_noStr  << " " << r << endl;
			globalSW.resume();
		}
		else if(!command.compare("IT")){
			linestream >> numberStr;
			int p=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p1=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p2=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p3=atoi(numberStr.c_str());
			int r=ps.inTri(p1, p2, p3, p);
			globalSW.pause();
			outputFile << line_noStr  << " " << r << endl;
			globalSW.resume();
		}
		else if(!command.compare("IC")){
			linestream >> numberStr;
			int p=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p1=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p2=atoi(numberStr.c_str());
			linestream >> numberStr;
			int p3=atoi(numberStr.c_str());
			int r=ps.inCircle(p1, p2, p3, p);

			globalSW.pause();
			outputFile << line_noStr  << " " << r << endl;
			globalSW.resume();
		}
		else{
			cerr << "Exception: Wrong input command" << endl;
		}
	}

}

void runningExperiment()
{
	globalSW.reset();
	globalSW.resume();
	processFile("input20.txt", "output20.txt");
	globalSW.pause();
}

int main()
{
    SYSTEMTIME st;
	const int no_exp = 5;
	ULONGLONG t[no_exp];
	ULONGLONG total_t = 0;
    
    GetLocalTime(&st);
	int start = (((st.wHour*60+st.wMinute)*60)+st.wSecond)*1000+st.wMilliseconds;

	cerr << groupName <<endl;
	cerr << "Start Time:  " << st.wHour << ":" << st.wMinute << ":" << st.wSecond + (st.wMilliseconds/1000.0) << endl;

	for(int i=0;i<no_exp;i++)
	{
		runningExperiment();
		t[i] = globalSW.ms();
		total_t += t[i];
	}

    GetLocalTime(&st);
	int end = (((st.wHour*60+st.wMinute)*60)+st.wSecond)*1000+st.wMilliseconds;
	cerr << "Ending Time: " << st.wHour << ":" << st.wMinute << ":" << st.wSecond + (st.wMilliseconds/1000.0) << endl;
	cerr << "Overall Length in millisecond(including file output): " << end-start << endl;
	cerr << "Excluding file output time:"<< endl;
		cerr << "         Total Stopwatch Length(ms): " << total_t << endl;

	for(int i=0;i<no_exp;i++)
		cerr << "         Stopwatch" << (i+1) << "Length(ms): " << t[i] << endl;
	cerr << "         Average Stopwatch Length(ms): " << total_t/no_exp << endl;
   
	system("pause");
	return 0;
}
