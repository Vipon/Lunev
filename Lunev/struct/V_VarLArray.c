#define ERROR1(func, reason)	printf ( "ERROR: In function %s, %s.\n", func, reason );

#define ERROR(func, reason) 	printf ("");
//C Headers
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//V_VarLArray Headers
#include "V_VarLArray.h"

//*********************************************************************

V_VarLArray* construct ( unsigned int len )
{
	V_VarLArray* Varr = (V_VarLArray*) malloc ( sizeof(V_VarLArray) );
	if ( !Varr )
	{
		ERROR("construct", "memory for Varr isn't allocation");
		errno = ENOMEM;
		return NULL;
	}
		
	Varr -> length = len;
	Varr -> array = (Elem_of_Array*) calloc ( len , sizeof(Elem_of_Array) );
	if ( !(Varr -> array) )
	{
		ERROR("construct", "memory for Varr -> array isn't allocation");
		errno = ENOMEM;
		free ( Varr );
		return NULL;
	}
	
	Varr -> end = &( Varr -> array[len-1] );

	errno = 0;
	return Varr;
}

//*********************************************************************

int insert ( V_VarLArray *Varr, unsigned int pos, Elem_of_Array *elem )
{
	if ( !Varr )
	{
		ERROR("insert", "*Varr isn't valid" );
		errno = EBADR;
		return -1;
	}
	if ( !elem )
	{
		ERROR("insert", "*elem isn't valid" );
		errno = EBADR;
		return -1;
	}



	if ( pos > ( Varr -> length ) )
	{
		ERROR("insert", "pos > length of array");
		errno = EINVAL;
		return -1;
	}

	Varr -> array[pos-1].data =  elem -> data;
	errno = 0;
	return 0;
}

//*********************************************************************

int resize ( V_VarLArray *Varr, unsigned int nLen )
{
	if ( !Varr )
	{
		ERROR("insert", "*Varr isn't valid" );
		errno = EBADR;
		return -1;
	}

	//Start copy data
	V_VarLArray *VC = construct ( Varr -> length );
	if ( !VC )
	{
		ERROR("resize", "construct problem");
		return -1;
	}
	int i = 0;
	for ( i = 0; i < Varr -> length; ++i )
	{
		if ( copy ( &(Varr -> array[i]), &(VC -> array[i]) ) )
		{
			ERROR("resize", "copy problem");
			return -1;
		}
	}
	//end copy data

	if ( !(Varr -> array) )
	{
		ERROR("resize", "array == 0");
		return -1;
	}
	else		
		free ( Varr -> array );	
	Varr -> array = (Elem_of_Array*) calloc ( nLen,  sizeof(Elem_of_Array) );

	if ( !(Varr -> array) )
	{
		ERROR("relen", "memory for Varr -> array isn't allocation");
		errno = ENOMEM;
		return -1;
	}
	for ( i = 0; i < nLen; ++i )
	{
		if ( copy ( &(VC -> array[i]), &(Varr -> array[i]) ) )
		{
			ERROR("resize", "copy problem");
			return -1;
		}
	}
	
	Varr -> length = nLen;
	Varr -> end = &(Varr -> array[nLen-1]);
	errno = 0;
	return 0;	
}

//*********************************************************************

int destroy ( V_VarLArray *Varr )
{
	if ( !Varr )
	{
		ERROR("insert", "*Varr isn't valid" );
		errno = ENOMEM;
		return -1;
	}

	free ( Varr -> array );
	free ( Varr );
	
	errno = 0;
	return 0;
}

//*********************************************************************

int copy ( Elem_of_Array *source, Elem_of_Array *destination )
{	
	if ( !source )
	{
		ERROR("copy", "*source isn't valid");
		errno = EBADR;
		return -1;
	}
	if ( !destination )
	{
		ERROR("copy", "*destination isn't valid");
		errno = EBADR;
		return -1;
	}
	
	destination -> data = source -> data; 
	errno = 0;
	return 0;
}

//*********************************************************************

int clear ( Elem_of_Array *elem )
{
	if ( !elem )
	{
		ERROR("clear", "*elem isn't valid");
		errno = EBADR;
		return -1;
	}

	elem -> data = 0;
	errno = 0;
	return 0;
}

//*********************************************************************

int print ( Elem_of_Array *elem )
{
	if ( !elem )
	{
		ERROR("print", "*elem isn't valid" );
		errno = EBADR;
		return -1;
	}

	printf ( "%c\n", elem -> data );
	errno = 0;
	return 0;
}

//*********************************************************************

int getSize ( V_VarLArray *Varr )
{
	if ( !Varr )
	{
		ERROR("dump", "*Varr isn't valid");
		errno = EBADR;
		return -1;
	}

	errno = 0;
	return Varr -> length;	
}

//*********************************************************************

Elem_of_Array *take ( V_VarLArray *Varr, unsigned int num )
{
	if ( !Varr )
	{
		ERROR("take", "Varr isn't valid`");
		errno = EBADR;
		return NULL;
	}
	if ( num >= Varr -> length )
	{
		ERROR("take", "num > length of array");
		errno = EINVAL;
		return NULL;
	}
	
	errno = 0;
	return &(Varr -> array[num]);	
}

//*********************************************************************


int Varr_for_each ( V_VarLArray *Varr, void *buf,\
		    int (*func) ( Elem_of_Array *elem, void *buf ) )
{
	if ( !Varr )
	{
		ERROR("Varr_for_each", "*Varr isn't valid");
		errno = EBADR;
		return -1;
	}
	if ( !func )
	{
		ERROR("Varr_for_each", "*func isn't valid");
		errno = EBADR;
		return -1;
	}
	
	int i = 0;
	int result = 0;
	for ( i = 0; i < Varr -> length; ++i )
	{
		result = (*func) ( &(Varr -> array[i]), buf  );
		if ( result < 0 )
		{
			ERROR("Varr_for_each", "problem with exec func")
			printf ( "On [%d] Elem_of_Array result = %d"\
							, i, result );
			errno = EINVAL; 
			return -1;
		}
	}

	errno = 0;
	return 0;
}

//********************************************************************
