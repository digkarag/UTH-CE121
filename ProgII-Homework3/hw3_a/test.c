#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc ,char* argv[] ) {
	
	int flag;
	
	flag = 0;
	do{	
		printf("test is alive\n");
		sleep(4);
	}while(flag == 0);
	
	 return(0);
}