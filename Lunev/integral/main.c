#include <stdio.h>
#include <stdlib.h>
#include "v_parser.h"

const unsigned LEN = 1024;

int main ( int argc, char *argv[] )
{
	char *func = (char*) calloc ( LEN, sizeof(char) );
	double result = 0;
	atribut atr;
	atr.pos = 0;	

	printf ( "Hello my friend!\n" );
	printf ( "Enter you function: " );
	scanf  ( "%s", func );

	result = Calculate ( func, &atr );
	
	printf ( "Result = %lf\n", result );
	printf ( "Goodbye\n" );
	
	return 0;

}
