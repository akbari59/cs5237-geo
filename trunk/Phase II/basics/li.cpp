#include "li.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void LongInt::setZero_(){
	
	LongInt::absolute.clear();
	signValue=0;
}

LongInt::LongInt(){
	
	signValue=0;

}

LongInt::LongInt(int n){
	convert(n);
}
void LongInt::convert(int n){
	if(n==0){
		signValue=0;
	} else {
		if(n>0){
			signValue=1;
		} else{
			signValue=-1;
			n=abs(n);
		}
		
		int r;
		while(n!=0){
          r=n%base;
		  n=n/base;		  
		  LongInt::absolute.push_back(r);
		}
	}
}
LongInt::LongInt(string sourceString){
	unsigned start=0;
	if(sourceString.at(0)=='0'){
		signValue=0;
		return;
	} else if(sourceString.at(0)=='-'){
		
		signValue=-1;
		sourceString=sourceString.substr(1, sourceString.length());
		start=1;
	} else{
		
		signValue=1;
	}
	
	
	while(sourceString.length()>=baselength){
		absolute.push_back( atoi(sourceString.substr(sourceString.length()-baselength, baselength).c_str()));
		sourceString=sourceString.substr(0, sourceString.length()-baselength);
	}
	if(!sourceString.empty())
		absolute.push_back( atoi(sourceString.c_str()));
}

LongInt LongInt::operator*(const LongInt& n) const{
	
	LongInt i;
	if(signValue!=0&&n.signValue!=0){
		i.signValue=signValue*n.signValue;
		absMult(*this,  n,  i);
	}
	return i;
}

void absMult(const LongInt& a,  const LongInt& b,  LongInt& result){
	
	if(a.absolute.size()==1){
		absMult(a.absolute.front(), b, result);
	}else if(b.absolute.size()==1){
		absMult(b.absolute.front(), a, result);
	}else{
		if(a.absolute.size()>b.absolute.size()){
			LongInt l1, l2;
			a.separate(b.absolute.size(), l1, l2);
			shiftSum(l2*b, l1*b, b.size(), result);			
		}else if(a.size()<b.size()){
			LongInt l1, l2;
			b.separate(a.absolute.size(), l1, l2);
			shiftSum(l2*a, l1*a, a.size(), result);			
		}else{
			/*x = x1Bm + x0
              y = y1Bm + y0,
              xy = (x1Bm + x0)(y1Bm + y0)= z2B2m + z1Bm + z0
			  z2 = x1y1
              z1 =(x1 + x0)(y1 + y0) - z2 - z0
              z0 = x0y0.
			 */
			int bm=a.size()/2;
			LongInt x1, x0, y1, y0,z2,z1,z0;
			a.separate(bm, x0, x1);
			b.separate(bm, y0, y1);
			z0=x0*y0;
			z2=x1*y1;
			z1=(x1+x0)*(y1+y0)-z2-z0;
			shiftSum(z2, z1, z0, 2*bm, bm, result);
		}
		
	}
}
void LongInt::separate(unsigned length1, LongInt& l1, LongInt& l2) const{
	l2.signValue=signValue;
	for(unsigned i=length1; i<absolute.size();i++){
		l2.absolute.push_back(absolute[i]);
	}
	
	while(length1>0&&absolute[length1-1]==0){
		length1--;
	}
	if(length1==0){
		if(absolute[length1]>0)
			l1.absolute.push_back(absolute[length1]);
	}else{
   
	  for(unsigned i=0; i<length1; i++){
		l1.absolute.push_back(absolute[i]);
	  }
	}
	if(l1.size()==0)
		l1.signValue=0;
	else
		l1.signValue=signValue;
	
}

