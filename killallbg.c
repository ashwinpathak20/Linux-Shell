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
void killall()
{
	int i;
	for(i=initial;i<global;i++)
	{
		kill(c[i],SIGKILL);
	}
}

