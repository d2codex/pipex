#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	main(void)
{
	int	pipefd[2];
	
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("pipefd[0] = %d\n", pipefd[0]);
	printf("pipefd[1] = %d\n", pipefd[1]);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
