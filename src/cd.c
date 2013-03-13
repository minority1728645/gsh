#include <unistd.h>
#include <stdio.h>

int main(int argc,char** argv)
{
     if(argc==1)exit(0);
     if(chdir(argv[1])<0)printf("cd failed!\n");
     return 0;
}
