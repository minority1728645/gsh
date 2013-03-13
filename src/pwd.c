#include <unistd.h>
#include <stdio.h>

#define MAX_ADDR_LEN 256

int main(int argc,char** argv)
{
     char* path = malloc(MAX_ADDR_LEN);    
     printf("%s\n",getcwd(path,MAX_ADDR_LEN));
     return 0;
}
