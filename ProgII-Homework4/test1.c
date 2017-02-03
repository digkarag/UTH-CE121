#include "shrmem.h"
#include <stdio.h>

/* MAIN */
int main (int agrc, char* argv[]){
	
	int shrid;
	char c;
	
	shrid = buf_init();
	if (shrid == -1){
		printf("error to memory\n");
		return(1);
	}
	
	while (c != 'q') {
		
		c = getchar();
		shrid = buf_put(c);
		if (shrid == -1){
			printf("error to memory\n");
			return(1);
		}
		if (shrid == 0){
			while(shrid == 0) { 	/* oso to shrid einai 0 to out den exei prolavei na diavasei ola ta stoixeia apo ton kukliko pinaka */
				shrid = buf_put(c);
			}
		}
	}
	
	shrid = buf_destroy();
		if (shrid == -1){
			printf("error to memory\n");
			return(1);
		}
		
	return(0);
}
