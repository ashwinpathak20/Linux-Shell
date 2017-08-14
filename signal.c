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
void sigstop(int sig_num)
{
	kill(currpid,20);
	kill(currpid,18);
	c[global]=currpid;
	strcpy(b[global],currname);
	a[global]=global+1;
	global++;
	printf("\n");
}
void sigh(int signum)
{
	pid_t wpid;
	int status,i;
	char x[1000];
	wpid=waitpid(-1,&status,WNOHANG);
	if(wpid>0)
	{
		if(WIFEXITED(status)==0)
		{
			for(i=initial;i<global;i++)
			{
				if(c[i]==wpid)
				{
					strcpy(x,b[i]);
					a[i]=-1;
					printf("\n%s with pid %d because of a signal\n",x,wpid);
				}
			}
		}
		if(WIFSIGNALED(status)==0)
		{
			for(i=initial;i<global;i++)
			{
				if(c[i]==wpid)
				{
					strcpy(x,b[i]);
					a[i]=-1;
					printf("\n%s with pid %d because of a signal\n",x,wpid);
				}
			}
		}
	}
	
}

