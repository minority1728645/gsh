#include <unistd.h>
#include <stdio.h>

int main(int argc,char** argv)
{
     if(argc==1)exit(0);
     if(rmdir(argv[1])<0)printf("romve dictionary failed!\n");
     return 0;
}
