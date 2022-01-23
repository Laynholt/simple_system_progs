#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 100

int main()
{
	int r_fifo;
    char buf[BUF_SIZE];

	//delete fifo file, if it exist
	unlink("fifo");

	//create fifo file 
	if((mkfifo("fifo", 0666 | S_IFIFO)) == -1)
	{
		perror("Error mkfifo: ");
        return 1;
	}

	//open fifo on read
	if((r_fifo = open("fifo", O_RDONLY)) < 0)
	{
		perror("Error open r_fifo: ");
        return 1;
	}

	//read fifo
	read(r_fifo, &buf, BUF_SIZE);
    printf("Messange: %s\n", buf);

    //close fifo
	close(r_fifo);
	//delete fifo
	unlink("fifo");
	return 0;
}
