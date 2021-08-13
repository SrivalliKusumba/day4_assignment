#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int fd;
	char Ubuff[] = "User to kernel";
	char kbuff[100];
	fd = open("/dev/mychar",O_RDWR,0777);
	if(fd < 0)
	{
		printf("Error opening file\n");
		exit(1);
	}
	write(fd,Ubuff,sizeof(Ubuff));
	read(fd,kbuff,100);
	printf("Data read from kernel %s \n",kbuff);
	close(fd);
	return 0;
}
