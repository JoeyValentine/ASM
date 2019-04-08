// Ones_Add_Sub_main.cpp : Defines the entry point for the console application.
//
#include <stdio.h>

bool ONEs_ADD_SUB ( // Return false if normal add or sub. Return true if overflow.
	unsigned char A, unsigned char B, // two 8 bit 1's complement numbers
	int ADD_SUB_FLAG, // 0 : S = A add B, 1 : S = A sub B
	unsigned char *S // Sum
);

// get 2's complement number(i.e. decimal) from 1's complement
char Convert_Ones_to_Decimal( unsigned char S );

void main(void) {
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
}

