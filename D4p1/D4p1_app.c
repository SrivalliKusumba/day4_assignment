#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
	int fd;

	fd = open("/dev/mychar",O_RDWR,0777);
	
	if(fd<0)
	{
		printf("Error\n");
		exit(1);
	}

	printf("\n the file open call is successful\n");
	close(fd);
	return 0;
}
