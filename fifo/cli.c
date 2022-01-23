#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int w_fifo;
	char str[] = "This is Client's message!\n";

	if((w_fifo = open("fifo", O_WRONLY)) < 0)
	{
		perror("Error open w_fifo:");
		return 1;
	}

	write(w_fifo, str, strlen(str) + 1);
	close(w_fifo);	
	return 0;
}
