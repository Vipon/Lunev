#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int  main(int argc, char *argv[])
{

int pipefd[2];
int fileid;
pid_t cpid;
char buf;
char buf2;

if (argc != 2) 
	{
	fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
	exit(EXIT_FAILURE);
	}
if (pipe(pipefd) == -1) 
	{
	perror("pipe");
	exit(EXIT_FAILURE);
	}

cpid = fork();

if (cpid == -1) 
	{
	perror("fork");
	exit(EXIT_FAILURE);
	}

if (cpid == 0) 
	{ 
	fileid = open(argv[1],O_RDONLY);
	close(pipefd[0]);          /* Close unused read end */
	while (read(fileid,&buf2,1)>0)
	write(pipefd[1], &buf2, 1);
	close(pipefd[1]);          /* Reader will see EOF */
//	wait(NULL);                /* Wait for child */
//	printf("!!!!! %d\n",errno);
	exit(EXIT_SUCCESS);
	}
	else 
	{
	close(pipefd[1]);          /* Close unused write end */
	while (read(pipefd[0], &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);
	write(STDOUT_FILENO, "\n", 1);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
	}
 
return 0;
}

