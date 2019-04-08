// Ones_Add_Sub_main.cpp : Defines the entry point for the console application.
//
#include <stdio.h>

int One_Bit_Adder(int A,int B,int Cin,int* Cout,int bit){
	int a,b,sum;
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
bool isItPlus( unsigned A ){
	if( (A&(1<<7)) == (1<<7) )
		return false;
	else
		return true;
}
int Bit_Full_Adder( unsigned char A, unsigned char B ){

	int Cin=0,sum,Cout,ret=0,tempA=(int)A,tempB=(int)B;

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

	int ret=0;
	char DA,DB;

	DA=Convert_Ones_to_Decimal(A);
	DB=Convert_Ones_to_Decimal(B);

	if(ADD_SUB_FLAG==0){
		*S = ret = Bit_Full_Adder(A,B);
		if( (ret<<8) == 1)
			Bit_Full_Adder(*S,1);
	}
	else if(ADD_SUB_FLAG==1){
		B = ~B;
		*S = ret = Bit_Full_Adder(A,B);
	}

	if( (ret&(1<<8)) == (1<<8) ){
		ret&=~(1<<8);
		*S=ret=Bit_Full_Adder(ret,1);
	}

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

	if(*S==255) //when they -0
		*S = 0;

	return false;
}
int main(void) {
	int t, TN, iA, iB, Flag;
	unsigned char A, B, S;
	char DA, DB, DS;
	bool OVF;	// overflow flag

	scanf("%d", &TN);	// get the number of test cases

	for ( t = 0; t < TN; t++ ) {
		scanf("%d %d %d", &iA, &iB, &Flag);	// use int type for scanf 
		A = (unsigned char) iA; B = (unsigned char) iB;		// convert 32bits to 8 bits
		OVF = ONEs_ADD_SUB ( A, B, Flag, &S );
		DA = Convert_Ones_to_Decimal( A );
		DB = Convert_Ones_to_Decimal( B );
		DS = Convert_Ones_to_Decimal( S );
		if ( t != 0 ) {
			printf("\n");
		}
		if ( Flag == 0 ) {
			printf("%4d + %4d = %4d (%4d) ",DA, DB, DS, S);
		}
		else {
			printf("%4d - %4d = %4d (%4d) ",DA, DB, DS, S);
		}
		if ( OVF == true ) {
			printf("(overflow)");
		}
		else {
			printf("          ");
		}
		if ( S == 0xff ) {	// negative zero
			printf("*** NEGATIVE ZERO DETECTED ***");
		}
	}
	return 0;
}
