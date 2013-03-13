#include <unistd.h>
#include <stdio.h>


int main(int argc,char** argv)
{
     if(argc==3)
     {
          if(link(argv[1],argv[2])<0)
               printf("link failed!\n");
          exit(0);          
     }
     if(argc==4)
     {
          if(argv[1][1]!='L')
          {
               printf("unknow parameter : %s !\n",argv[1]);
               exit(0);
          }
          if(symlink(argv[2],argv[3])<0)
               printf("link failed!\n");
          exit(0);
     }
     return 0;
}
