#define BUFFERSISE 2048

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main ( int args, char* argv[] )
{
	char buffer[BUFFERSISE] = {};	
	int input = 0;
        int output = 0;
	int count = 0;

	if ( argv[1] == NULL  )                                                 //Chech and open the file 
	{                                                                       //       
		printf ( "You didn't enter input and output file\n" );          // 
		return 0;                                                       //       
	}                                                                       //
	                                                                        //         
        input = open ( argv[1], O_RDONLY ); 	                                //
	if ( input == -1 )                                                      //
	{                                                                       //
		printf ( "Input File incorrect\n" );                            //
		return 0;                                                       //
	}                                                                       //
	
         
        if ( argv[2] == NULL )
	{
		close ( input );
		printf ( "Please, Enter the output File\n" );
		return 0;
	}
	
        FILE * out = fopen ( argv[2], "w" );
        fclose ( out );
        output = open ( argv[2], O_WRONLY | O_CREAT   ); 
        
	if ( output == -1 )
	{
               printf ( "Output File incorrect\n" );
	       return 0;
       	}
	
	do
	{
               	count = read ( input, &buffer, BUFFERSISE );
		if ( write ( output, &buffer, count ) < 0)
		{
      			printf( "Failed to write to  file \"%s\".\n", argv[2] );
			return 0;   
       		 };	
	}
	while ( count > 0 );

	close ( input );
        close ( output );

	return 0;
}
