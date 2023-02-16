#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
int fd=open(argv[1],O_RDWR);
if(-1==fd)
{
printf("Can‘t open!\n");
return -1;
}
printf("Open OK!\n");
return 0;
}
