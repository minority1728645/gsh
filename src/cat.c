#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main(int argc,char** argv)
{
     if(argc==1)exit(0);
     int fd;
     if((fd = open(argv[1],O_RDONLY))<0)
     {
          printf("open file failed!\n");
          exit(0);
     }
     char *buf = malloc(BUFFER_SIZE);
     while(BUFFER_SIZE==read(fd,buf,BUFFER_SIZE))write(STDOUT_FILENO,buf,BUFFER_SIZE);
     write(STDOUT_FILENO,buf,BUFFER_SIZE); 
      
     close(fd);
     return 0;
}
