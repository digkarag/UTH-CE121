#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static void handler(int sig) {
	printf("test2 got signal\n");
}

int main (int argc ,char* argv[] ) {
	
	int flag,n;
	struct sigaction act;
	act.sa_handler = handler;
	
	n = sigaction(SIGUSR1,&act,NULL);
	if (n < 0) { 
		perror("sigaction"); 
		return(1); 
	}
	
	flag = 0;
	do{	
		printf("test2 is alive\n");
		sleep(4);
	}while(flag == 0);
	
	 return(0);
}