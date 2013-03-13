#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_ADDR_LEN 256
#define BUFFER_SIZE 4096

void mode_format( int mode , char* str )
{
    strcpy(str,"----------");
    if ( S_ISDIR(mode) )  str[0] = 'd';    
    if ( S_ISCHR(mode) )  str[0] = 'c';  
    if ( S_ISBLK(mode) )  str[0] = 'b';   
    if ( mode & S_IRUSR ) str[1] = 'r'; 
    if ( mode & S_IWUSR ) str[2] = 'w';
    if ( mode & S_IXUSR ) str[3] = 'x';
    if ( mode & S_IRGRP ) str[4] = 'r'; 
    if ( mode & S_IWGRP ) str[5] = 'w';
    if ( mode & S_IXGRP ) str[6] = 'x';
    if ( mode & S_IROTH ) str[7] = 'r'; 
    if ( mode & S_IWOTH ) str[8] = 'w';
    if ( mode & S_IXOTH ) str[9] = 'x';
}

int main(int argc,char** argv)
{
     char* path = malloc(MAX_ADDR_LEN);
     getcwd(path,MAX_ADDR_LEN);
     int l=0,a=0;
     if(argc == 2)
     {
          if(argv[1][0]!='-')
               path = argv[1];
          else
          {
               if (strchr(argv[1],'l') != 0)
                    l = 1;
               if (strchr(argv[1],'a') != 0)
                    a = 1;
          }
     }
     else if(argc==3)
     {
          path = argv[2];
           if (strchr(argv[1],'l'))
                l = 1;
           if (strchr(argv[1],'a'))
                a = 1;
     }
     DIR*  dir;
     if(!(dir=opendir(path)))
     {
          printf("open dictionary failed!\n");
          exit(0);
     }
     struct dirent *rddir;
     while(rddir=readdir(dir))
     {
          if((rddir->d_name)[0] == '.'&&!a)continue;
          if(!l)printf("%s\t",rddir->d_name);
          else
          {
               struct stat state;
               lstat(rddir->d_name,&state);
               char *change_time = malloc(BUFFER_SIZE);
               strftime(change_time,BUFFER_SIZE,"%F %H",localtime(&(state.st_mtime)));
	       char *buf=malloc(11);
	       mode_format(state.st_mode,buf);
               printf("%s\t%s\t%ld\t",buf,change_time,state.st_size);
	       printf("%s \n",rddir->d_name);//I don't know why,but once I write these together,minix will not show it's name,though linux works well.
          }
     }
     printf("\n");
     closedir(dir);
     return 0;
}
