#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define BUFFER_SIZE 4096

int main(int argc,char** argv)
{
     char *buf = malloc(BUFFER_SIZE);
     time_t t=time(0);
     strftime(buf,BUFFER_SIZE,"%c\n",localtime(&t));
     printf(buf);
     return 0;
}
