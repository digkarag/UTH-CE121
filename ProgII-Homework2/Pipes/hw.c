//Akridas Dimitris 1581
//Garagounis Dimitris 1589

#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 81

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
	if  ( (par[k-1] == '*')  && (par[k] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
	//elegxos gia sintaktiko lathos p.x. 2+3/..
	if ( (par[k-1] == '/')  && (par[k] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
	//elegxos gia sintaktiko lathos p.x. 2+3+..
	if  ( (par[k-1] == '+')  && (par[k] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
	//elegxos gia sintaktiko lathos p.x. 2+3-..
	if ( (par[k-1] == '-')  && (par[k] == '~') ){
		flag=0;
		printf("sintaktiko lathos\n");
	}
		
	return(flag);
}

//******************MAIN*******************
int main (int argc ,char *argv[]) {
	
	char par[SIZE],c;                             //par : pinakas gia tin epexsergasia tis parastasis
	int flag = 1,i = 0,k = 0;                     //flag,i,k : voithitikes metavlites
	int fd1[2],fd2[2],fd3[2],bytes,pid1,pid2;     //fd1,fd2,fd3 : metablites eisodou exodou ton pipe
	int p1,p2,p3;
	
		
		
	//*************open pipe1*********************
	p1 = pipe(fd1);
	if (p1<0) {                                   //elegxos gia sfalma
		perror("pipe");
		exit(1);
	}
		
	//*************open pipe2*********************
	p2 = pipe(fd2);
	if (p2<0) {                                   //elegxos gia sfalma
		perror("pipe");
		exit(1);
	}
		
	//*************open pipe3*********************
	p3 = pipe(fd3);
	if (p3<0) {                                   //elegxos gia sfalma
		perror("pipe");
		exit(1);
	}
	
	//diergasia p1
	pid1 = fork();                                //anoigma diergasias pid1
	if (pid1 == 0) {
		dup2(fd1[0],0);                           //anakateuthinsi tou stdin sto fd1[0]
		dup2(fd2[1],1);                           //anakateuthinsi tou stdout sto fd2[1]
		execlp("./p1","p1",NULL);                 //allagi kodika ektelesis
		perror("execlp");
		return (1);
	}
	if (pid1 < 0) {                               //elegxos gia sfalma
		perror ("fork");
		return (1);
	}
	
	//diergasia p2
		
	pid2 = fork();                                //anoigma diergasias pid1
	if (pid2 == 0) {
		dup2(fd2[0],0);                           //anakateuthinsi tou stdin sto fd2[0]
		dup2(fd3[1],1);                           //anakateuthinsi tou stdout sto fd3[1]
		execlp("./p2","p2",NULL);                 //allagi kodika ektelesis
		perror("execlp");
		return (1);
	}
	if (pid2 < 0) {                                //elegxos gia sfalma
		perror ("fork");
		return (1);
	}
	
	do{	
		
		do {
			flag = input(par);                    //kallite i sinartisi input gia eisodos kai epexsergasias parastasis
		}while ( flag == 0);
		
		
		i = 0;
		while(par[i] != '~') {                    //metrisi tou megethou tis parastasis tou xristi
			i++;
		}
		bytes = write(fd1[1],par,i+1);            //egrafi tis parastasis par stin pipe1
		if (bytes < 0) {
			perror("Error writing");
			close (fd1[1]);
			close (fd1[0]);
			return (1);
		}
		fsync(fd1[1]);
		
		i = 0;                                    //arxikopoiisi metavliton
		c = '1';
		
		while(c != '~') {
			bytes = read(fd3[0],&c,1);            //diavasma tis epexergasmenis pastasis apo to pipe3
			if (bytes < 0) {                      //elegxos gia sfalma
				perror("Error writing");
				close(fd3[0]);
				return (1);		
			}
			par[i] = c;
			i++;
		}
		if (par[0] == 'q'){                       //elegxos gia to an dothike entoli termatismou tou programatos
			flag = 2;
			printf("exit\n");
		}
		else if(par[0] == 'e') {                  //elegxos gia ton an brethike arithmitiko lathos stin parrastasi
			printf("arithmetic  error\n");
		}
		else{
			k = 0;
			for ( k = 0; k<i-1; k++) {
				printf("%c",par[k]);              //ektiposi tou apotelesmatos ths parastasis
			}
			printf("\n");
		}
		
	}while ( flag!=2 );
	
	//klisimo ton pipe
	close (fd1[1]);
	close (fd1[0]);
	close (fd2[1]);
	close (fd2[0]);
	close (fd3[1]);
	close (fd3[0]);
	
	return(0);
}