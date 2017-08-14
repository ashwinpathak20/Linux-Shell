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
void kjobs(char **tokens)
{
	int i;
	int checker=0;
	if(tokens[1]==NULL)
	{
		fprintf(stderr,"Job Id is not specified\n");
	}
	else if(tokens[2]==NULL)
	{
		fprintf(stderr,"Signal Id is not specified\n");
	}
	else
	{
		for(i=initial;i<global;i++)
		{
			if(a[i]==atoi(tokens[1]))
			{
				checker=1;
				kill(c[i],atoi(tokens[2]));
				break;
			}
		}
		if(checker==0)
		{
			fprintf(stderr,"No such job ID\n");
		}
	}
}

