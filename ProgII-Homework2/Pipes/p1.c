//Akridas Dimitris 1581
//Garagounis Dimitris 1589

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 81

/*********MAIN******************************/
int main (int argc, char *argv[]) {
	
	int i = 0,j = 0,f = 0,k = 0,len = 0,flag = 0,flag2 = 0;
	char par[SIZE],c,str1[SIZE],str2[SIZE],str[SIZE],par1[SIZE];
	int result = 0, result1 = 0, result2 = 0; 
	
	do{

		i = 0;
		do  {
			scanf("%c",&c);                       //diavasma parastasis apo to pipe1
			par[i] = c;
			i++;
		}while(c != '~');
		
		fflush(stdin);
		
		i = 0,j = 0,f = 0,k = 0,len = 0,result = 0, result1 = 0, result2 = 0,flag = 0,flag2 = 0;       //arxikopoihsh ton metavliton
		
		while (par[i] != '~') {                                            //diavasma tou par[] mexri na diavastei to sumvolo termatismou (~)
			if (( par[i] >= '0') && (par[i]<= '9') ) {                     //oso o xaraktiras einai arithmos
				j = i;                                                     //antigrafi tis timis tou i se voi8itiki metavliti j
				f = 0;                                                     //arxikopoihsh voi8itikis metavlitis
				while (( par[j] >= '0') && (par[j]<= '9') ) {
					str1[f] = par[j];                
					str1[f+1] = '\0';
					f++;
					j++;
				}
				i = j;                                                     //allagi tou vimatos tis epanalipsis
					
				if ((par[i] == '*' ) || (par[i] == '/')) {
					if ((par[i] == '/') && (par[i+1] == '0')) {            //elenxos gia arithmitiko la8os p.x 2/0
						par1[0] = 'e';
						par1[1] = '~';
						flag = 1;
						break;
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
					
						result1 = atoi(str1);                              //metatropi tou string se akeraio
						result2 = atoi(str2);

						if (par[i] == '*' ){
							result = result1*result2;
						}
						else{
							result = result1/result2;
						}
						
						i = j;
							
						sprintf(str,"%d",result);                           //metatropi tou akeraiou se xaraktira
						
						len = strlen(str);
						
						if  ((par[i] == '*' ) || (par[i] == '/')) {         //ektelesi gia sunexomenes pra3is
							while ((par[i] == '*' ) || (par[i] == '/')) {
								if ((par[i] == '/') && (par[i+1] == '0')) {    //elenxos gia arithmitiko la8os
									par1[0] = 'e';
									par1[1] = '~';
									flag = 1;
									flag2 = 1;
									break;
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
									result2 = atoi(str2);
									if (par[i] == '*' ){
										result1 = result*result2;
									}
									else{
										result1 = result/result2;
									}
									result = result1;
									i = j;
								
									i = i-f+1;
									sprintf(str1,"%d",result1);
									len = strlen(str1);
									
									if ((par[i] != '*' ) && (par[i] != '/')) {
										for(j = 0; j<len; j++) {
											par1[k] = str1[j];
											k++;
										}
									}
								}
							}
						}
						else{
							for(j = 0; j<len; j++) {
								par1[k] = str[j];
								k++;
							}
						}
					}
					
				}
				else{
					len = strlen(str1);
					for (j = 0; j<len; j++) {
						par1[k] = str1[j];
						k++;
					}
				}
			
			}
			else {
				par1[k] = par[i];
				k++;
				i++;
			}
			if (flag2 == 1) {
				break;
			}
		}
		if (flag == 1) {
			k = 1;
		}
		else{
			par1[k] = '~'; 
		}
		

		for ( i = 0; i <=k; i++) {
			printf("%c",par1[i]);                 //eggrafi parastasis ston pipe2
		}
			
		fflush(stdout);
	
	}while (par[0] != 'q');
	
	exit(0);                                      //termatismos diergasias
	
	return(0);
}