//Akridas Dimitris 1581
//Garagounis Dimitris 1589

#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 81                                           //megisto megethos ekfrasis

//******************INPUT******************
//parametroi:pinakas par******
//epistrofi :boithiki metavliti flag*******
//xrisi :elegxos tis parastasi tou xristi**

int input(char par[]) {
	
	int flag = 1,i = 0,j = 0,k = 0;                         //boithitikes metablites
	char c, str[SIZE];                                      //pinakes xaraktiron
	
	printf("parastasi gia ypologismo: \n");
	
	do {

		c = getchar();                                       //eisodos tis parastasi pros ypologismo
		str[i] = c;
		i++;
	}while (c != '\n');
	
	if ( (str[0] == 'q') && ( str[1] == '\n') ) {            //elegxos gia entoli termatismou programatos
		flag=2;
		par[0] = 'q';
		par[1] = '~';
		return(flag);
	}
	if (str[0] == '\n') {                                     //elegxos gia lathos ekfrasi
		flag = 0;
		return(flag);
	}
	if ( (str[0] == ' ') && ( str[1] == '\n') ) {
		flag = 0;
		return (flag);
	}
	//elegxos gia lathos ekfrasi p.x 1\n
	if (( (str[0] >= '0') && (str[0] <= '9') ) && (str[1] == '\n') ) { 
		flag = 0;
		return(flag);
	}
	
	//elegxos gia sintaktiko lathos p.x. 1+,1-,1/,1*..ktlpa
	if ((( (str[0] >= '0') && (str[0] <= '9') ) && ( (str[1] == '*') || (str[1] == '/')  
		|| (str[1] == '+') || ( str[1] == '-') ))  && ( str[2] == '\n') ){
			flag = 0;
			printf("sintaktiko lathos\n");
			return(flag);
	}
	
	k = i;                                                     //arxikopoiisi metavlitis

	for (i = 0; i < k-1; i++) {
		 //elegxos gia sintaktiko lathos p.x. +1,-1,/1,*1
		if( (str[0] == '*') || (str[0] == '/')  || (str[0] == '+') || ( str[0] == '-') ) {  
			flag = 0;
			printf("sintaktiko lathos\n");
			return(flag);
		}
		//elegxos gia sintaktiko lathos p.x. 1++2,1--2,1/*2..ktlpa
		if(( (str[i] == '*') || (str[i] == '/')  || (str[i] == '+') || ( str[i] == '-') ) && (        
			 (str[i-1] == '*') || (str[i-1] == '/')  || (str[i-1] == '+') || ( str[i-1] == '-') )) {
			flag = 0;
			printf("sintaktiko lathos\n");
			return(flag);
		}
		
		 //perasma tou elegmenou xaraktira ston pinaka par
		if ( ( (str[i] >= '0') && (str[i] <= '9') ) || (str[i] == '*') || (str[i] == '/') || (str[i] == '-') || (str[i] == '+') ) {  
			par[j] = str[i];
			j++;
		}
		else if (str[i] == ' ') {
			//elegxos gia sintaktiko lathos p.x. 1 2,5 6,..ktlpa
			if ( ( (str[i-1] >= '0') && (str[i-1] <= '9') ) && ( (str[i+1] >= '0') && (str[i+1] <= '9') ) ){
				flag = 0;
				printf("sintaktiko lathos\n");
				for (j =0; j<i; j++) {
					par[j] = ' ';
				}
				break;
			}
		}
		//elegxos gia sintaktiko lathos p.x. a+1,b12,..ktlpa
		else {
			flag = 0;
			printf("sintaktiko lathos\n");
			for (j =0; j<i; j++) {
					par[j] = ' ';
				}
			break;
		}	
	}
	par[j] = '~';        //'~' endeixi telous parastasis
	
	
	//elegxos gia sintaktiko lathos p.x. 2+3*..
	if  ( (par[j-1] == '*')  && (par[j] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
	//elegxos gia sintaktiko lathos p.x. 2+3/..
	if ( (par[j-1] == '/')  && (par[j] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
	//elegxos gia sintaktiko lathos p.x. 2+3+..
	if  ( (par[j-1] == '+')  && (par[j] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
	//elegxos gia sintaktiko lathos p.x. 2+3-..
	if ( (par[j-1] == '-')  && (par[j] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
		
	return(flag);
}

//******************MAIN*******************
int main (int argc ,char *argv[]) {
	
	char par[SIZE],p;                //par : pinakas gia tin epexsergasia tis parastasis
	int flag = 1,i = 0,k = 0,a = 1;             //flag,i,k,a,bytes : boithitikes metablites
	int fd1,fd2,fd3,bytes,pid1,pid2;            //fd1,fd2,fd3 :perigrafeis arxeion
	
	//*************a1**********************
	fd1 = open("a1", O_RDWR | O_CREAT , 0644);  //anoigma arxeiou a1
	if (fd1 < 0) {                              //elegxos gia sfalma
		perror("Error opening file");
	}
	
	bytes = write(fd1,"w",1);                   //grapsimo w stin 1 thesi toy a1
	if (bytes < 0) {                            //elegxos gia sfalma
		perror("Error writing");
		close(fd1);
		return (1);
	}
	fsync(fd1);
	//*************a2*********************
	fd2 = open("a2", O_RDWR | O_CREAT , 0644);  //anoigma arxeiou a2
	if (fd2 < 0) {                              //elegxos gia sfalma
		perror("Error opening file");
	}
	
	bytes = write(fd2,"w",1);                   //grapsimo w stin 1 thesi toy a2
	if (bytes < 0) {                            //elegxos gia sfalma
		perror("Error writing");
		close(fd2);
		return (1);
	}
	fsync(fd2);
	//*************a3*********************
	fd3 = open("a3", O_RDWR | O_CREAT , 0644); //anoigma arxeiou a3
	if (fd3 < 0) {                             //elegxos gia sfalma
		perror("Error opening file");
	}
	
	bytes = write(fd3,"w",1);                  //grapsimo w stin 1 thesi toy a3
	if (bytes < 0) {                           //elegxos gia sfalma
		perror("Error writing");
		close(fd3);
		return (1);
	}
	fsync(fd3);
	
	
	//******diergasia p1*****************
	pid1 = fork();                             //anoigma diergasias pid1
	if (pid1 == 0) {                        
		execlp("./p1","p1",NULL);              //allagi kodika ektelesis
		perror("execlp");
		return (1);
	}
	if (pid1 < 0) {                            //elegxos gia sfalma
		perror ("fork");
		return (1);
	}
	
	//******diergasia p2*****************
		
	pid2 = fork();                             //anoigma diergasias pid2
	if (pid2 == 0) {
		execlp("./p2","p2",NULL);              //allagi kodika ektelesis
		perror("execlp");
		return (1);
	}
	if (pid2 < 0) {                            //elegxos gia sfalma
		perror ("fork");
		return (1);
	}
	
	do{
		//katharismos arxeion************
		ftruncate(fd1,1);                     
		ftruncate(fd2,1);
		ftruncate(fd3,1);
		
		
		flag = 1,i = 0,k = 0,a = 1;            //arxikopoiisi boithitikon metavliton
		p = 'a';
		
		bytes = lseek(fd1, 0L, SEEK_SET);      //metakinisi tou fd1 stin arxi toy arxioy a1
		if (bytes < 0) {                       //elegxos gia sfalma
			perror(NULL);
			close(fd1);
			return 1;
		}

		bytes = lseek(fd1, 1, SEEK_CUR);       //metakinisi tou fd1 mia thesi mprosta sto arxio a1
		if (bytes < 0) {                       //elegxos gia sfalma
			perror(NULL);
			close(fd1);
			return 1;
		}

		
		do {
			
			flag = input(par);           //kallite i sinartisi input gia eisodos kai epexsergasias parastasis
			
		}while ( flag == 0);
	
		while(par[i] != '~') {               //metrisi tou megethou tis parastasis tou xristi
			i++;
		}
		bytes = write(fd1,par,i+1);          //egrafi tis parastasis par sto arxio a1
		if (bytes < 0) {                      //elegxos gia sfalma
			perror("Error writing");
			close(fd1);
			return (1);
		}
		fsync(fd1);
		
		bytes = lseek(fd1, 0L, SEEK_SET);     //metakinisi tou fd1 stin arxi toy arxioy a1
		if (bytes < 0) {                      //elegxos gia sfalma
			perror(NULL);
			close(fd1);
			return 1;
		}
		bytes = write(fd1,"r",1);             //grapsimo tou r stin proti thesi tou arxeiou a1 gia endeixi katastasis tou
		if (bytes < 0) {                      //elegxos gia sfalma
			perror("Error writing");
			close(fd1);
			return (1);
		}
		fsync(fd1);
		
		
		
		a = 1;                                //arxikopoiisi metavlitis
		while (a == 1) {
		
			bytes = lseek(fd3, 0L, SEEK_SET); //metakinisi tou fd3 stin arxi toy arxioy a3
			if (bytes < 0) {                  //elegxos gia sfalma
				perror(NULL);
				close(fd3);
				return 1;
			}
			bytes = read(fd3,&p,1);           //diavasma tis protis thesis tou a3 gia elegxo tis katastasis tou
			if (bytes < 0) {                  //elegxos gia sfalma
				perror("Error writing");
				close(fd3);
				return (1);
			}
			
			
			if (p == 'r') {                   
				
				i=0,k=0;                      //arxikopoiisi metavliton
				
				while(p != '~') {
					bytes = read(fd3,&p,1);   //diavasma tis epexergasmenis pastasis apo to a3
					if (bytes < 0) {          //elegxos gia sfalma
						perror("Error writing");
						close(fd3);
						return (1);
					}
					par[i] = p;
					i++;
				}
				if (par[0] == 'e') {         //elegxos gia ton an brethike arithmitiko lathos stin parrastasi
					printf("arithmetic  error\n");
				}
				else if (par[0] != 'q') {    //elegxos gia to an dothike entoli termatismou tou programatos
					for (k = 0; k< i-1; k++) {
						printf("%c",par[k]);   //ektiposi tou apotelesmatos ths parastasis
					}
					printf("\n");
				}
				a = 0;                        //arxikopoiisi metavlitis
			}
			
		}
		
		bytes = lseek(fd3, 0L, SEEK_SET);    //metakinisi tou fd3 stin arxi toy arxioy a3
		if (bytes < 0) {                     //elegxos gia sfalma
			perror(NULL);
			close(fd3);
			return 1;
		}
		bytes = write(fd3,"w",1);           //grapsimo tou w stin proti thesi tou arxeiou a3 gia endeixi katastasis tou
		if (bytes < 0) {                    //elegxos gia sfalma
			perror("Error writing");
			close(fd3);
			return (1);
		}
		fsync(fd3);

	}while (flag!=2);
	
	printf("exit\n");
	
	//katharismos arxeion
	ftruncate(fd1,1);
	ftruncate(fd2,1);
	ftruncate(fd3,1);
	
	//klisimo arxeion
	close(fd1);
	close(fd2);
	close(fd3);
	
	return(0);
}