#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char** argv)
{
     if(argc==1)exit(0);
     int fd;
     if((fd = open(argv[1],O_RDWR|O_CREAT,0666))<0)
     {
          printf("touch file failed!\n");
          exit(0);
     }
     close(fd);
     utime(argv[1],0);
     return 0;
}
