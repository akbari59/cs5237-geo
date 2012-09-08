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
		LongInt();
	} else if(sourceString.at(0)=='-'){
		
		signValue=-1;
		start=1;
	} else{
		
		signValue=1;
	}
	for(unsigned i=start; i<sourceString.length(); i+=baselength){
		absolute.push_back( atoi(sourceString.substr(1, i+baselength).c_str()));
	}
	
}

LongInt LongInt::operator*(LongInt& n){
	
	LongInt i;
	if(signValue!=0&&n.signValue!=0){
		i.signValue=signValue*n.signValue;
		absMult(*this,  n,  i);
	}
	return i;
}

void LongInt::absMult(LongInt& a,  LongInt& b,  LongInt& result){
	
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
void LongInt::separate(int length1, LongInt& l1, LongInt& l2){
	
	l1.signValue=signValue;
	l2.signValue=signValue;
	for(int i=0; i<length1; i++){
		l1.absolute.push_back(absolute[i]);
	}
	for(unsigned i=length1; i<absolute.size();i++){
		l2.absolute.push_back(absolute[i]);
	}
}

void LongInt::shiftSum(LongInt& z2,LongInt& z1, LongInt& z0, int b1, int b0, LongInt& result){
	//result=z1*Base^b1+z2*Base^b0+z0
	int v0, v1, v2;
	unsigned i, carry=0;
	for(i=0; i<b0;i++){
		if(i<z0.absolute.size()){
			v0=z0.absolute[i];
		}else{
			v0=0;
		}
		result.absolute.push_back(v0);
	}
	for(; i<b1;i++){
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
		int v=v0+v1+carry;
		if(v<base){
		  carry=0;
		}else{
          carry=1;
		  v=v-base;		  
		}
		result.absolute.push_back(v);
	}
	
	while(i<z0.absolute.size()||i<(z1.absolute.size()+b0)||i<(z2.absolute.size()+b1)){
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
		int v=v0+v1+v2+carry;
		carry=v/base;

		result.absolute.push_back(v%base);
		i++;
	}
}

void LongInt::shiftSum(LongInt& z1, LongInt& z0, int b, LongInt& result){
	//result=z1*Base^b+z0
	int v0, v1;
	int i, carry=0;
	for(i=0; i<b;i++){
		if(i<z0.absolute.size()){
			v0=z0.absolute[i];
		}else{
			v0=0;
		}
		result.absolute.push_back(v0);
	}
	while(i<z0.absolute.size()||i<(z1.absolute.size()+b)){
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
		int v=v0+v1+carry;
		if(v<base){
		  carry=0;
		}else{
          carry=1;
		  v=v-base;		  
		}
		result.absolute.push_back(v);
		i++;
	}
	
	
}
void LongInt::absMult(int scaler, LongInt& v, LongInt& result){
	int carry=0;
	for(int i=0; i<v.absolute.size(); i++){
		int value=scaler*v.absolute[i]+carry;
		if(value<base){
			carry=0;
		}else{
			carry=value/base;
			value=value%base;
		}
		result.absolute.push_back(value);
	}
	
	  while(carry>0){
		   int v=carry%base;
		   carry=carry/base;
		   result.absolute.push_back(v);
	   }
	
}

bool LongInt::eqZero(){
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
LongInt& LongInt::operator=(LongInt& i){
	absolute=i.absolute;
	signValue=i.signValue;
	return *this;
}
LongInt LongInt::operator+(LongInt& n){
	if(n.signValue==0)
		return *this;
	if(signValue==0)
		return n;
	if(signValue==n.signValue){	
	    LongInt l;
	    l.signValue=n.signValue;
	    int carry=0;
	    int maxbase=base-1;
		int minsize=min(absolute.size(), n.absolute.size());
		for(int i=0; i<minsize;i++){
		
			int result=absolute[i]+n.absolute[i]+carry;
			if(result>maxbase){
				carry=1;
				result=result-100;
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

void vappend(vector<int>& source, vector<int>& target, int start, int carry, int basemax){
	for(unsigned i=start; i<source.size();i++){
		
		int result=source[i]+carry;
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
int LongInt::abscompare(vector<int>& a, vector<int>& b){
	if(a.size()>b.size()){
		return 1;
	}else if(a.size()<b.size()){
		return -1;
	}else{
		for(int i=a.size()-1; i>=0;i--){
			if(a[i]>b[i]){
		          return 1;
	        }else if(a[i]<b[i]){
		         return -1;
	        }
		}
	}
	return 0;
}
LongInt LongInt::operator-(LongInt& n){
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
void LongInt::absDiff(vector<int>& large, vector<int>& small, vector<int>& result){
	int borrow=0;
	
	for(unsigned i=0; i<small.size(); i++){
		int actual=large[i]-borrow;
		if(actual<small[i]){
			borrow=1;
			result.push_back(actual+base-small[i]);
		}else{
			borrow=0;
            result.push_back(actual-small[i]);
		}
	}
	if(large.size()>small.size()){
		for(unsigned i=small.size(); i<large.size(); i++){
			int actual=large[i]-borrow;
			if(actual<0){
			   borrow=1;
			   result.push_back(actual+base);
		    }else{
			   borrow=0;
               result.push_back(actual);
		    }
		}
	}
}

bool LongInt::operator>(LongInt& i){
	if(sign()>i.sign()){
		return true;
	}else if(sign()==i.sign()){
		
		return sign()*abscompare(absolute, i.absolute)==1;
	}else{
	   return false;
	}
}
bool LongInt::operator<(LongInt& i){
	if(sign()<i.sign()){
		return true;
	}else if(sign()==i.sign()){
		
		return sign()*abscompare(absolute, i.absolute)==-1;
	}else{
	   return false;
	}
}
bool LongInt::operator==(LongInt& i){
	if(sign()==i.sign()&&abscompare(absolute, i.absolute)==0){
		
		return true;
	}else{
		return false;
	}
}


int LongInt::sign(){
	return signValue;
};     // return +1 if it's positive, -1 if it's negative, 0 if it's zero


double LongInt::doubleValue(){
	int sum=0;

	for(int i=0, coef=1; i<absolute.size(); (i++, coef*=base)){
		sum=sum+coef*absolute[i];
	}
	return 0;
}
LongInt operator-(LongInt& n){
	LongInt out=n;
	out.signValue=-out.signValue;
	return out;
}