void shiftSum(const LongInt& z2, const LongInt& z1, const LongInt& z0, unsigned b1, unsigned b0, LongInt& result){
	//result=z1*Base^b1+z2*Base^b0+z0
	_int64 v0, v1, v2;
	unsigned i; 
	_int64 carry=0;
	for(i=0; i<b0;i++){
		if(i<z0.size()){
			v0=z0.absolute[i];
		}else{
			v0=0;
		}
		result.absolute.push_back(v0);
	}
	for(; i<b1;i++){
		if(i<z0.size()){
			v0=z0.absolute[i];
		}else{
			v0=0;
		}
		if(i<z1.absolute.size()+b0){
			v1=z1.absolute[i-b0];
		}else{
			v1=0;
		}
		_int64 v=v0+v1+carry;
		if(v<LongInt::base){
		  carry=0;
		}else{
          carry=1;
		  v=v-LongInt::base;		  
		}
		result.absolute.push_back(v);
	}
	
	while(i<z0.size()||i<(z1.size()+b0)||i<(z2.size()+b1)){
		if(i<z0.absolute.size()){
			v0=z0.absolute[i];
		}else{
			v0=0;
		}
		if(i<z1.absolute.size()+b0){
			v1=z1.absolute[i-b0];
		}else{
			v1=0;
		}
		if(i<z2.absolute.size()+b1){
			v2=z2.absolute[i-b1];
		}else{
			v2=0;
		}
		_int64 v=v0+v1+v2+carry;
		if(v<LongInt::base){
			carry=0;
			result.absolute.push_back(v);
		}else{
		    carry=v/LongInt::base;
		    result.absolute.push_back(v%LongInt::base);
		}
		i++;
	}
	if(carry>0)
		result.absolute.push_back(carry);
}

void shiftSum(const LongInt& z1, const LongInt& z0, unsigned b, LongInt& result){
	//result=z1*Base^b+z0
	__int64 v0, v1;
	unsigned i; 
	__int64 carry=0;
	for(i=0; i<b;i++){
		if(i<z0.size()){
			v0=z0.absolute[i];
		}else{
			v0=0;
		}
		result.absolute.push_back(v0);
	}
	while(i<z0.size()||i<(z1.size()+b)){
		if(i<z0.absolute.size()){
			v0=z0.absolute[i];
		}else{
			v0=0;
		}
		if(i<z1.absolute.size()+b){
			v1=z1.absolute[i-b];
		}else{
			v1=0;
		}
		_int64 v=v0+v1+carry;
		if(v<LongInt::base){
		  carry=0;
		}else{
          carry=1;
		  v=v-LongInt::base;		  
		}
		result.absolute.push_back(v);
		i++;
	}
	if(carry>0)
	result.absolute.push_back(carry);
}
void absMult(__int64 scaler, const LongInt& v, LongInt& result){
	__int64 carry=0;
	for(unsigned i=0; i<v.absolute.size(); i++){
		_int64 value=scaler*v.absolute[i]+carry;
		if(value<LongInt::base){
			carry=0;
		}else{
			carry=value/LongInt::base;
			value=value%LongInt::base;
		}
		result.absolute.push_back(value);
	}
	
	  while(carry>0){
		   _int64 v=carry%LongInt::base;
		   carry=carry/LongInt::base;
		   result.absolute.push_back(v);
	   }
	
}

bool LongInt::eqZero() const{
	return signValue==0;
}

void LongInt::dump(){
	if(signValue==0)
		cout<<0;
	else{
		if(signValue==-1)
			cout<<'-';
		cout<<absolute.back();
	    for(int i=absolute.size()-2;i>=0;i--)
	   
	      cout<<std::setw(baselength)<<setfill('0')<<absolute[i];
	   
        
	}
	cout<<endl;
}

LongInt& LongInt::operator=(int i ){
	absolute.clear();
	convert(i);
	return *this;
}
LongInt& LongInt::operator=(const LongInt& i){
	absolute=i.absolute;
	signValue=i.signValue;
	return *this;
}
LongInt LongInt::operator+(const LongInt& n) const{
	if(n.signValue==0)
		return *this;
	if(signValue==0)
		return n;
	if(signValue==n.signValue){	
	    LongInt l;
	    l.signValue=n.signValue;
	    _int64 carry=0;
	    _int64 maxbase=base-1;
		int minsize=min(absolute.size(), n.absolute.size());
		for(int i=0; i<minsize;i++){
		
			_int64 result=absolute[i]+n.absolute[i]+carry;
			if(result>maxbase){
				carry=1;
				result=result-base;
			}else{
				carry=0;
			}
			l.absolute.push_back(result);
		}
		if(absolute.size()>n.absolute.size()){
			vappend(absolute,  l.absolute, n.absolute.size(), carry, maxbase);
		}else if(n.absolute.size()>absolute.size()){
			vappend(n.absolute,  l.absolute, absolute.size(), carry, maxbase);
		}else if(carry==1){
			l.absolute.push_back(carry);
		}	  
		return l;
	}else{		
		return *this-(-n);
	}
}

