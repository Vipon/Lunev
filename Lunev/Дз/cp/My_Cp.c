#define BUFFERSISE 2048

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main ( int args, char* argv[] )
{
	char buffer[BUFFERSISE] = {};	
	int count = 0;

	if ( argv[1] == NULL  )                                                 //Chech and open the file 
	{                                                                       //       
		printf ( "You didn't enter input and output file\n" );          // 
		return 0;                                                       //       
	}                                                                       //
	                                                                        //         
        FILE* input = fopen ( argv[1], "rb" ); 	                                //
	if ( !input )                                                           //
	{                                                                       //
		printf ( "Input File incorrect\n" );                            //
		return 0;                                                       //
	}                                                                       //  
         
        if ( argv[2] == NULL )
	{
		fclose ( input );
		printf ( "Please, Enter the output File\n" );
		return 0;
	}
	
        FILE * output = fopen ( argv[2], "wb+" );       
	if ( !output )
	{      
                fclose ( input );
                printf ( "Output File incorrect\n" );
	        return 0;
       	}
	
	do
	{
               	count = fread ( &buffer, sizeof ( char ), BUFFERSISE, input );
		if ( fwrite ( &buffer, sizeof ( char ), count, output ) < 0)
		{
      			printf( "Failed to write to  file \"%s\".\n", argv[2] );
			return 0;   
       		};	
	}
	while ( count > 0 );
        
        char *endpointer;
        chmod( argv[2], strtol( "0777", &endpointer, 8 ) );
	
        fclose ( input );
        fclose ( output );

	return 0;
}
