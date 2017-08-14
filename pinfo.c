#include <stdio.h>
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
void pinfo(char **t1)
{
	int fl=0,d,i,j,h=0;
	char string4[1000],string5[1000],ex[1000];
	char *pid,*temp,*check,*mem;
	pid=(char *)malloc(1000*sizeof(char));
	temp=(char *)malloc(1000*sizeof(char));
	check=(char *)malloc(1000*sizeof(char));
	mem=(char *)malloc(1000*sizeof(char));
	if(t1[1]!=NULL)
	{
		strcpy(pid,t1[1]);
		fl=1;
	}
	else
	{
		d=getpid();
		j=d;
		while(j!=0)
		{
			h++;
			j=j/10;
		}
		j=d;
		for(i=h-1;i>=0;i--)
		{
			temp[i]=(j%10+'0');
			j=j/10;
		}
		temp[h]='\0';
	}
	if(t1[1]!=NULL)
	{
		printf("pid -- %s\n", pid);
	}
	else
	{
		printf("pid -- %s\n",temp);
	}
	printf("Process Status -- "); 
	fflush(stdout);
	strcpy(check,"ps -o stat= -p ");
	if(t1[1]!=NULL)
	{
		strcat(check,pid);
	}
	else
	{
		strcat(check,temp);
	}
	t1=tokenize1(check," ");
	execute(t1);
	printf("Memory --"); 
	fflush(stdout);
	strcpy(mem, "ps -o vsz= -p ");
	if(fl==1)
	{
		strcat(mem,pid);
	}
	else
	{
		strcat(mem,temp);
	}
	t1=tokenize1(mem," ");
	execute(t1);
	strcpy(string4, "/proc/");
	if(fl==1)
	{
		strcat(string4, pid);
	}
	else
	{
		sprintf(ex,"%d",d);
		strcat(string4,ex);
	}
	strcat(string4, "/exe");
	readlink(string4,string5, sizeof(string5)-1);
	printf("Executable Path -- %s\n", string5);
}
