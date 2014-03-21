#define INFOG(str) 	printf ( "%s\n", str );\
			printf ( "**************************************************\n\n" );
#define INFOL(str)	printf ( "%s	", str );
#define STATUS(str)	printf ( "%s\n", str );

//C headers
#include <stdio.h>
#include <errno.h>
#include <sys/time.h> 
#include <sys/resource.h>
#include <stdlib.h>

//V_VarLArray headers
#include "V_VarLArray.h"

int PRINT ( Elem_of_Array *elem, void *buf)
{
	return print ( elem );
}

int main ( int argc, char *argv[] )
{
	int i = 0;
	int result = 0;

	INFOG ( "___START TEST___" );
	
	INFOG ( "TEST CONSTRUCT AND DESROY" );
	//*****************CONSTRUCT*******************//
	//Prepare
	INFOL ( "Prepare" );
	
	V_VarLArray *Varr;
	struct rlimit r;
	r.rlim_cur = 1000000000;
	r.rlim_max = 1000000005;	
	
	if ( setrlimit ( RLIMIT_AS, &r ) )
	{
		STATUS ( "PROBLEM: setrlimits" );
		return -1;
	}
	else
		STATUS ( "OK" );
	
	//START TEST CONSTRUCT AND DOSTROY
	INFOL ( "Start test construct and destroy" );	
	fflush ( stdout );	
	for ( i = 1; i < 100; ++i )
	{
		errno = 0;
		result = 0;
		//Test construct
		Varr = construct ( i*10000000000 );
		if (( ( Varr == NULL ) && ( errno == 0 ) ) ||\
		    ( ( Varr != NULL ) && ( errno != 0 ) ))

		{
			STATUS ( "Construct FAIL" );
			printf ( "test #%d\n", i );
			return -1;
		}
		
		//Test destroy
		result = destroy ( Varr );
		if (( ( result == 0 ) && ( errno != 0 ) ) ||\
		    ( ( result != 0 ) && ( errno == 0 ) ))
		{
			STATUS ( "Destroy FAIL" );
			printf ( "test #%d\n", i );
			return -1;
		}
	}
	STATUS ( "OK" );
	INFOG ( "End test construct and destroy" );
	//END test construct and sestroy

	//Test Resize
	INFOG ( "Start test resize" );
	INFOL ( "Prepare" );
	//Prepare
	Varr = construct ( 10 );
	STATUS ( "OK" );
	
	INFOL ( "Test \"Bad pointer\"" );
	result = resize ( NULL, 100 );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );  
	
	INFOL ( "Test \"Not memory\"" );
	result = resize ( Varr, 1000000000 );
	if ( result == 0 || errno == 0 )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );
	
	destroy ( Varr );
	Varr = construct ( 10 );
	INFOL ( "Test \"Nolmal allocate\"" );
	result = resize ( Varr, 100 );
	if ( result == 0 && errno == 0 )
	{
		STATUS( "OK" );
	}
	else
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	INFOG ( "Test resize end" );
	

	Elem_of_Array x = {'1'};
	insert(Varr, 3, &x);
	Elem_of_Array *gg = take ( Varr, 2 );
	printf("%c\n", gg->data);

	destroy ( Varr );

	//Test insert
	INFOG ( "Test insert start" );
	INFOL ( "Prepare" );
	Varr = construct ( 5 );
	Elem_of_Array el = { '5' };	
	STATUS ( "OK" );

	INFOL ( "Test \"Bad pointer array\" ")
	result = insert ( NULL, 0, &el );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Bad pos\"" );
	result = insert ( Varr, 6, &el );
 	if ( result == 0 || errno != EINVAL )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Bad pointer elem\" ")
	result = insert ( Varr, 0, NULL );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Nolmal insert\"" );
	result = insert ( Varr, 1, &el );
	if ( result == 0 && errno == 0 )
	{
		STATUS( "OK" );
		destroy ( Varr );
	}
	else
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	INFOG ( "Test insert end" );
	//Test insert end

	//Test copy start
	INFOG ( "Test copy start" );
	INFOL ( "Prepare" );
	Elem_of_Array s = {'5'};
	Elem_of_Array d;	
	STATUS ( "OK" );

	INFOL ( "Test \"Bad sourse\"" );
	result = copy ( NULL, &d );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Bad dest\" ")
	result = copy ( &s, NULL );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Nolmal copy\"" );
	result = copy ( &s, &d );
	if ( result == 0 && errno == 0 )
	{
		STATUS( "OK" );
	}
	else
	{
		STATUS ( "FAIL" );
		return -1;
	}
	INFOG ( "Test copy end" );	

	//Test clear start
	INFOG ( "Test clear start" );
	INFOL ( "Prepare" );	
	STATUS ( "OK" );

	INFOL ( "Test \"Bad pointer\"" );
	result = clear ( NULL );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Nolmal clear\"" );
	result = clear ( &s );
	if ( result == 0 && errno == 0 )
	{
		STATUS( "OK" );
	}
	else
	{
		STATUS ( "FAIL" );
		return -1;
	}
	INFOG ( "Test clear end" );	

	//Test print start
	INFOG ( "Test print start" );
	INFOL ( "Prepare" );	
	STATUS ( "OK" );

	INFOL ( "Test \"Bad pointer\"" );
	result = print ( NULL );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Nolmal print\"" );
	result = print ( &s );
	if ( result == 0 && errno == 0 )
	{
		STATUS( "OK" );
	}
	else
	{
		STATUS ( "FAIL" );
		return -1;
	}
	INFOG ( "Test clear end" );	

	//Test getSize start
	INFOG ( "Test getSize start" );
	INFOL ( "Prepare" );
	Varr = construct (10);	
	STATUS ( "OK" );

	INFOL ( "Test \"Bad pointer\"" );
	result = getSize ( NULL );
 	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Nolmal getSize\"" );
	result = getSize ( Varr );
	if ( result == 10 && errno == 0 )
	{
		STATUS( "OK" );
		destroy ( Varr );
	}
	else
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	INFOG ( "Test getSize end" );	

	//Test take
	INFOG ( "Test take start" );
	INFOL ( "Prepare" );
	Varr = construct ( 5 );
	Elem_of_Array *elem;	
	STATUS ( "OK" );

	INFOL ( "Test \"Bad pointer array\" ")
	elem = take ( NULL, 0 );
 	if ( elem != NULL || errno != EBADR )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Bad pos\"" );
	elem = take ( Varr, 6 );
 	if ( elem != NULL || errno != EINVAL )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );  

	INFOL ( "Test \"Nolmal take\"" );
	elem = take ( Varr, 1 );
	if ( elem != 0 && errno == 0 )
	{
		STATUS( "OK" );
		destroy ( Varr );
	}
	else
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	INFOG ( "Test take end" );
	//Test take end

	//Test for_each
	INFOG ( "Test for_each start" );
	INFOL ( "Prepare" );
	
	char buf[10] = "";
	Varr = construct (10);
	for ( i = 0; i < 10; ++i )		
		Varr -> array[i].data = i + '0';
	
	STATUS ( "OK" );

	INFOL ( "Test \"Bad array\"" );
	result = Varr_for_each ( NULL, &buf, &PRINT );
	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );

	INFOL ( "Test \"Bad func\"" );
	result = Varr_for_each ( Varr, &buf, NULL );
	if ( result == 0 || errno != EBADR )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );

	INFOL ( "Test \"Normal work\"" );
	result = Varr_for_each ( Varr, &buf, &PRINT );
	if ( result != 0 || errno != 0 )
	{
		STATUS ( "FAIL" );
		destroy ( Varr );
		return -1;
	}
	else
		STATUS ( "OK" );


	INFOL ( "Test \"Bad result exec\"" );
	free ( Varr -> array );	
	Varr -> array = NULL;
	result = Varr_for_each ( Varr, &buf, &PRINT );	
	if ( result == 0 || errno != EINVAL )
	{
		STATUS ( "FAIL" );
		Varr -> array = (Elem_of_Array*) malloc ( sizeof(Elem_of_Array) );
		destroy ( Varr );
		return -1;
	}
	else
	{
		STATUS ( " OK" );
		Varr -> array = (Elem_of_Array*) malloc ( sizeof(Elem_of_Array) );
		destroy ( Varr );
	}	

	INFOG ( "Test for_each end" );

	INFOG ( "___TEST_LIB_END___" );	
	

	return 0;
}

