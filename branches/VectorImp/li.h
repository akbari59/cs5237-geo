#ifndef LIH
#define LIH
#include<vector>
using namespace std;
class LongInt {

	protected:
		void setZero_(); // set this number to be zero
        int abscompare(vector<int>& a, vector<int>& b); //1: a>b; 0: a==b; -1: a<b
		void absDiff(vector<int>& larger, vector<int>& small, vector<int>& target);
		void absMult(LongInt& a,  LongInt& b,  LongInt& result);
		void absMult(int a, LongInt& b, LongInt& result);
		
	public:
		vector<int> absolute;
		int signValue;
		static int const base=10000;
		static int const baselength=4;
		
		void LongInt::shiftSum(LongInt& z2,LongInt& z1, LongInt& z0, int b1, int b0, LongInt& result);//result=z1*Base^b1+z2*Base^b0+z0
		void LongInt::shiftSum(LongInt& z1, LongInt& z0, int b, LongInt& result); //result=z1*Base^b+z0
		LongInt();
		int size(){return absolute.size();};
		LongInt(int);      // take in an integer 
		LongInt(string);
		void dump();       // print out this number
		void LongInt::convert(int i);
		void LongInt::separate(int length1, LongInt& l1, LongInt& l2);
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
void vappend(vector<int>& source, vector<int>& target, int start, int carry, int basemax);


#endif