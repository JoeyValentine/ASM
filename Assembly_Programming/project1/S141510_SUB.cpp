#include <stdio.h>

// calculate one bit with bit operator
int One_Bit_Adder(int A,int B,int Cin,int* Cout,int bit){

	//Cin = carry in , Cout = carry out
	//a and b is first bit of A and B
	int a,b,sum;

	// divide the number of cases
	if((A&(1<<bit)) == (1<<bit))
		a = 1;
	else
		a = 0;
	if((B&(1<<bit)) == (1<<bit))
		b = 1;
	else
		b = 0;

	*Cout = ((~a)&b&Cin)|(a&(~b)&Cin)|(a&b&(~Cin))|(a&b&Cin);
	sum = ~a&~b&Cin|~a&b&~Cin|a&~b&~Cin|a&b&Cin;
	
	return sum;
}

// function which distinguishes between positive number and negative number
bool isItPlus( unsigned A ){
	if( (A&(1<<7)) == (1<<7) )
		return false;
	else
		return true;
}

// calculate A add B completeley by calling One_Bit_Adder function 9 times
int Bit_Full_Adder( unsigned char A, unsigned char B ){

	int Cin=0,sum,Cout,ret=0,tempA=(int)A,tempB=(int)B;

	//calculate A add B
	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,0);
	if(sum==1)
		ret|=(1<<0);
	else if(sum==0)
		ret&=~(1<<0);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,1);
	if(sum==1)
		ret|=(1<<1);
	else if(sum==0)
		ret&=~(1<<1);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,2);
	if(sum==1)
		ret|=(1<<2);
	else if(sum==0)
		ret&=~(1<<2);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,3);
	if(sum==1)
		ret|=(1<<3);
	else if(sum==0)
		ret&=~(1<<3);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,4);
	if(sum==1)
		ret|=(1<<4);
	else if(sum==0)
		ret&=~(1<<4);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,5);
	if(sum==1)
		ret|=(1<<5);
	else if(sum==0)
		ret&=~(1<<5);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,6);
	if(sum==1)
		ret|=(1<<6);
	else if(sum==0)
		ret&=~(1<<6);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,7);
	if(sum==1)
		ret|=(1<<7);
	else if(sum==0)
		ret&=~(1<<7);
	Cin=Cout;

	sum=One_Bit_Adder(tempA,tempB,Cin,&Cout,8);
	if(sum==1)
		ret|=(1<<8);
	else if(sum==0)
		ret&=~(1<<8);
	Cin=Cout;

	return ret;
}

// get 2's complement number(i.e. decimal) from 1's complement
char Convert_Ones_to_Decimal( unsigned char S ){
	int Cin=0,sum,Cout,tempS=(int)S;
	char ret=0;
	if( (S&(1<<7)) == 0 )
		ret = (char)S;
	else{
		sum=One_Bit_Adder(tempS,1,Cin,&Cout,0);
		if(sum==1)
			ret|=(1<<0);
		else if(sum==0)
			ret&=~(1<<0);
		Cin=Cout;

		sum=One_Bit_Adder(tempS,1,Cin,&Cout,1);
		if(sum==1)
			ret|=(1<<1);
		else if(sum==0)
			ret&=~(1<<1);
		Cin=Cout;

		sum=One_Bit_Adder(tempS,1,Cin,&Cout,2);
		if(sum==1)
			ret|=(1<<2);
		else if(sum==0)
			ret&=~(1<<2);
		Cin=Cout;

		sum=One_Bit_Adder(tempS,1,Cin,&Cout,3);
		if(sum==1)
			ret|=(1<<3);
		else if(sum==0)
			ret&=~(1<<3);
		Cin=Cout;

		sum=One_Bit_Adder(tempS,1,Cin,&Cout,4);
		if(sum==1)
			ret|=(1<<4);
		else if(sum==0)
			ret&=~(1<<4);
		Cin=Cout;

		sum=One_Bit_Adder(tempS,1,Cin,&Cout,5);
		if(sum==1)
			ret|=(1<<5);
		else if(sum==0)
			ret&=~(1<<5);
		Cin=Cout;

		sum=One_Bit_Adder(tempS,1,Cin,&Cout,6);
		if(sum==1)
			ret|=(1<<6);
		else if(sum==0)
			ret&=~(1<<6);
		Cin=Cout;

		sum=One_Bit_Adder(tempS,1,Cin,&Cout,7);
		if(sum==1)
			ret|=(1<<7);
		else if(sum==0)
			ret&=~(1<<7);
		Cin=Cout;
	}
	return ret;
}

bool ONEs_ADD_SUB ( // Return false if normal add or sub. Return true if overflow.
		unsigned char A, unsigned char B, // two 8 bit 1's complement numbers
		int ADD_SUB_FLAG, // 0 : S = A add B, 1 : S = A sub B
		unsigned char *S /*sum*/){

	int ret=0; //it store A add B to check overflow
	char DA,DB; //

	DA=Convert_Ones_to_Decimal(A);
	DB=Convert_Ones_to_Decimal(B);

	//chose operator
	if(ADD_SUB_FLAG==0){
		*S = ret = Bit_Full_Adder(A,B);
		if( (ret<<8) == 1)
			Bit_Full_Adder(*S,1);
	}
	else if(ADD_SUB_FLAG==1){
		B = ~B;
		*S = ret = Bit_Full_Adder(A,B);
	}

	// if 9th bit is 1, then end around borrow is produced.
	// so we have to add ret and 1
	if( (ret&(1<<8)) == (1<<8) ){
		ret&=~(1<<8);
		*S=ret=Bit_Full_Adder(ret,1);
	}

	// if ret is overflow, function will return true
	if( isItPlus(A) && isItPlus(B) ){
		if( (ret&(1<<7)) == (1<<7) ){
			*S = 127;
			return true;
		}
	}
	else if( !isItPlus(A) && !isItPlus(B) ){
		if( (ret&(1<<7)) != (1<<7) ){
			*S = 128;
			return true;	
		}
	}

	// if S is minus 0, then S is changed by 0
	if(*S==255)
		*S = 0;

	// if ret is not overflow, function will return false
	return false;
}
