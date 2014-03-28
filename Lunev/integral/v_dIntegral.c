//*************//
//Made by Vipon//
//*************//

//C headers
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>

//Vipon headers
#include "v_dIntegral.h"
#include "v_parser.h"

//Constants
const double V_DEPSILON = 0.01;

double *dIntegral ( argI *arg )
{
	double *result = (double*) calloc ( 1, sizeof(double));
	double sq = V_DEPSILON * V_DEPSILON;
	atribut atr;	

	double i = 0;
	double j = 0;
	double maxY = 0;
	double minY = 0;

	for ( i = (arg -> p -> minX);\
	      i <= (arg -> p -> maxX); i += V_DEPSILON )
	{
		atr.X = i;
		atr.pos = 0;
		maxY = Calculate ( (arg -> p -> maxY), &atr );
		atr.pos = 0;
		minY = Calculate ( (arg -> p -> minY), &atr );

		for ( j = minY; j < maxY; j += V_DEPSILON )
		{
			atr.X = i + V_DEPSILON/2;
			atr.Y = j + V_DEPSILON/2;
			atr.pos = 0; 
			*(result) += (sq * Calculate ( arg -> func, &atr ));
		//	printf ( "res = %lf\n", *(result) ); 
		}

	}
		
	return result;
}

