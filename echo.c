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
void echofunc(char *arg)
{
	int i;
	for(i=5;arg[i]!='\0';i++)
	{
		if(arg[i]!='"')
		{
			printf("%c",arg[i]);
		}
	}
	printf("\n");
}

