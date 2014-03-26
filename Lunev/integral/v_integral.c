//*************//
//Made by Vipon//
//*************//

//C headers
#include <stdio.h>

//Vipon headers
#include "v_integral.h"
#include "v_parser.h"

//consts
const double V_EPSILON = 0.0001;

//************************************************************************

double Integral ( point *p )
{

	double result = 0;	
	double f1 = 0;
	double f2 = 0;
	atribut atrI;
	
	double i = 0;
	for ( i = (p -> minX); i < (p -> maxX); i += V_EPSILON )
	{
		(atrI.X)   = i;	
		(atrI.pos) = 0;
		f1 = Calculate ( p -> Y , &atrI );

		(atrI.X)   = i + V_EPSILON;	
		(atrI.pos) = 0;		
		f2 = Calculate ( (p -> Y),  &atrI );

		result += (f1 + f2) * V_EPSILON / 2;
	}

	return result;

}

//************************************************************************
