#include "li.h"

#include <iostream>
#include <string>

LongInt::LongInt() {
	//isZero = true;
	intSignValue = 0;
	intString = "0";
	size = 1;

}


LongInt::LongInt(LongInt& i) {
	//isZero = i.eqZero();
	intSignValue = i.intSignValue;
	intString = i.intString;
	size = i.size;
	
}


LongInt::LongInt(int i) {
	if(i == 0) {
		intSignValue = 0;
		intString = "0";
	}
	else {
		if(i<0) {
			intSignValue  = -1;
			i = i*-1;
		}
		else {
			intSignValue  = 1;
		}

		char buffer[64];
		_itoa(i,buffer,10);
		
		size = strlen(buffer);
		intString = buffer;
		
		
}

}

// '+' operator
LongInt LongInt::operator+(LongInt& longInt){	
	//longInt.intString -> parameter
	//LongInt::intString -> current num

	LongInt resultInt = *(new LongInt());
	char* num1 = LongInt::intString;
	char* num2 = longInt.intString;
	char* answer = new char[40];
	int len1 = strlen(num1) - 1, len2 = strlen(num2) - 1, carry = 0, result;
	
	if(LongInt.sign() == 1 && longInt.sign() == -1){
		LongInt temp = *(new LongInt)
		temp = longint;
		temp.signValue = 1;
		return (this - temp);
	}
	if(LongInt.sign() == -1 && longInt.sign() == 1){
		LongInt temp = *(new LongInt)
		temp = this;
		temp.signValue = 1;
		return (longInt - temp);
	}

	while(len1>=0 && len2>=0)
	{
		result = (int)(num1[len1] - '0') + (int)(num2[len2] - '0') + carry;
		if(result > 9){
			carry = result/10;
			result = result%10;
		}
		else{
			carry = 0;
		}
		//Constructing the answer string back
		answer = strcat(answer,(char*)(result + '0'));

		len1--;
		len2--;
	}
	while(len1>=0)
	{
		result = (int)(num1[len1] - '0') + carry;
		if(result > 9){
			carry = result/10;
			result = result%10;
		}
		else{
			carry = 0;
		}
		answer = strcat(answer,(char*)(result + '0'));
		len1--;
	}

	while(len2>=0)
	{
		result = (int)(num2[len2] - '0') + carry;
		if(result > 9){
			carry = result/10;
			result = result%10;
		}
		else{
			carry = 0;
		}
		answer = strcat(answer,(char*)(result + '0'));
		len2--;
	}

	if(carry>0)
		answer = strcat(answer,(char*)(carry + '0'));
	
	resultInt.intString = strrev(answer);

	// add sign;
	resultInt.signValue = longInt.sign();

	return resultInt;
}

