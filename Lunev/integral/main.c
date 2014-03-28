//C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//Vipon headers
#include "v_dIntegral.h"

const unsigned LEN = 1024;
const unsigned LENY = 32;

int main ( int argc, char *argv[] )
{
	char *func = (char*) calloc ( LEN, sizeof(char) );
	double result = 0;
	int n;
	double minX;
	double maxX;
	
	switch ( argc ) {
	
	case 2:
		n = 1; 
		break;
	case 3:
		n = atoi ( argv[2] );
		break;
	default:
		printf ( "Too many arguments\n" );
		return -1;
	}

	FILE *integr = fopen ( argv[1], "r" );
	if ( !integr )
	{
		printf ( "ERROR: i can't open file %s", argv[1] );
		free ( func );
		return -1;
	}

	Dpoint p;
	p.minY  = (char*) calloc ( LENY, sizeof(char) );
	p.maxY  = (char*) calloc ( LENY, sizeof(char) );

	fscanf  ( integr, "%s", func );
	fscanf  ( integr, "%lf", &(minX) );
	fscanf  ( integr, "%lf", &(maxX) );
	fscanf  ( integr, "%s", p.minY );
	fscanf  ( integr, "%s", p.maxY );

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
	
	double **r = (double**) calloc ( 1, sizeof(double*) );
	for ( i = 0; i < n; ++i)
	{
		pthread_join ( tid[i], (void**)r );
		result += **r;
		free (*r);	
	}

	printf ( "Result = %lf\n", result );

	free ( func );
	free ( p.minY );
	free ( p.maxY );
	free ( p1 );
	free ( arg );
	free ( tid );
	free ( r );

	fclose ( integr );
		
	return 0;

}
