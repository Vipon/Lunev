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
	if ( Varr <= 0 )
	{
		ERROR("construct", "memory for Varr isn't allocation");
		errno = ENOMEM;
		return NULL;
	}
		
	Varr -> length = len;
	Varr -> array = (Elem_of_Array*) calloc ( len , sizeof(Elem_of_Array) );
	if ( Varr -> array <= 0 )
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
	if ( Varr <= 0 )
	{
		ERROR("insert", "*Varr isn't valid" );
		errno = EBADR;
		return -1;
	}
	if ( elem <= 0 )
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
	if ( Varr <= 0 )
	{
		ERROR("insert", "*Varr isn't valid" );
		errno = EBADR;
		return -1;
	}
	
	free ( Varr -> array );	
	Varr -> array = (Elem_of_Array*) malloc ( nLen * sizeof(Elem_of_Array) );

	if ( Varr -> array <= 0 )
	{
		ERROR("relen", "memory for Varr -> array isn't allocation");
		errno = ENOMEM;
		return -1;
	}
	
	Varr -> length = nLen;
	Varr -> end = &(Varr -> array[nLen-1]);
	errno = 0;
	return 0;	
}

//*********************************************************************

int destroy ( V_VarLArray *Varr )
{
	if ( Varr <= 0 )
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
	if ( source <= 0 )
	{
		ERROR("copy", "*source isn't valid");
		errno = EBADR;
		return -1;
	}
	if ( destination <= 0 )
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
	if ( elem <= 0 )
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
	if ( elem <= 0 )
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
	if ( Varr <= 0 )
	{
		ERROR("dump", "*Varr isn't valid");
		errno = EBADR;
		return -1;
	}

	errno = 0;
	return Varr -> length;	
}
/*
//*********************************************************************

Elem_of_Array *start ( V_VarLArray *Varr )
{
	if ( Varr <= 0 )
	{
		ERROR("start", "*Varr isn't valid");
		return NULL;
	}

	return Varr -> array;	
}

//*********************************************************************

Elem_of_Array *end ( V_VarLArray *Varr )
{
	if ( Varr <= 0 )
	{
		ERROR("end", "*Varr isn't valid");
		return NULL;
	}

	return Varr -> end;	
}

//*********************************************************************
*/
Elem_of_Array *take ( V_VarLArray *Varr, unsigned int num )
{
	if ( Varr <= 0 )
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
/*
Elem_of_Array *next ( V_VarLArray *Varr, unsigned int num )
{
	if ( Varr <= 0 )
	{
		ERROR("next", "*elem isn't valid`");
		return NULL;
	}
	if ( num >= Varr -> length )
	{
		ERROR("next", "num > length of array");
		return NULL;
	}
	if ( num + 1 == Varr -> length )
	{
		ERROR("next", "you have already been in the end");
		return Varr -> end;
	} 
	
	return &(Varr -> array[num+1]);
}

//*********************************************************************

Elem_of_Array *prev ( V_VarLArray *Varr, unsigned int num )
{
	if ( Varr <= 0 )
	{
		ERROR("prev", "*elem isn't valid");
		return NULL;
	}
	if ( num >= Varr -> length )
	{
		ERROR("prev", "num > length of array");
		return NULL;
	}
	if ( !num )
	{
		ERROR("prev", "you have already been in the start");
		return Varr -> array;
	} 
	
	return &(Varr -> array[num-1]);
}

//*********************************************************************
*/
int Varr_for_each ( V_VarLArray *Varr, void *buf,\
		    int (*func) ( Elem_of_Array *elem, void *buf ) )
{
	if ( Varr <= 0 )
	{
		ERROR("Varr_for_each", "*Varr isn't valid");
		errno = EBADR;
		return -1;
	}
	if ( func <= 0 )
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
