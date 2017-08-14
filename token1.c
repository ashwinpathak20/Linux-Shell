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
char **tokenize1(char *p,char t[])
{
	int a=1000,b;
	int o=0;
	char **tokenlist=(char **)malloc(a*sizeof(char*)),*iterate,s[2]=";\n",*iterate1;
	iterate=strtok(p,t);
	if(tokenlist==0)
	{
		fprintf(stderr,"allocation error\n");
		exit(EXIT_FAILURE);
	}
	while(iterate!=NULL)
	{
		tokenlist[o]=iterate;
		o++;
		if(o>=a)
		{
			a+=a;
			tokenlist=(char **)realloc(tokenlist,(a*sizeof(char *)));
			if(tokenlist==0)
			{
				fprintf(stderr,"allocation error\n");
				exit(EXIT_FAILURE);
			}

		}
		iterate=strtok(NULL,t);
	}
	return tokenlist;
}

