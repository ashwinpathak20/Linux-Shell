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
void listjobs()
{
	int i;
	for(i=initial;i<global;i++)
	{
		if(a[i]!=-1)
		{
			printf("[%d] %s [%d]\n",a[i],b[i],c[i]);
		}
	}
}
