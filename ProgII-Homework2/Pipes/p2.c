//Akridas Dimitris 1581
//Garagounis Dimitris 1589

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 81

/*********************MAIN**************************/
int main (int argc, char *argv[]) {
	
	int i = 0,j = 0,f = 0,k = 0,len = 0;
	char par[SIZE],c,str1[SIZE],str2[SIZE],str[SIZE],par1[SIZE];
	int result = 0, result1 = 0, result2 = 0; 
	
	do {
		i = 0;
		do {
			scanf("%c",&c);             //diavasma parastasis apo ton pipe2
			par[i] = c;
			i++;
		}while (c != '~');
		
		fflush(stdin);
		
		if ( (par[0] == 'q')||(par[0] == 'e') ) {     //elegxos gia entoli termatismou
			par1[0] = par[0];
			par1[1] = par[1];
			k = 1;
		}
		else {
			
			i = 0,j = 0,f = 0,k = 0,len = 0,result = 0, result1 = 0, result2 = 0;     //arxikopoihsh metavliton
			
			while (par[i] != '~') {
				j = i;
				f = 0;
				while (( par[j] >= '0') && (par[j]<= '9') ) {
					str1[f] = par[j];
					str1[f+1] = '\0';
					f++;
					j++;
				}
				i = j;
				
				if (par[i] == '~') {
					result1 = atoi(str1);
				}
				else {
					j = i+1;
					f = 0;
					while (( par[j] >= '0') && (par[j]<= '9') ) {
						str2[f] = par[j];
						str2[f+1] = '\0';
						f++;
						j++;
					}
					
					result1 = atoi(str1);                                          //metatropi tou string se akeraio
					result2 = atoi(str2);
					
					if (par[i] == '+' ){
						result = result1+result2;
					}
					else{
						result = result1-result2;
					}
					
					i = j;
					result1 = result;                                              //apo8ikeusi tou apotelesmatos sto result1 gia diadoxikes pra3eis
					
					while ( ( par[i] == '+') || ( par[i] == '-') ) {
						j = i+1;
						f = 0;
						while (( par[j] >= '0') && (par[j]<= '9') ) {
							str2[f] = par[j];
							str2[f+1] = '\0';
							f++;
							j++;
						}
						
						result2 = atoi(str2);
						if (par[i] == '+' ){
							result = result1+result2;
						}
						else{
							result = result1-result2;
						}
						
						i = j;
						result1 = result;
					}
				}
			}
			
			
			sprintf(str,"%d",result1);                                  //metatropi tou akeraiou se xaraktires
			len = strlen(str);
			
			k = 0;
			for(j = 0; j<len; j++) {
				par1[k] = str[j];
				k++;
			}
			
			par1[k] = '~';
		}
		
		for ( i = 0; i <= k; i++) {
			printf("%c",par1[i]);       //tiposi parastasis ston pipe3
		}
		
		fflush(stdout);
	
	}while (par[0] != 'q');
	
	exit(0);                            //termatismos diergasias p2
	
	return(0);
}