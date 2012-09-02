#include "li.h"
#include <list>
using namespace std;

void LongInt::setZero_(){
	LongInt::intList.clear();
}

LongInt::LongInt(){

}
LongInt::LongInt(LongInt& longInt){
	intList = longInt.intList;
}
LongInt::LongInt(int n){
	isPositive=(n>0);
	while(n!=0){
		intList.push_back(n % 10);
		n/=10;
	}
}
LongInt::LongInt(string intString){
	for(int i=0;i<intString.size();i++){
		intList.push_front(intString.at(i)-'0');
	}
}

LongInt LongInt::operator*(LongInt& longInt){
	list<int> newList = longInt.intList;

	int resultSize=intList.size()+newList.size();
	int* result;
	result=(int *)malloc(sizeof(int)*resultSize);
	for(int i=0;i<resultSize;i++){
		result[i]=0;
	}

	list<int>::iterator itr1, itr2;
	int offset=0;
	for(itr1=newList.begin();itr1!=newList.end();itr1++){
		int b=*itr1;
		int count=0;
		for(itr2=intList.begin();itr2!=intList.end();itr2++){
			int a=*itr2;
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
	}
	LongInt *resultInt = new LongInt();
	for(int i=0;i<resultSize&&result[i]!=0;i++){
		(*resultInt).intList.push_back(result[i]);
	}
	return *resultInt;
}
