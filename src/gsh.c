#define MSG "\
 * I have achieved basic shell command and function. \n\                       
 * Internal Command: cd exit \n\
 * External Command: cp rm rmdir ln echo pwd cat touch date kill ls(with -al) \n\
 * Function: MultiPipe,RedirectIO(By Recursive)\n\
 * There's not so many command but you can use commands provided by system.\n\
 * Just copy them such as sort grep less etc. to this dictionary(gsh).\n"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX_ADDR_LEN 256
#define MAX_CMD_LEN 1024
#define MAX_ARG_CNT 5

int stdin_fd,stdout_fd;
char* base_path;

void execute_cmd(char* cmd)
{
     int i;
     char* arg[5];
     for(i=0;i<5;i++)arg[i]=malloc(256);
     i=sscanf(cmd,"%s%s%s%s",arg[0],arg[1],arg[2],arg[3]);
     arg[i]=0;
     if(execv(arg[0],arg)<0)//if not in current dir,search base dir.
     {
      	char* path = malloc(MAX_ADDR_LEN);
        strcpy(path,base_path);
        if(strcmp(path,"/"))strcat(path,"/");
        strcat(path,arg[0]);
        if(execv(path,arg)<0)
        {
	     printf("command not found!\n");
	     exit(0);
        }
     }
}
/* If there's a pipe(|) or redirectIO(><) 
 * fork a child process to execute command before |
 * and link the child's pipeout to parent's pipein
 * and recursive parse the surplus.
 * else fork a child process to execute 
 * and relink parent's pipeout to standard out.
 */
void parse_cmd(char* cmd)
{
     char* split;
     if(split=strpbrk(cmd,"|<>"))
     {
          if((*split) == '|')
          {
               *split=0;
               int fd[2];
               pipe(fd);
               if(fork() == 0)
               {
                    close(fd[0]);
                    close(STDOUT_FILENO);
                    dup(fd[1]);
                    execute_cmd(cmd);
               }
               else
               {
                    close(fd[1]);
                    close(STDIN_FILENO);
                    dup(fd[0]);
                    parse_cmd(split+1);
               }
          }
          else if((*split) == '>')//after > must the filename
          {
               *split   = 0;
               char* filename=malloc(MAX_ADDR_LEN);
               sscanf(split+1,"%s",filename);
               int fd = open(filename,O_RDWR|O_CREAT,0666);
               close(STDOUT_FILENO);
               dup(fd);
               parse_cmd(cmd);
          }
          else//after < may not filename such as "#sort<a.txt>b.txt"
          {
               *split   = 0;
	       char* sp2;
	       char* filecmd=malloc(MAX_ADDR_LEN);
               if(sp2=strpbrk(split+1,"|<>"))
	       {
	          char tmp=*sp2;
	          *sp2 =0;
		  strcpy(filecmd,split+1);
		  *sp2=tmp;
		  strcat(cmd,sp2);
	       }
	       else strcpy(filecmd,split+1);

               char* filename=malloc(MAX_ADDR_LEN);
               sscanf(filecmd,"%s",filename);
               int fd = open(filename,O_RDWR|O_CREAT,0666);
               close(STDIN_FILENO);
               dup(fd);
               parse_cmd(cmd);
               return;
          }
           
     }
     else
     {
          int pid;
          if((pid=fork()) == 0)execute_cmd(cmd);
          else
          {
               close(STDIN_FILENO);
               close(STDOUT_FILENO);
               dup(stdin_fd);
               dup(stdout_fd);
               waitpid(pid,0,0);
          }
     }
     return ;
}

int main (int argc,char** argv)
{
     printf(MSG);
     stdin_fd   = dup(STDIN_FILENO);
     stdout_fd  = dup(STDOUT_FILENO);
     char* cmd  = malloc(MAX_CMD_LEN);
     char* buf  = malloc(MAX_CMD_LEN);
     char* path = malloc(MAX_ADDR_LEN);
     base_path   = malloc(MAX_ADDR_LEN);
     getcwd(base_path,MAX_ADDR_LEN);
     while(1)
     {
          printf("[Gsh:%s]$",getcwd(path,MAX_ADDR_LEN));
          fgets(cmd,MAX_CMD_LEN,stdin);
	  int ac=sscanf(cmd,"%s%s",buf,path);//check internal command
          if(!strcmp(buf,"exit"))exit(0);
          if(!strcmp(buf,"cd"))
	  {
		if(ac!=2)continue;
		chdir(path);
		continue;
	  }
          parse_cmd(cmd);
     }
     exit(0);
}









