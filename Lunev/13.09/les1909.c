#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


int main ( int argv, char* argc[] )
{
	int fd[2];
	int f;
	char buf = 0;
		
	if ( pipe ( fd ) == -1 ) 
        {
               perror ( "pipe" );
               exit ( EXIT_FAILURE );
        }

	int pid = fork ();
	if ( pid == -1 ) 
        {
              perror ( "fork" );
              exit ( EXIT_FAILURE );
        }
	
        if ( pid == 0 ) 
        {   
 		f = open ( argc[1], O_RDONLY );
               	close(fd[0]); 
		
                while ( read ( f, &buf, 1 ) > 0 )
                   write ( fd[1], &buf, 1 );
               
            	close ( fd[1] );

             	exit ( EXIT_SUCCESS );         
     	} 
        else 
        {    
                close ( fd[1] );            
               	
                while ( read ( fd[0], &buf, 1 ) > 0 )
                	write ( STDOUT_FILENO, &buf, 1 );

          
               	wait ( NULL );  
               	close ( fd[0] );
             	exit ( EXIT_SUCCESS );
        } 
	return 0;
}
