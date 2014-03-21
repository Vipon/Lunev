#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

 
int get ( int args, char* argv[] );
            
int main ( int args, char* argv[] )
{
	int num = get ( args, argv );
	int i = 0;
	int pid = 0;
        int stat = 0;

	for ( i = 0; i < num; ++i )
	{
		pid = fork ();
                if ( pid < 0 )
                {       
                        printf ( "Fail #%d fork ()\n", i );
                        return -1;
                }
                if ( !pid )
                {
                        printf ( "#%d pid = %d\n", i, getpid() ); 
                        return 0;                
                }
                wait ( &stat );
	} 
	return 0;  
}