// '-' operator
LongInt LongInt::operator-(LongInt& longInt){	
	//longInt.intString -> parameter
	//LongInt::intString -> current num

	LongInt resultInt = *(new LongInt());
	int borrow = 0,result;

	char* num1 = LongInt::intString;
	char* num2 = longInt.intString;

	if(LongInt.sign() == 1 && longInt.sign() == -1){
		LongInt temp = *(new LongInt)
		temp = longint;
		temp.signValue = 1;
		return (this + temp);
	}
	if(LongInt.sign() == -1 && longInt.sign() == 1){
		LongInt temp = *(new LongInt)
		temp = longint;
		temp.signValue = -1;
		return (this + temp);
	}
	if(LongInt.sign() == -1 && longInt.sign() == -1){
		LongInt temp = new LongInt(this);
		temp.signValue = 1;
		return (longInt - temp);
	}	

	int len1 = strlen(num1) - 1, len2 = strlen(num2) - 1;
	char* answer = new char[40];
	char* first,second;
	int flen,slen,i;

	// when control is here it is of the form a-b (where a and b are positive)
	if(len1 > len2){
		first = num1;
		second = num2;
		flen = len1;
		slen = len2;
		resultInt.signValue = 1;
	}
	else if(len1 < len2){
		first = num2;
		second = num1;
		flen = len2;
		slen = len1;
		resultInt.signValue = -1;
	}
	else{
		i = 0;
		while(i < len1){
			if(num1[i] > num2[i]){
				first = num1;
				second = num2;
				flen = len1;
				slen = len2;
				resultInt.signValue = 1;
				break;
			}
			else if (num2[i] > num1[i]){
				first = num2;
				second = num1;
				flen = len2;
				slen = len1;
				resultInt.signValue = -1;
				break;
			}
			else
				i++;
		}
	}
	int val;
	while(flen>=0 && slen>=0)
	{
		//result = (int)(first[flen] - '0') - (int)(second[slen] - '0') + borrow;
		if(first[flen] < second[slen]){
			//borrowing from previous digit(s)
			i = 1;
			while((flen - i)>=0 && first[flen-i]=='0'){
				i++;
			}
			val = first[flen-i] - '0';
			while(i>=1){
				first[flen-i] = (char)(val-1 + '0');
				val = (int)(first[flen-i+1] - '0' + 10);
				i--;
			}
			result = val - (int)(second[slen] - '0');
		}
		else{
			result = (int)(first[flen] - '0') - (int)(second[slen] - '0');
		}

		//Constructing the answer string back
		answer = strcat(answer,(char*)(result + '0'));

		flen--;
		slen--;
	}
	while(flen >= 0)
	{
		result = (int)(first[flen] - '0');
		answer = strcat(answer,(char*)(result + '0'));
		flen--;
	}

	while(slen >= 0)
	{
		result = (int)(second[slen] - '0');
		answer = strcat(answer,(char*)(result + '0'));
		slen--;
	}
	
	resultInt.intString = strrev(answer);

	return resultInt;
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

//display number in standard out
void LongInt::dump() {
	if(intSignValue == 0) {
		cout<<0<<endl;
		return ;
	}
	if(intSignValue == -1) {
		cout<<"-";
	}
	cout<<intString;
	cout<<endl;
}


//assignment operator
LongInt& LongInt::operator=(int i) {
	
	if(i == 0) {
		intSignValue = 0;
		intString = "0";
		size = 1;
		return *this;
	}
	else {
		
		if(i<0) {
			intSignValue = -1;
			i = i*-1;
		}
		else {
			intSignValue  = 1;
		}

		char buffer[64];
		_itoa(i,buffer,10);
		
		size = strlen(buffer);
		intString = buffer;


	}
		
}

//assignment operator
LongInt& LongInt::operator=(LongInt& i) {

	intSignValue = i.intSignValue;
	size = i.size;
	intString = i.intString;
	
	return *this;
}

/*
//add operator
LongInt LongInt::operator+(LongInt& i) {
	LongInt ans;
	//check zero
	if(this->eqZero() && i.eqZero()) {
		ans.setZero(true);
		ans.setNeg(false);
		return ans;
	}
	if(this->eqZero()) {
		return LongInt(i);
	}
	if(i.eqZero()) {
		return LongInt(*this);
	}
	//check same sign
	if(this->sign() == i.sign()) {
		ans.setZero(false);
		ans.setNeg(i.sign()==-1);
		int x = 0;
		int y = 0;
		int sizeX = this->num.size();
		int sizeY = i.num.size();

		//add set of 9 digits
		while(x < sizeX && y < sizeY) {
			
			int sum = this->num[x]+i.num[y];
			ans.num.push_back(sum);
			x++;
			y++;
		}
		if(x != sizeX) {
			while(x<sizeX) {
				ans.num.push_back(this->num[x]);
				x++;
			}
		}
		if(y != sizeY) {
			while(y<sizeY) {
				ans.num.push_back(i.num[y]);
				y++;
			}
		}
		//add carry
		for(int k = 0;k<ans.num.size();k++) {
			int carryCount = 0;
			if(ans.num[k] > 1000000000) {
				carryCount = ans.num[k]/1000000000;
				ans.num[k] = ans.num[k] % 1000000000;
	
				if((k+1) != ans.num.size()) 
					ans.num[k+1] += carryCount;
				else
					ans.num.push_back(carryCount);
			}
		}
		return ans;

	}
	//check different sign combination
	if(this->sign() == -1) {
		LongInt temp(*this);
		temp.setNeg(false);
		ans = i - temp;
		return ans;
	}
	else {
		LongInt temp(i);
		temp.setNeg(false);
		ans = *this - temp;
		return ans;
	}
}
*/
/*
//minus operator
LongInt LongInt::operator-(LongInt& i) {
	LongInt ans;
	//check zero
	if(this->eqZero() && i.eqZero()) {
		ans.setZero(true);
		ans.setSignValue(0);
		return ans;
	}
	if(this->eqZero()) {
		ans = i;
		ans.setNeg(i.sign()==-1 ? +1:-1);
		return ans;
	}
	if(i.eqZero()) {
		return LongInt(*this);
	}
	//check same sign		//@@@@@@@@@@@@@@@@@@@@@@
	if(this->sign() == i.sign()) {
		if(*this == i) {			//Same Sign and equal absolute value
			return LongInt(0);
		}
		//answer is not zero
		LongInt* large;
		LongInt* small;
		bool negate = false;
		if(*this > i) {
			large = this;
			small = &i;
		}
		else {
			large = &i;
			small = this;
			negate = true;
		}
		
		int x = 0;
		int y = 0;
		int sizeX = large->num.size();
		int sizeY = small->num.size();
		
		
		//minus set of 9 digits
		while(x < sizeX && y < sizeY) {
			
			int dif = large->num[x]-small->num[y];
			ans.num.push_back(dif);
			x++;
			y++;
		}
		if(x != sizeX) {
			while(x<sizeX) {
				ans.num.push_back(large->num[x]);
				x++;
			}
		}
		//check negative number and remove by taking one unit from more significant int
		for(int k = 0;k<ans.num.size();k++) {
			if(ans.num[k]<0) {
				if((k+1) != ans.num.size()) {
					ans.num[k] = 1000000000-ans.num[k]*-1;
					ans.num[k+1] = ans.num[k+1]-1;
				}
			}
		}
		int j = ans.num.size()-1;
		//remove 0 at the start of Longint
		while(j>=0) {
			if(ans.num[j] == 0) {
				ans.num.pop_back();
				j--;
			}
			else break;
		}
		//set sign and zero
		if(this->sign() == -1) {
			if(negate) {
				ans.setNeg(false);
			}
			else {
				ans.setNeg(true);
			}
		}
		else {
			if(negate) {
				ans.setNeg(true);
			}
			else {
				ans.setNeg(false);
			}
		}
		return ans;
	}
	//check different sign combination
	if(this->sign() == -1) {
		LongInt temp(*this);
		temp.setNeg(false);
		ans = temp + i;	
		ans.setNeg(ans.sign() == -1 ? false : true);
		return ans;
	}
	else {
		LongInt temp(i);
		temp.setNeg(false);
		ans = *this + temp;;
		return ans;
	}
}

*/

/*
//multiplication operator
LongInt LongInt::operator*(LongInt& i) {
	//check zero
	if(i.eqZero() || this->eqZero()) {
		return LongInt(0);
	}
	LongInt ans(0);
	ans.setZero(false);

	for(int x = 0;x<i.num.size();x++) {
		LongInt temp(0);
		for(int k = 0;k<x;k++) {
			temp.num.push_back(0);
		}
		for(int y = 0;y<this->num.size();y++) {
			long long pro = (long long) i.num[x] * this->num[y];
			if((temp.num.size())-x != y) {
				pro = pro + temp.num[y+x];
				temp.num.pop_back();
			}
			int countCarry = 0;
			if(pro > 1000000000) {
				countCarry = pro/1000000000;
				pro = pro% 1000000000;
			}
			temp.num.push_back((int)pro);
			if(countCarry >0) {
				temp.num.push_back(countCarry);
			}
		}
		int l = temp.num.size()-1;
		while(l>=0) {
			if(temp.num[l] == 0) {
				temp.num.pop_back();
				l--;
			}
			else break;
		}
		temp.setZero(temp.num.size()<0);
		ans = ans+temp;
	}
	//set sign
	if(i.sign() == this->sign()) {
		ans.setNeg(false);
	}
	else {
		ans.setNeg(true);
	}
	return ans;
}

*/
//> operator
bool LongInt::operator>(LongInt& i) {
	if(this->eqZero() && i.eqZero()) {
		return false;
	}

	if(this->eqZero()) {
		return i.intSignValue == -1;
	}

	if(i.eqZero()) {
		return this->intSignValue == 1;
	}

	if(this->intSignValue != i.intSignValue) {
		return this->intSignValue == 1;
	}

	else {

		
		if(this->size != i.size) {		// Two Numbers has same Sign and One has more digits
				
				return ((this->intSignValue == 1)? this->size > i.size : !(this->size > i.size));
		}
		else{						// Two Numbers has same Sign and Same number of digits
			int numdigits = max((this->size), (i.size));
			for (int inx = 0; inx< numdigits; inx++)
			{
				if (this->intString[inx] > i.intString[inx])
					return (this->intSignValue == 1)?  true: false;
				else if (this->intString[inx] < i.intString[inx])
					return (this->intSignValue == 1)?  false: true;
			}
		}

		
		return false;
		}
	}






//< operator
bool LongInt::operator<(LongInt& i) {
	if(this->eqZero() && i.eqZero()) {
		return false;
	}

	if(this->eqZero()) {
		return i.intSignValue == 1;
	}

	if(i.eqZero()) {
		return this->intSignValue == -1;
	}

	if(this->intSignValue != i.intSignValue) {
		return this->intSignValue == -1;
	}

	else {
		if(this-> size != i.size) {	// Two Numbers has same Sign and One has more digits
			return ((this->intSignValue == -1)? this->size > i.size : !(this->size > i.size));
		}
		else
		{
			int numdigits = max((this->size), (i.size));
			for (int inx = 0; inx< numdigits; inx++)
			{
				if (this->intString[inx] > i.intString[inx])
					return (this->intSignValue == -1)?  true: false;
				else if (this->intString[inx] < i.intString[inx])
					return (this->intSignValue == -1)?  false: true;
			}

		}
		
		return false;
	}
}

bool LongInt::operator==(LongInt& i) {
	if(this->eqZero() && i.eqZero()) {
		return true;
	}
	if(this->eqZero() || i.eqZero()) {
		return false;
	}
	if(this->intSignValue != i.intSignValue) {
		return false;
	}
	else {
		if(this-> intSignValue != i.intSignValue) {
			return false;
		}
		
		return true;
	}
}
}

bool LongInt::eqZero() {
	return intSignValue == 0;
}

int LongInt::sign() {
	return intSignValue;
}

/*
double LongInt::doubleValue() {
	double ans = 0;
	double multi = 1000000000;
	for(int i = 0;i<num.size();i++) {
		double place = 1;
		for(int j = 0;j<i;j++) {
			place = place * multi;
		}
		ans = ans + (double)num[i] * place;
	}
	return ans;
}
*/
