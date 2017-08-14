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
int execute(char **tokens)
{
	int x,fl=0,fl1=0,fd,fl2=0,d,e,f,g,h,fl3=0,j,k,fl4=0,l,m,fl5=0,n,o,p;
	pid_t pid, waitpidi;
	int status,checker=0;
	int i;
	char output[10000],input[10000],output1[10000],fg[10000],kjob1[100],kjob2[100];
	for(i=1;tokens[i]!=NULL;i++)
	{
		if(tokens[i][0]=='&' && tokens[i][1]=='\0')
		{
			fl=1;
			d=i;
			break;
		}
		if(tokens[i][0]=='>' && tokens[i][1]=='\0')
		{
			fl1=1;
			f=i;
			if(tokens[i+1]!=NULL)
			{
				strcpy(output,tokens[i+1]);
				g=i+1;
			}
			else
			{
				fprintf(stderr,"syntax error near unexpected token `newline'\n");
				return 1;
			}
		}
		if(tokens[i][0]=='>' && tokens[i][1]=='>' && tokens[i][2]=='\0')
		{
			fl3=1;
			j=i;
			if(tokens[i+1]!=NULL)
			{
				strcpy(output1,tokens[i+1]);
				k=i+1;
			}
			else
			{
				fprintf(stderr,"syntax error near unexpected token `newline'\n");
				return 1;
			}

		}
		if(tokens[i][0]=='<' && tokens[i][1]=='\0')
		{
			fl2=1;
			h=i;
			if(tokens[i+1]!=NULL)
			{
				e=i+1;
				strcpy(input,tokens[i+1]);
			}
			else
			{
				fprintf(stderr,"syntax error near unexpected token `newline'\n");
				return 1;
			}

		}
	}
	if(fl==1)
	{
		tokens[d]=NULL;
	}
	if(fl1==1)
	{
		tokens[f]=NULL;
		if(tokens[f+1]!=NULL)
		{
			tokens[g]=NULL;
		}
	}
	if(fl2==1)
	{
		tokens[h]=NULL;
		if(tokens[h+1]!=NULL)
		{
			tokens[e]=NULL;
		}
	}
	if(fl3==1)
	{
		tokens[j]=NULL;
		if(tokens[j+1]!=NULL)
		{
			tokens[k]=NULL;
		}
	}
	if(tokens[0][0]=='f' && tokens[0][1]=='g' && tokens[0][2]=='\0')
	{
		if(tokens[1]!=NULL)
		{
			strcpy(fg,tokens[1]);
			fl4=1;
		}
		else
		{
			fprintf(stderr,"fg: current: no such job\n");
			return 1;
		}
	}
	pid = fork();
	currpid=pid;
	strcpy(currname,tokens[0]);
	if (pid == 0) 
	{
		if(fl3==1)
		{
			fd = open(output1, O_WRONLY | O_APPEND | O_CREAT,0644);
			dup2(fd, STDOUT_FILENO);
			fd = dup(1);
		}
		if(fl1==1)
		{
			fd = creat(output, 0644);
			dup2(fd, STDOUT_FILENO);
			fd = dup(1);
		}
		if(fl2==1)
		{
			fd = open(input, O_RDONLY, 0);
			dup2(fd, STDIN_FILENO);
			fd = dup(0);
		}
		x=execvp(*tokens,tokens);
		if(x==-1 && fl4!=1)
		{
			fprintf(stderr,"Command Not Found\n");
		}
		exit(EXIT_FAILURE);
	} 
	else if (pid < 0) 
	{
		perror("ERROR!!");
	}
	else 
	{
		if(fl==1)
		{
			u=tokens[0];
			a[global]=global+1;
			strcpy(b[global],tokens[0]);
			c[global]=pid;
			global++;
			printf("[%d]\n",pid);
			signal(SIGCHLD,sigh);
			return 1;
		}
		else if(fl4==1)
		{
			for(i=initial;i<global;i++)
			{
				if(a[i]==atoi(fg))
				{
					printf("%s\n",b[i]);
   					a[i]=-1;
					checker=1;
					kill(c[i],SIGCONT);
					waitpid(c[i],&i,WCONTINUED);
					break;
				}
			}
			if(checker==0)
			{
				fprintf(stderr,"No such job ID\n");
			}
		}
		else
		{
			waitpidi = waitpid(pid, &status, WCONTINUED);
			/*waitpidi = waitpid(pid, &status, WUNTRACED);
			while (WIFEXITED(status)!=0 && WIFSIGNALED(status)!=0)
			{
				waitpidi = waitpid(pid, &status, WUNTRACED);
			}*/
		}
	}	
	return 1;
}

