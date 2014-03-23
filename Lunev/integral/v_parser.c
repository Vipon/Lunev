//C headers
#include <stdio.h>
#include <errno.h>
#include <assert.h>

//Vipon header
#include "v_parser.h"

//************************************************************************

int checkInput ( char *func, atribut *atr, char *nameF )
{
	int error = 0;
	
	if ( !func )
	{
		printf ( "ERROR: %s has problem with input\
			  data, func isn't available\n", nameF );
		++error;
	}
	if ( !atr )
	{
		printf ( "ERROR: %s has problem with input\
			  data, atr isn't available\n", nameF );
		++error;
	}

	if ( error )
		return -1;
	
	return 0;	
}

//************************************************************************


double Calculate ( char *func, double x )
{
	//check
	if ( !func )
	{
		printf ( "Sory, but you fogot to give me function\n" );
		errno = EADDRNOTAVAIL;
		return -1;
	}

	//Prepear : create and start inicialize
	double value = 0;
	
	atribut atr;
	atr.pos = 0;
	atr.x   = x;
	//end Prepear

	//start calculation
	value = GetE ( func, &atr );
	//end calculation
	
	return value;
}

//************************************************************************

double GetE ( char *func, atribut *atr )
{
	//check
	assert ( !checkInput ( func, atr, "GetE" ) );
	
	double value = GetT ( func, atr );
	
	while ( ( func[atr -> pos] == '+' ) || ( func[atr -> pos] == '-' ) )
	{
		int operation = func[atr -> pos];
		++(atr -> pos);
		
		double value2 = GetT ( func, atr );
		
		if ( operation == '+' )
			value += value2;
		else
			value -= value2; 
	}
	
	return value;
}

//************************************************************************

double GetT ( char *func, atribut *atr )
{
	assert ( !checkInput ( func, atr, "GetT" ) );
	
	double value = GetP ( func, atr );
	
	while ( ( func[atr -> pos] == '*' ) || ( func[atr -> pos] == '/' ) )
	{
		char operation = func[atr -> pos];
		++(atr -> pos);

		double value2 = GetP ( func, atr );
		
		if ( operation == '/' )
		{
			if ( value2 != 0 )
				value /= value2;
			else
				assert ( "ERROR: division by 0" == 0 );
		}
		else
			value *= value2;
	}

	return value;		
}

//************************************************************************

double GetP ( char *func, atribut *atr )	
{
	assert ( !checkInput ( func, atr, "GetT" ) );
	
	if ( func[atr -> pos] == '(' )
	{
		++(atr -> pos);
		double value = GetE ( func, atr );		

		if ( func[atr -> pos] != ')' )
		{
			printf ( "ERROR : Incorrect vocabulary, skipped \')\'\n" );
			assert ( 0 );

		}
		++(atr -> pos );

		return value;
	}
	else
		return GetN ( func, atr );
	
}

//************************************************************************

double GetN ( char *func, atribut *atr )
{
	assert ( !checkInput ( func, atr, "GetT" ) );
	
	double value = 0;
	
	while ( ( '0' <= func[atr -> pos] ) && ( func[atr -> pos] <= '9' ) )
	{
		value = value*10 + func[atr -> pos] - '0'; 
		++(atr -> pos);
	}

	return value;
}

//************************************************************************
