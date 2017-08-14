#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/utsname.h>
#include "function.h"
int pipes(char **tokens)
{
	int i,stat,s;
	pid_t pid,ppid;
	int k,fd[2],l;
	char *token;
	char **t1;
	k=0;
	for(i=0;tokens[i+1]!=NULL;i++)
	{
		token=tokens[i];
		int fl1=0,fl3=0,fl2=0,g,y,z,j,h,e,filedesc,f;
		char output[10000],input[10000],output1[10000];
		pipe(fd);
		t1=tokenize1(token," \n");
		for(j=0;t1[j]!=NULL;j++)
		{
			if(t1[j][0]=='>' && t1[j][1]=='\0')
			{
				fl1=1;
				f=j;
				if(t1[j+1]!=NULL)
				{
					strcpy(output,t1[j+1]);
					g=j+1;
				}
				else
				{
					fprintf(stderr,"syntax error near unexpected token `newline'\n");
					return 1;
				}

			}
			if(t1[j][0]=='>' && t1[j][1]=='>' && t1[j][2]=='\0')
			{
				fl3=1;
				z=j;
				if(t1[j+1]!=NULL)
				{
					strcpy(output1,t1[j+1]);
					y=j+1;
				}
				else
				{
					fprintf(stderr,"syntax error near unexpected token `newline'\n");
					return 1;
				}

			}
			if(t1[j][0]=='<' && t1[j][1]=='\0')
			{
				fl2=1;
				h=j;
				if(t1[j+1]!=NULL)
				{
					e=j+1;
					strcpy(input,t1[j+1]);
				}
				else
				{
					fprintf(stderr,"syntax error near unexpected token `newline'\n");
					return 1;
				}

			}
		}
		if(fl1==1)
		{
			t1[f]=NULL;
			if(t1[f+1]!=NULL)
			{
				t1[g]=NULL;
			}
		}
		if(fl2==1)
		{
			t1[h]=NULL;
			if(t1[h+1]!=NULL)
			{
				t1[e]=NULL;
			}
		}
		if(fl3==1)
		{
			t1[j]=NULL;
			if(t1[j+1]!=NULL)
			{
				t1[y]=NULL;
			}
		}
		l=fd[1];
		pid=fork();
		if(pid==0)
		{
			if(k!=0)
			{
				dup2(k,0);
				close(k);
			}
			if(l!=1)
			{	
				dup2(l,1);
				close(l);
			}
			if(fl3==1)
			{
				filedesc = open(output1, O_WRONLY | O_APPEND | O_CREAT,0644);
				dup2(filedesc, STDOUT_FILENO);
				filedesc = dup(1);
			}
			if(fl1==1)
			{
				filedesc = creat(output, 0644);
				dup2(filedesc, STDOUT_FILENO);
				filedesc = dup(1);
			}
			if(fl2==1)
			{
				filedesc = open(input, O_RDONLY, 0);
				dup2(filedesc, STDIN_FILENO);
				filedesc = dup(0);
			}
			//close(filedesc);
			e=execvp(t1[0],t1);
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		k=fd[0];
	}
	if(k!=0)
	{
		dup2(k,0);
	}
	if(i!=0)
	{
		token=tokens[i];
		t1=tokenize1(token," \n");
		s=execute(t1);
	}
	else
	{
		fprintf(stderr,"INvalid Command\n");
	}
}
