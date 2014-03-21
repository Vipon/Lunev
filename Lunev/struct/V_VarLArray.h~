#ifndef V_VarLArray_H_
#define V_VarLArray_H_

//*********************************************************************

typedef struct Elem_of_Array {
	
	char data;
	
} Elem_of_Array;

//*********************************************************************

typedef struct V_VarLArray {
	
	unsigned int length;
	Elem_of_Array *array;
	Elem_of_Array *end;

} V_VarLArray;

//********************************************************************

V_VarLArray* construct ( unsigned int len );

int insert ( V_VarLArray *Varr, unsigned int pos, Elem_of_Array *elem );
int resize ( V_VarLArray *Varr, unsigned int nLen );
int destroy ( V_VarLArray *Varr );
int copy ( Elem_of_Array *source, Elem_of_Array *destination );
int clear ( Elem_of_Array *elem );
int print ( Elem_of_Array *elem );
int getSize ( V_VarLArray *Varr );

//Elem_of_Array *start ( V_VarLArray *Varr );
//Elem_of_Array *end ( V_VarLArray *Varr ); 
Elem_of_Array *take ( V_VarLArray *Varr, unsigned int num );
//Elem_of_Array *next ( V_VarLArray *Varr, unsigned int num );
//Elem_of_Array *prev ( V_VarLArray *Varr, unsigned int num );

int Varr_for_each ( V_VarLArray *Varr, void *buf,\
		    int (*func) ( Elem_of_Array *elem, void *buf ) );
//********************************************************************

#endif //V_VarLArray_H_
