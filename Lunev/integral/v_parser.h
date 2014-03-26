//**************//
//Maked by Vipon//
//**************//


#ifndef V_PARSER
#define V_PARSER

typedef struct atribut{

	double 	X;
	double	Y;
	unsigned pos;

} atribut;

double Calculate ( char *func, atribut *atr );
double GetN  ( char *func, atribut *atr );
double GetE  ( char *func, atribut *atr );
double GetT  ( char *func, atribut *atr );
double GetP  ( char *func, atribut *atr );
double GetEF ( char *func, atribut *atr );

#endif //V_PARSER

