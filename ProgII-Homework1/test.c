#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	char command[50],c;
	
	strcpy(command,"./test < dictionary.txt");
	system(command);
	
	c=getchar();
	printf("%c\n",c);
	
return 0;
}
	
