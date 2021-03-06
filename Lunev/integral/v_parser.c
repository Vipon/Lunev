//**************//
//Maked by Vipon//
//**************//

//C headers
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <math.h>

//Vipon header
#include "v_parser.h"

//const
const double V_PI = 3.14159265359;

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


double Calculate ( char *func, atribut *atr )
{
	//check
	assert ( !checkInput ( func, atr, "Calculate" ) );

	//Prepear : create and start inicialize
	double value = 0;

	//start calculation
	value = GetE ( func, atr );
	
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
	
	while ( ( func[atr -> pos] == '*' ) || ( func[atr -> pos] == '/' )\
					    || ( func[atr -> pos] == '^' ) )
	{
		char operation = func[atr -> pos];
		++(atr -> pos);

		double value2 = GetP ( func, atr );
		
		switch ( operation ) {
		case '/':
			if ( value2 != 0 )
				value /= value2;
			else
				assert ( "ERROR: division by 0" == 0 );
			break;
		case '*':
			value *= value2;
			break;
		case '^':
			value = pow ( value, value2 );
			break;
		default:
			break;
		}
	}

	return value;		
}

//************************************************************************

double GetP ( char *func, atribut *atr )	
{
	assert ( !checkInput ( func, atr, "GetP" ) );
	
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
	else if ( ((func[atr -> pos] <= '9') && (func[atr -> pos] >= '0'))\
					    || (func[atr -> pos] == '-') )
		return GetN ( func, atr );
	else
		return GetEF ( func, atr );	
}

//************************************************************************

double GetN ( char *func, atribut *atr )
{
	assert ( !checkInput ( func, atr, "GetN" ) );
	
	double value = 0;
	double k = 10;
	unsigned point = 0;
	int checkF = -1;

	while ( (( '0' <= func[atr -> pos] ) && ( func[atr -> pos] <= '9' ))\
			|| (func[atr -> pos] == '.') )
	{
		if ( func[atr -> pos] == '.' )
		{
			point = 1;
			++(atr -> pos);
			checkF = (atr -> pos);
		}

		if ( !point )
		{
			value = value*10 + func[atr -> pos] - '0'; 
			++(atr -> pos);
		}
		else
		{	
			value += (double)(func[atr -> pos] - '0') / k ;
			++(atr -> pos);
			k *= 10;	
		}
		
	}
	
	if ( checkF == (atr -> pos) )
		assert ( "ERROR: incorrect input Fraction" );

	return value;
}

//************************************************************************

double GetEF ( char *func, atribut *atr )
{
	assert ( !checkInput ( func, atr, "GetEF" ) );
	double value = 0;
	
	switch ( func[atr -> pos] )	
	{
	case 'c': case 'C':
		++(atr -> pos);
		if ( (func[atr -> pos] == 't') && (func[atr -> pos + 1] == 'g')\
					       && (func[atr -> pos + 2] == '(') )
		{
			(atr -> pos) += 3;
			value = 1 / tan ( GetE ( func, atr ) );	
			
			if ( func[atr -> pos] != ')' )
			{
				printf ( "ERROR : Incorrect vocabulary, skipped \')\'\n" );
				assert ( 0 );

			}	
			++(atr -> pos );
			
			return value;
		}
		else if ( (func[atr -> pos] == 'o') && (func[atr -> pos + 1] == 's')\
					            && (func[atr -> pos + 2] == '(') )
		{
			(atr -> pos) += 3;
			value = cos ( GetE ( func, atr ) );	
						
			if ( func[atr -> pos] != ')' )
			{
				printf ( "ERROR : Incorrect vocabulary, skipped \')\'\n" );
				assert ( 0 );

			}	
			++(atr -> pos );
			
			return value;
		}
		else
			assert	( "ERROR: i don't understand that you mean" == 0 );
		break;
	case 's': case 'S':
		++(atr -> pos);

		if ( (func[atr -> pos] == 'i') && (func[atr -> pos + 1] == 'n')\
					            && (func[atr -> pos + 2] == '(') )
		{
			(atr -> pos) += 3;
			value = sin ( GetE ( func, atr ) );	
			
			if ( func[atr -> pos] != ')' )
			{
				printf ( "ERROR : Incorrect vocabulary, skipped \')\'\n" );
				assert ( 0 );

			}	
			++(atr -> pos );
			
			return value;
		}
		else
			assert	( "ERROR: i don't understand that you mean" == 0 );
		break;
	case 't': case 'T':
		++(atr -> pos);

		if ( (func[atr -> pos] == 'g') && (func[atr -> pos + 1] == '(') )
		{
			(atr -> pos) += 2;
			value = tan ( GetE ( func, atr ) );	
			
			if ( func[atr -> pos] != ')' )
			{
				printf ( "ERROR : Incorrect vocabulary, skipped \')\'\n" );
				assert ( 0 );

			}	
			++(atr -> pos );
			
			return value;
		}
		else
			assert	( "ERROR: i don't understand that you mean" == 0 );
		break;
	
	case 'e': case 'E':
		++(atr -> pos);

		if ( (func[atr -> pos] == 'x') && (func[atr -> pos + 1] == 'p')\
					       && (func[atr -> pos + 2] == '(') )
		{
			(atr -> pos) += 3;
			value = exp ( GetE ( func, atr ) );	
			
			if ( func[atr -> pos] != ')' )
			{
				printf ( "ERROR : Incorrect vocabulary, skipped \')\'\n" );
				assert ( 0 );

			}	
			++(atr -> pos );
			
			return value;
		}
		else
			assert	( "ERROR: i don't understand that you mean" == 0 );
		break;
	
	case 'l': case 'L':
		++(atr -> pos);

		if ( (func[atr -> pos] == 'o') && (func[atr -> pos + 1] == 'g')\
					            && (func[atr -> pos + 2] == '(') )
		{
			(atr -> pos) += 3;
			value = log ( GetE ( func, atr ) );	
			
			if ( func[atr -> pos] != ')' )
			{
				printf ( "ERROR : Incorrect vocabulary, skipped \')\'\n" );
				assert ( 0 );

			}	
			++(atr -> pos );
			
			return value;
		}
		else
			assert	( "ERROR: i don't understand that you mean" == 0 );
		break;
	
	case 'p': case 'P':
		++(atr -> pos);

		if (func[atr -> pos] == 'i')
		{
			++(atr -> pos);			
			return V_PI;
		}
		else
			assert	( "ERROR: i don't understand that you mean" == 0 );
		break;

	case 'x': case 'X':
		++(atr -> pos);
		return (atr -> X);
	
		break;
	
	case 'y': case 'Y':
		++(atr -> pos);
		return (atr -> Y);
	
		break;
	
	default:
		assert	( "ERROR: i don't understand that you mean" == 0 );
		break;
	}
	return value;
}

//************************************************************************



















