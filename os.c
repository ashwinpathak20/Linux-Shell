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
void sigintHandler(int sig_num)
{
	int w,e;
	char host[2000],a[2000];
	signal(SIGINT, sigintHandler);
	printf("\n");
	char *user=getenv("USER");
	gethostname(host,sizeof(host));
	getcwd(a,sizeof(a));
	for(e=0;control[e]!='\0' && a[e]!='\0';e++)
	{
		if(control[e]!=a[e])
		{
			break;
		}
	}
	printf("<%s@%s:",user,host);
	if(a[e]!='\0' || strlen(a)==strlen(control))
	{
		printf("~");
		for(w=e;a[w]!='\0';w++)
		{
			printf("%c",a[w]);
		}
		printf(">");
	}
	else
	{
		for(w=0;a[w]!='\0';w++)
		{
			printf("%c",a[w]);
		}
		printf(">");
	}
	fflush(stdout);
}
int main()
{
	int i,w,e,fl=0,str;
	int in=dup(0);
	int out=dup(1);
	global=0;
	initial=0;
	char a[2000],*p,**q,b[2000],host[2000],eof[2000];
	//struct utsname unm;
	//uname(&unm);
	char *user=getenv("USER");
	i=0;
	getcwd(b,sizeof(b));
	strcpy(control,b);
	gethostname(host,sizeof(host));
	while(fl==0)
	{
		flag=0;
		in=dup(0);
		out=dup(1);
		getcwd(a,sizeof(a));
		for(e=0;b[e]!='\0' && a[e]!='\0';e++)
		{
			if(b[e]!=a[e])
			{
				break;
			}
		}
		printf("<%s@%s:",user,host);
		if(a[e]!='\0' || strlen(a)==strlen(b))
		{
			printf("~");
			for(w=e;a[w]!='\0';w++)
			{
				printf("%c",a[w]);
			}
			printf(">");
		}
		else
		{
			for(w=0;a[w]!='\0';w++)
			{
				printf("%c",a[w]);
			}
			printf(">");
		}
		char **tokens,*p,*token,**t1;
		char s[2] = ";";
		signal(SIGINT, sigintHandler); 
		signal(SIGTSTP,sigstop); 
		p=readline();
		if(strcmp(p,"\0")==0)
		{
			printf("\nexit\n");
			break;
		}
		tokens=tokenize1(p,";\n");
		//printf("%s\n",fgets(tokens[0],1024,stdin));
		/*if(fgets(tokens[0],1024,stdin)==NULL)
		  {
		  break;
		  }*/
		w=0;
		while(tokens[w]!=NULL)
		{
			token=tokens[w];
			if(token[0]=='c' && token[1]=='d')
			{
				if(token[2]=='\0' || token[2]==' ')
				{
					t1=tokenize1(token," ");
					changedirectory(t1,b);
				}
			}
			else if(token[0]=='e' && token[1]=='c' && token[2]=='h' && token[3]=='o' && (token[4]=='\0' || token[4]==' '))
			{
				echofunc(token);
			}
			else if(token[0]=='p' && token[1]=='w' && token[2]=='d' && (token[3]=='\0'))
			{
				t1=tokenize1(token," ");
				pwdfunc();
			}
			else if(token[0]=='q' && token[1]=='u' && token[2]=='i' && token[3]=='t' && token[4]=='\0')
			{
				fl=1;
				break;
			}
			else if(token[0] == 'p' && token[1] =='i' && token[2] =='n' && token[3] =='f' && token[4] =='o' && (token[5]=='\0' || token[5]==' '))
			{
				t1=tokenize1(token," ");
				pinfo(t1);
			}
			else if(token[0] == 'j' && token[1]=='o' && token[2]=='b' && token[3]=='s' && token[4]=='\0')
			{
				listjobs();
			}
			else if(token[0] == 'k' && token[1]=='i' && token[2]=='l' && token[3]=='l' && token[4]=='\0')
			{
				killall();
			}
			else if(token[0]=='k' && token[1]=='j' && token[2]=='o' && token[3]=='b' && (token[4]==' ' || token[4]=='\0'))
			{
				t1=tokenize1(token," ");
				kjobs(t1);
			}
			else
			{
				for(str=0;token[str]!='\0';str++)
				{
					if(token[str]=='|')
					{
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					t1=tokenize1(token," \n");
					e=execute(t1);
				}
				else
				{
					for(str=0;token[str]!='\0';str++)
					{
						if(token[str]=='|')
						{
							if(token[str+2]=='\0')
							{
								flag=0;
								fprintf(stderr,"Not valid command\n");
							}
						}
					}
					if(flag==1)
					{
						t1=tokenize1(token,"|\n");
						e=pipes(t1);
					}
				}
			}
			w++;
		}
		dup2(in,0);
		dup2(out,1);
		close(in);
		close(out);
		i++;
	}
	return 0;
}

