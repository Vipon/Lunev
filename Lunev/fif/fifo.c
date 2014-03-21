#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO1 "Fifo"
#define FIFOWS "Write_Synchronization"
#define FIFORS "Read_Synchronization"
#define MAXLINE 1024



int main ( int argc, char *argv[] )
{
	int Fifo = 0;
	int Fifows = 0;
	int Fifors = 0;
	int Write_Fd = 0;
	int Read_Fd = 0;
   	char buff = 0;
		
	switch ( argv[1][0] ) 
	{
	case 'r':	//open output File and check
			Write_Fd = open ( argv[2], O_RDWR | O_CREAT, 0644 );  
			if ( Write_Fd <= 0 )
			{
				printf ( "ERROR, Don't open output File!\n" );
				return -1;
			} 
			
			do {
				if ( ( mkfifo ( FIFORS, 0644 ) < 0 ) && ( errno != EEXIST ) )
				{
					close ( Write_Fd );			
					printf ( "can't create %s\n", FIFOWS );
					return -1;
				}
				
				if ( errno == EEXIST )
				{
					Fifors = open ( FIFORS, O_WRONLY | O_NDELAY ); 
					
					if ( Fifors <= 0 )
					{
						unlink ( FIFORS );	
						unlink ( FIFO1 );
						unlink ( FIFOWS );								
					}
					else
						close ( Fifors );
					errno = EEXIST;
				}
				else
					Fifors = open ( FIFORS, O_RDONLY | O_NDELAY );
	
			} while ( ( errno == EEXIST ) );
			
			//open Fifo for Read and ckeck 	
			do {
				Fifo = open ( FIFO1, O_RDONLY );
			} while ( Fifo <= 0 );
			{			
				while (	read ( Fifo, &buff, 1 ) > 0 ) 	
					write ( Write_Fd, &buff, 1 );
			}
			close ( Write_Fd );
			close ( Fifo );
			close ( Fifors );	
			unlink ( FIFORS );	
	break;
	case 'w':	//open input File and Check
			Read_Fd = open ( argv[2], O_RDONLY );
			if ( !Read_Fd )
			{
				printf ( "ERROR, Don't open input File!\n" );
				return -1;
			} 
			
			//creat FIFOWS and Check
			do {
				errno = 0;
				if ( ( mkfifo ( FIFOWS, 0644 ) < 0 ) && ( errno != EEXIST ) )
				{
					close ( Read_Fd );			
					printf ( "can't create %s\n", FIFOWS );
					return -1;
				}
				if ( errno == EEXIST )
				{
					Fifows = open ( FIFOWS, O_WRONLY | O_NDELAY );
					
					if ( Fifows <= 0 )
					{
						unlink ( FIFO1 );
						unlink ( FIFOWS );
						unlink ( FIFORS );
					}
					else
						close ( Fifows );
						
					errno = EEXIST;	
				}
				else
				{
					Fifows = open ( FIFOWS, O_RDONLY | O_NDELAY );
				}

			} while ( ( errno == EEXIST ) || ( errno == ENOENT ) );
			
			do {
				errno = 0;
				if ( ( mkfifo ( FIFO1, 0644 ) < 0 ) && ( errno != EEXIST ) )
				{
					close ( Read_Fd );			
					printf ( "can't create %s\n", FIFO1 );
					return -1;
				}
			} while ( errno == EEXIST );

			
			//open Fifo for write and Check
			Fifo = open ( FIFO1, O_WRONLY );
			
			if ( Fifo <= 0 )
			{
				close ( Read_Fd );	
				printf ( "Fifo ERROR\n" );
				return -1;
			}
	
					
			{
				while ( read ( Read_Fd, &buff, 1 ) > 0 )
	    				write ( Fifo, &buff, 1 );
					
			}
			unlink ( FIFOWS );			
			close ( Read_Fd );
			close ( Fifo );
			close ( Fifows );
			unlink ( FIFO1 );
	break;
	default :
	break;	
	}
	
	return 0;
}
