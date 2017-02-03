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
		
		while (1){
			
			shrid = buf_get(&c);
			if (shrid == -1){
				printf("error to memory\n");
				return(1);
			}
			if (shrid != 0){
				if ( c == 'q') {
					printf("--EXIT--\n");
					return(0);
				}
				putchar(c);
			}
			else {
				
			}
		}
		
		
		shrid = buf_destroy();
		if (shrid == -1){
			printf("error to memory\n");
			return(1);
		}
	
	return(0);
	}
