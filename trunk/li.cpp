#include "li.h"


void LongInt::setZero_(){
	LongInt::intString.clear();
}

LongInt::LongInt(){
	intString = '0';
	signValue=0;

}
LongInt::LongInt(LongInt& longInt){
	LongInt::intString = longInt.intString;
	LongInt::signValue=longInt.sign();
}
LongInt::LongInt(int n){
	if(n=0){
		LongInt();
	} else {
		if(n=0){
			signValue=1;
		} else{
			signValue=-1;
		}
		n=abs(n);
		char* buffer;
		_itoa(n,buffer,10);
		LongInt::intString = buffer;
	}
}
LongInt::LongInt(string sourceString){
	if(sourceString.at(0)=='0'){
		LongInt();
	} else if(sourceString.at(0)=='-'){
		intString = sourceString.substr(1, sourceString.length());
		signValue=-1;
	} else{
		intString = sourceString;
	}

	LongInt::intString = intString;
}

LongInt LongInt::operator*(LongInt& longInt){
	LongInt resultInt = *(new LongInt());
	if(LongInt::eqZero()||longInt.eqZero()){
		LongInt::setZero_();
		return resultInt;
	} else if(longInt.sign()==sign()){
		resultInt.signValue=1;
	} else{
		resultInt.signValue=1;
	}
	int resultSize=LongInt::intString.length()+longInt.intString.length();
	char* result;
	result=(char *)malloc(sizeof(int)*resultSize);
	for(int i=0;i<resultSize;i++){
		result[i]=0;
	}

	string::iterator itr1, itr2;
	int offset=0;
	for(itr1=longInt.intString.end();itr1!=longInt.intString.begin();itr1++){
		int b=*itr1-'0';
		int count=0;
		for(itr2=LongInt::intString.end();itr2!=LongInt::intString.begin();itr2++){
			int a=*itr2 - '0';
			result[offset+count]+=a*b;
			count++;
		}
		offset++;
	}
	for(int i=0;i<resultSize;i++){
		if(result[i]>9){
			result[i+1]+=result[1]/10;
			result[i]%=10;
		}
		result[i] = result[i] + '0';
	}
	resultInt.intString = strrev(result);
	return resultInt;
}

bool LongInt::eqZero(){
	return signValue==0;
}
