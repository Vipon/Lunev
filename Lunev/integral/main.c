//C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Vipon headers
#include "v_integral.h"

const unsigned LEN = 1024;
const unsigned LENY = 32;

int main ( int argc, char *argv[] )
{
//	char *func = (char*) calloc ( LEN, sizeof(char) );
	double result = 0;
	char *Ymin = (char*) calloc ( LENY, sizeof(char) );
	
	point p;
	p.Y = (char*) calloc ( LENY, sizeof(char) );

	printf ( "Hello my friend!\n" );
//	printf ( "Enter you function: " );
//	scanf  ( "%s", func );

	printf ( "Enter minX: " );
	scanf  ( "%lf", &(p.minX) );

	printf ( "Enter maxX: " );
	scanf  ( "%lf", &(p.maxX) );
	
	printf ( "Enter func of Ymax: " );
	scanf  ( "%s", p.Y );

	printf ( "Enter func of Ymin: " );
	scanf  ( "%s", Ymin );

	result = Integral ( &p );
	strcpy ( p.Y, Ymin );
	result -= Integral ( &p );
	
		
	printf ( "Result = %lf\n", result );
	printf ( "Goodbye\n" );
	
	return 0;

}
