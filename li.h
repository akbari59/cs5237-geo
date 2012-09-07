#ifndef LIH
#define LIH

#include<string>
using namespace std;
class LongInt {

private:
//public:
//	bool	isZero;			//Show that the number is Zero or Not   //@@CAN BE REMOVED
	int		intSignValue;	// Show the Sign of Number -1,0,+1

	public:
		string intString;
		int size;
		
	protected:
		void setZero_(); // set this number to be zero

public:
	void setSignValue(int sgn);

	public:
		LongInt();
		LongInt(LongInt&); // copy constructor
		LongInt(int);      // take in an integer 
		void dump();       // print out this number

		LongInt& operator=(int); 
		LongInt& operator=(LongInt&);  
		LongInt operator+(LongInt&); 
		LongInt operator+(int i) {return (*this) + LongInt(i);};
		LongInt operator-(LongInt&);
		LongInt operator-(int i) {return (*this) + LongInt(i);};
		LongInt operator*(LongInt&);
		LongInt operator*(int i) {return (*this) * LongInt(i);};
		
		bool operator>(LongInt&);
		bool operator<(LongInt&);
		bool operator==(LongInt&);

		bool eqZero();  // return true if it is zero
		int sign();     // return +1 if it's positive, -1 if it's negative, 0 if it's zero


		double doubleValue(); // return a double approximation (you can assume that it will not be out of bound)

	friend LongInt operator-(LongInt&); 
};

LongInt operator-(LongInt&); // negative sign


#endif