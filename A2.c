#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int a[2];
    int g=pipe(a);
    pid_t pid=fork();
    if(pid==0)
    {
		char  buffer[15];
        close(a[1]);
        char d;
        int e=0;
        while(read(a[0],&d,1))
        {
			buffer[e++]=d;
        }
        buffer[e++]='\0';
        close(a[0]); 
		printf("Child 1: %s \n",buffer);
    }
		  
    else if(pid>0)
    {
		pid_t pid1=fork();
		if(pid1==0)
		{
			char buffer[15];
			close(a[1]);
			char d;
			int e=0;
			while(read(a[0],&d,1))
			{
				buffer[e++]=d;
			}
			buffer[e++]='\0';
			close(a[0]); 
			printf("Child 2: %s \n",buffer);
		}
		else if(pid1>0)
		{
			close(a[0]);
		    char str[]="Hello I am parent";
		    write(a[1],str,strlen(str));
		    close(a[1]);
		    wait(NULL);
		}
	}
    return 0;
}