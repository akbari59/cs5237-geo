#ifndef LIH
#define LIH
#include<vector>
using namespace std;
class LongInt {

	protected:
		void setZero_(); // set this number to be zero
        int abscompare(vector<_int64>& a, vector<_int64>& b); //1: a>b; 0: a==b; -1: a<b
		void absDiff(vector<_int64>& larger, vector<_int64>& small, vector<_int64>& target);
		void absMult(LongInt& a,  LongInt& b,  LongInt& result);
		void absMult(_int64 a, LongInt& b, LongInt& result);
		
	public:
		vector<_int64> absolute;
		int signValue;
		static _int64 const base=1000000000;
		static int const baselength=9;
		
		void LongInt::shiftSum(LongInt& z2,LongInt& z1, LongInt& z0, unsigned b1, unsigned b0, LongInt& result);//result=z1*Base^b1+z2*Base^b0+z0
		void LongInt::shiftSum(LongInt& z1, LongInt& z0, unsigned b, LongInt& result); //result=z1*Base^b+z0
		LongInt();
		unsigned size(){return absolute.size();};
		LongInt(int);      // take in an integer 
		LongInt(string);
		void dump();       // print out this number
		void LongInt::convert(int i);
		void LongInt::separate(unsigned length1, LongInt& l1, LongInt& l2);
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
void vappend(vector<_int64>& source, vector<_int64>& target, unsigned start, _int64 carry, _int64 basemax);
ostream& operator<< (ostream& out, LongInt i );

#endif