#pragma once
#ifndef LIH
#define LIH
#include<vector>
using namespace std;
class LongInt {

	protected:
		void setZero_(); // set this number to be zero
        
		
	public:
		vector<_int64> absolute;
		int signValue;
		static _int64 const base=1000000000;
		static int const baselength=9;
		
		void negateSign();
		LongInt();
		unsigned size() const {return absolute.size();};
		LongInt(int);      // take in an integer 
		LongInt(string);
		void dump();       // print out this number
		void LongInt::convert(int i);
		void LongInt::separate(unsigned length1, LongInt& l1, LongInt& l2) const;
		LongInt& operator=(int); 
		LongInt& operator=(const LongInt&);  
		LongInt operator+(const LongInt&) const; 
		LongInt operator+(int i) const {return (*this) + LongInt(i);};
		LongInt operator-(const LongInt& ) const ;
		LongInt operator-(int i)  const {return (*this) + LongInt(i);};
		LongInt operator*(const LongInt&) const;
		LongInt operator*(int i) const {return (*this) * LongInt(i);};
		
		bool operator>(const LongInt&) const;
		bool operator<(const LongInt&) const;
		bool operator==(const LongInt&) const;

		bool eqZero() const;  // return true if it is zero
		int sign() const;     // return +1 if it's positive, -1 if it's negative, 0 if it's zero


		double doubleValue(); // return a double approximation (you can assume that it will not be out of bound)

	friend LongInt operator-(const LongInt&); 
};

void shiftSum(const LongInt& z2, const LongInt& z1, const LongInt& z0, unsigned b1, unsigned b0, LongInt& result);
void shiftSum(const LongInt& z1, const LongInt& z0, unsigned b, LongInt& result);
int abscompare(const vector<_int64>& a, const vector<_int64>& b); //1: a>b; 0: a==b; -1: a<b
void absDiff(const vector<_int64>& larger, const vector<_int64>& small, vector<_int64>& target);
void absMult(const LongInt& a,  const LongInt& b,  LongInt& result);
void absMult(_int64 a, const LongInt& b, LongInt& result);
LongInt operator-(const LongInt&); // negative sign
void vappend(const vector<_int64>& source, vector<_int64>& target, unsigned start, _int64 carry, _int64 basemax);
ostream& operator<< (ostream& out, LongInt i );

#endif