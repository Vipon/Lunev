#include <pthread.h>
#include <stdio.h>

int get ( int argc, char *argv[] );
void *proc ( void* i );

int main ( int argc, char *argv[] )
{
	int n = get ( argc, argv );
	int i = 0;
	int result = 0;
	pthread_t tread;

	for ( ; i < n; ++i)
	{
		result = pthread_create ( &tread, NULL, &proc , (void *)( i ) );
		if ( result )
		{
			printf ( "Fail #%dcreate\n", i );
			return -1;
		}
		
					
	}
	pthread_join ( tread, result ); 	
	return 0;
}

void* proc ( void *i )
{
	printf ( "HI! %d\n", (int)( i ) );
	pthread_exit (i);
} 