void vappend(const vector<_int64>& source, vector<_int64>& target, unsigned start, _int64 carry, _int64 basemax){
	for(unsigned i=start; i<source.size();i++){
		
		_int64 result=source[i]+carry;
		if(result>basemax){
			carry=1;
			result=0;
		}else{
			carry=0;
		}
		target.push_back(result);
	}
	if(carry==1)
	  target.push_back(carry);
}
int abscompare(const vector<_int64>& a, const vector<_int64>& b){
	if(a.size()>b.size()){
		return 1;
	}else if(a.size()<b.size()){
		return -1;
	}else{
		unsigned size=a.size();
		for(unsigned i=1; i<=size;i++){
			unsigned index=size-i;
			if(a[index]>b[index]){
		          return 1;
	        }else if(a[index]<b[index]){
		         return -1;
	        }
		}
	}
	return 0;
}

LongInt LongInt::operator-(const LongInt& n) const{
	if(n.signValue==0)
		return *this;
	if(signValue==0)
		return -n;
	if(n.signValue==signValue){
	   int detersign=abscompare(this->absolute, n.absolute);
	   LongInt out;
	   switch(detersign){
	       case 0:
		       break;
		   case 1:
			   absDiff(absolute, n.absolute, out.absolute);
			   //absDiff();
			   out.signValue=signValue;
			   break;
		   case -1:
			   //absDiff();
			   absDiff( n.absolute, absolute, out.absolute);
			   out.signValue=-signValue;
			   break;
	   }
	   return out;
	}else{
		return *this+(-n);
	}
	
}
void absDiff(const vector<_int64>& large, const vector<_int64>& small, vector<_int64>& result){
	_int64 borrow=0;
	
	for(unsigned i=0; i<small.size(); i++){
		_int64 actual=large[i]-borrow;
		if(actual<small[i]){
			borrow=1;
			result.push_back(actual+LongInt::base-small[i]);
		}else{
			borrow=0;
            result.push_back(actual-small[i]);
		}
	}
	if(large.size()>small.size()){
		for(unsigned i=small.size(); i<large.size(); i++){
			_int64 actual=large[i]-borrow;
			if(actual<0){
			   borrow=1;
			   result.push_back(actual+LongInt::base);
		    }else{
			   borrow=0;
               result.push_back(actual);
		    }
		}
	}
	while(result.back()==0)
		result.pop_back();
}

bool LongInt::operator>(const LongInt& i) const{
	if(sign()>i.sign()){
		return true;
	}else if(sign()==i.sign()){
		
		return sign()*abscompare(absolute, i.absolute)==1;
	}else{
	   return false;
	}
}
bool LongInt::operator<(const LongInt& i) const{
	if(sign()<i.sign()){
		return true;
	}else if(sign()==i.sign()){
		
		return sign()*abscompare(absolute, i.absolute)==-1;
	}else{
	   return false;
	}
}
bool LongInt::operator==(const LongInt& i) const{
	if(sign()==i.sign()&&abscompare(absolute, i.absolute)==0){
		
		return true;
	}else{
		return false;
	}
}


int LongInt::sign() const{
	return signValue;
};     // return +1 if it's positive, -1 if it's negative, 0 if it's zero

void LongInt::negateSign(){
	signValue=-signValue;
}
double LongInt::doubleValue(){
	if(signValue==0){
		return 0;
	}else{
	double sum=0;

	  for(unsigned i=0, coef=1; i<absolute.size(); (i++, coef*=base)){
		 sum+=coef*absolute[i];
	  }
	  return signValue*sum;
	}
}
LongInt operator-(const LongInt& n){
	LongInt out=n;
	out.signValue=-out.signValue;
	return out;
}

ostream& operator<< (ostream& out, LongInt n ){
	if(n.sign()==0)
		out<<0;
	else{
		if(n.sign()==-1)
			out<<'-';
		out<<n.absolute.back();
		if(n.size()>1){
			unsigned end=n.size()-1;
	        for(unsigned i=1;i<=end;i++)
	   
	           out<<std::setw(LongInt::baselength)<<setfill('0')<<n.absolute[end-i];
		    }
        
	}
	return out;
}