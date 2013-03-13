#include <unistd.h>
#include <stdio.h>

int main(int argc,char** argv)
{
     if(argc==1)exit(0);
     if(mkdir(argv[1],0666)<0)printf("make dictionary failed!\n");
     return 0;
}
