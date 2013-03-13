#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 4096

void rmdirfiles(char* path)
{
     
}

int main(int argc,char** argv)
{
     char* path = argv[1];
     char* captcha=malloc(5);
     char* sure=malloc(20);
     printf("romve %s , you sure ?[y/n]:",path);
     scanf("%s",sure);
     if(sure[0]!='Y'&&sure[0]!='y')exit(0);
     srand(time(NULL));
     char  CAPTCHA[5];
     while(1)
     {
          CAPTCHA[0] = rand()%94+33;
          CAPTCHA[1] = rand()%94+33;
          CAPTCHA[2] = rand()%94+33;
          CAPTCHA[3] = rand()%94+33;
	  CAPTCHA[4] = 0;
          printf("please enter the captcha |%s| :",CAPTCHA);
          scanf("%s",captcha);
          if(!strcmp(captcha,CAPTCHA))break;
     }
     remove(path);
     return 0;
}
