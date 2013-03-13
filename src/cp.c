#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main(int argc,char** argv)
{
     if(argc<3)exit(0);
     int fdrd,fdwr;
     if((fdrd = open(argv[1],O_RDWR))<0)
     {
          printf("open source file failed!\n");
          exit(0);
     }
     if((fdwr=open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0666))<0)
     {
          printf("open target file failed!\n");
          exit(0);
     }
     char *buf = malloc(BUFFER_SIZE);
     int size;
     while((size=read(fdrd,buf,BUFFER_SIZE))==BUFFER_SIZE)
          write(fdwr,buf,BUFFER_SIZE);
     write(fdwr,buf,BUFFER_SIZE);
     close(fdrd);
     close(fdwr);
     return 0;
}













