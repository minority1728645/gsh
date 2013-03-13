#include <unistd.h>
#include <stdio.h>
#include <signal.h>


int main(int argc,char** argv)
{
     if(argc<2)exit(0);
     kill(atol(argv[1]),SIGKILL);
     return 0;
}
