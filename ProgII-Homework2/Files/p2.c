//Akridas Dimitris 1581
//Garagounis Dimitris 1589

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 81

/********MAIN****************************************/
int main (int argc, char *argv[]) {
	
	int bytes,fd2,fd3,i = 0,j = 0,f = 0,k = 0,len = 0;
	char par[SIZE],c,str1[SIZE],str2[SIZE],str[SIZE],par1[SIZE];
	int result = 0, result1 = 0, result2 = 0; 
	
	fd2 = open("a2", O_RDWR | O_CREAT , 0644);                //anoigma tou arxeiou a2
	if (fd2 < 0) {                                            //elenxos gia sfalma
		perror("Error opening file");
	}
	
	fd3 = open("a3", O_RDWR | O_CREAT , 0644);                //anoigma tou arxeiou a3
	if (fd3 < 0) {                                            //elenxos gia sfalma
		perror("Error opening file");
	}
		
		
	do{
		
		for (i = 0; i< SIZE; i++) {
			par[i] = ' ';
			str1[i] = ' ';
			str2[i] = ' ';
			str[i] = ' ';
			par1[i] = ' ';
		}
		c = '1';                                               //arxikopoihsh tou c
		
		do {
			bytes = lseek(fd2, 0L, SEEK_SET);                  // Metakinisi tou fd stin arxi tou arxeiou
			if (bytes < 0) {                                   // Elenxos gia sfalma
				perror(NULL);
				close(fd2);
				return 1;
			}
			bytes = read(fd2,&c,1);
			if (bytes < 0) {
				perror("Error writing");
				close(fd2);
				return (1);
			}
			
		}while(c != 'r');                                      //epanalipsi mexri to arxeio na einai etoimo gia diavasma
		
		i = 0;                                                 //arxikopoihsh metavliton
		c = '1';
		
		while(c != '~') {                                      //epanalipsi mexri na diavastei o xaraktiras termatismou

			bytes = read(fd2,&c,1);
			if (bytes < 0) {
				perror("Error writing");
				close(fd2);
				return (1);
			}
			par[i] = c;
			i++;
		}
		if ( (par[0] == 'q')||(par[0] == 'e') ) {
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
		
		bytes = lseek(fd3, 0L, SEEK_SET);                              //metakinisi tou fd stin arxi tou arxeiou
		if (bytes < 0) {                                               //elenxos gia sfalma
			perror(NULL);
			close(fd3);
			return 1;
		}
		
		bytes = lseek(fd3, 1, SEEK_CUR);                               //metakinisi tou fd mia 8esi mprosta gia na perasei to r h w
		if (bytes < 0) {                                               //elenxos gia sfalma
			perror(NULL);
			close(fd3);
			return 1;
		}
		bytes = write(fd3,par1,k+1);
		if (bytes < 0) {
			perror("Error writing");
			close(fd3);
			return (1);
		}
		fsync(fd3);

		bytes = lseek(fd2, 0L, SEEK_SET); 
		if (bytes < 0) {  
			perror(NULL);
			close(fd2);
			return 1;
		}
		
		bytes = write(fd2,"w",1);
		if (bytes < 0) {
			perror("Error writing");
			close(fd2);
			return (1);
		}
		fsync(fd2);
		
		bytes = lseek(fd3, 0L, SEEK_SET); 
		if (bytes < 0) {
			perror(NULL);
			close(fd3);
			return 1;
		}
		
		bytes = write(fd3,"r",1);
		if (bytes < 0) {
			perror("Error writing");
			close(fd3);
			return (1);
		}
		fsync(fd3);
		
	}while( (par[0] != 'q') || (par[1] != '~') );
	
	close(fd2);
	close(fd3);
	
	exit(0);     //termatismos dergasias p2
	
	return(0);
}