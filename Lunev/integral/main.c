//C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <pthread.h>

//Vipon headers
#include "v_dIntegral.h"

const unsigned LEN = 1024;
const unsigned LENY = 32;

/*typedef struct argI {
	
	char *func;
	Dpoint *p;	
} argI;*/

int main ( int argc, char *argv[] )
{
	char *func = (char*) calloc ( LEN, sizeof(char) );
	double result = 0;
	struct tms Start;
	struct tms End;
	int n;
	double minX;
	double maxX;

	switch ( argc ) {
	
	case 1:
		n = 1; 
		break;
	case 2:
		n = atoi ( argv[1] );
		break;
	default:
		printf ( "Too many arguments\n" );
		return -1;
	}
	
	Dpoint p;
	p.minY  = (char*) calloc ( LENY, sizeof(char) );
	p.maxY  = (char*) calloc ( LENY, sizeof(char) );

	printf ( "Hello my friend!\n" );
	printf ( "Enter you function: " );
	scanf  ( "%s", func );

	printf ( "Enter minX: " );
	scanf  ( "%lf", &(minX) );

	printf ( "Enter maxX: " );
	scanf  ( "%lf", &(maxX) );
	
	printf ( "Enter func of Ymin: " );
	scanf  ( "%s", p.minY );
	
	printf ( "Enter func of Ymax: " );
	scanf  ( "%s", p.maxY );

	times ( &Start );
	
	double d = (maxX - minX) / n;
	int i = 0;
	pthread_t *tid = (pthread_t*) calloc ( n, sizeof(pthread_t) );
	argI *arg      = (argI*) calloc ( n, sizeof(argI) );
	Dpoint *p1     = (Dpoint*) calloc ( n, sizeof(Dpoint) );	
	

	for ( i = 0; i < n; ++i )
	{	
		p1[i].minX = minX + d*i;
		p1[i].maxX = minX + d*(i+1);
		p1[i].minY = p.minY;
		p1[i].maxY = p.maxY;		
	
		arg[i].func = func;
		arg[i].p = &p1[i];	
		pthread_create ( &tid[i], NULL, (void*) &dIntegral, (void*) &arg[i] );	
	}
	
	double **r;
	for ( i = 0; i < n; ++i)
	{
		pthread_join ( tid[i], (void**)r );
		result += **r;
		free (*r);	
	}

	times ( &End );	
	
	printf ( "Result = %lf\n", result );
	printf ( "Work Time = %ld\n", End.tms_utime - Start.tms_utime );
	printf ( "Goodbye\n" );

	free ( func );
	free ( p.minY );
	free ( p.maxY );
	free ( arg );
	//free ( result );
	free ( tid );
		
	return 0;

}
