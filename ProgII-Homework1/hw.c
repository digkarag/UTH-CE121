/* Tilefonikos Katalogos me xrisi arxeion */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>





#define SIZE1 21	/* Megisto megethos onomatos */	
#define SIZE2 11	/* Megisto megethos tilefonou */


int anazitisi(int fd,char name[],char number[]);


/*************************-PROSTHIKI-*************************/

int prosthiki(int fd){
	
	int i=0 , f=0 , n_bytes = 0;				/* H metavliti f pernei tin timi 1 otan exei vre8ei epafi me to idio onoma kai ari8mo kai 
												tin timi 2 otan i anazitisi exei ftasei sto telos tou arxeiou kai den exei vre8ei i epafi */
	char name[SIZE1], number[SIZE2];	
	char formatstring[13];

	for (i=0; i<SIZE1; i++) {
	  name[i] = ' ';
	}
	for (i=0; i<SIZE2; i++) {
	  number[i] = ' ';
	}
	

	sprintf(formatstring, "%%%ds",SIZE1-1);		/* Eisagogi apo ton xristi tou onomatos kai tou tilefonou pou thelei na eisagei */
	scanf(formatstring, name);

	sprintf(formatstring, "%%%ds",SIZE2-1);
	scanf(formatstring, number);

	f = anazitisi(fd,name,number);		/*Klisi tis sunartisis anazitisis */

	if ( f == 2 ) {		/* To f einai 2 ara to onoma kai to tilefono den exei vrethei */

		n_bytes = write(fd,name,(SIZE1-1)*sizeof(char));
		if (n_bytes < 0) {				/* Elenxos gia to an i sunartisi write doulepse sosta */
		perror("Error writing");
		close(fd);
		return 1;
		}
		
		n_bytes = write(fd,number,(SIZE2-1)*sizeof(char));
		if (n_bytes < 0) {			/* Elenxos gia to an i sunartisi write doulepse sosta */
		perror("Error writing");
		close(fd);
		return 1;
		}
		
		n_bytes = write(fd,"\n",1);
		if (n_bytes < 0) {		/* Elenxos gia to an i sunartisi write doulepse sosta */
		perror("Error writing");
		close(fd);
		return 1;
		}
		printf ("H epafi kataxori8ike \n");
	}
	else {
		printf ("H epafi uparxei idi \n");
	}
	
return fd;
}


/*************************-ANAZITISI GIA DIPLOTIPIES-*************************/

int anazitisi(int fd,char name[],char number[]) {
	
	int f,bytes1,bytes2,a,b,where;		/* Oi metavlites bytes einai oi epistrofes tis sunartisis read kai i where epistofi tis lseek */
	char name1[SIZE1],number1[SIZE2];	/* Ta name1 kai number1 einai ta stoixeia pou diavazontai apo to arxeio se ka8e anazitisi gia tin 
										sugrisi me ta stoixeia pou edose o xristis */


	where = lseek(fd, 0L, SEEK_SET); /* Metakinisi tou fd stin arxi tou arxeiou me xrisi lseek */
	if (where < 0) { 			/* Elenxos gia to an i sinartisi lseek doulepse sosta */
		perror(NULL);
		close(fd);
		return 1;
	}
	
	f=0;

	while ( f == 0) {	/* Otan to f parei timi diafori tou midenos to onoma vre8ike h 
						h anazitisi eftase sto telous tou arxeiou xoris na vrethei */						
	 	  
	  bytes1 = read(fd, name1, (SIZE1-1)*sizeof(char));		/* Antigrafi tou onomatos apo to arxeio se string */
	  if (bytes1 < 0) {					/* Elenxos gia to an i sinartisi read doulepse sosta */
		  perror("Error reading");
	  }
	  if (bytes1 >0)  {									
		  name1[bytes1]='\0';		  
	  }
	
	  bytes2 = read(fd, number1, (SIZE2-1)*sizeof(char));	/* Antigrafi tou tilefonou apo to arxeio se string */
	  if (bytes2 < 0) {
		  perror("Error reading");
	  }
	  if (bytes2 > 0 ) {
		  number1[bytes2]='\0';		  
	  }
	  	  
	  if (( bytes1 == 0) && ( bytes2 == 0)) {		/* Ta bytes1 kai bytes2 einai 0 ara i anazitisi eftase sto telos tou arxeiou
													xoris na vrei epafi me to idio onoma kai tilefono */
	    f = 2;	/* To f pernei tin timi 2 ara i anazitisi eftase sto telous tou arxeiou xoris na vrei tin epafi */
	  }
	  else {
	    where = lseek(fd,1, SEEK_CUR);
	      if (where < 0) {		/* Elenxos gia to an i sunartisi lseek doulepse sosta */
		  perror(NULL);
		  close(fd);
		  return 1;
	      }
	  }
	    
	  a = strcmp(name,name1);			/* Sugrisi tou onomatous kai tou ari8mou pou eisigage o xristis me ta upoloipa onomata
										kai ari8mous pou uparxoun sto arxeio */
	  b = strcmp(number,number1);

	  if ((a==0)&&(b==0)){  /* An oi oi sunartisis stcmpr epestrepsan 0 ta stoixeia einai idia ara i anazitisi petuxe */
		  f=1;	/* To f pernei tin timi ena ara i anazitisi teleiose */
	  }
	 

	}
		
return f;
}

/*************************-ANAZITISI GIA TIN PROVOLH TON EPAFON-*************************/

int search(int fd){

	int f,bytes,bytes2,a,where;
	char onoma[SIZE1],onoma1[SIZE1],number1[SIZE2];
	char formatstring[13];


	sprintf(formatstring, "%%%ds",SIZE1-1);		/* Eisagogi apo ton xristi tou onomatos pou thelei na dei */
	scanf(formatstring, onoma);
	

	where = lseek(fd, 0L, SEEK_SET);
	if (where < 0) { 				/* Elenxos gia to an i sinartisi lseek doulepse sosta */
		perror(NULL);
		close(fd);
		return 1;
	}
	
	f=0;

	while ( f == 0) {							
	 
	  
		bytes = read(fd, onoma1, (SIZE1-1)*sizeof(char));		/* Antigrafi tou onomatos apo to arxeio se string */
		if (bytes < 0) {						/* Elenxos gia to an i sinartisi read doulepse sosta */
			perror("Error reading");
		}
		if (bytes >0)  {										
			onoma1[bytes]='\0';		  
		}

	  	bytes2 = read(fd, number1, (SIZE2-1)*sizeof(char));		/* Antigrafi tou tilefonou apo to arxeio se string */
	  	if (bytes2 < 0) {
			perror("Error reading");
	  	}
	  	if (bytes2 > 0 ) {
			number1[bytes2]='\0';		  
	  	}
	
	  	  	  
		if ( bytes == 0) {		/* To bytes einai 0 diladi i sunartisi read diavase 0 grammata ara i anazitisi eftase sto telos tou arxeiou */
			break;
		}
		else {
			where = lseek(fd,1, SEEK_CUR);
	    	if (where < 0) { 		/* Elenxos gia to an i sunartisi lseek doulepse sosta */
				perror(NULL);
				close(fd);
				return 1;
			}	
		}
	    
		a = strcmp(onoma,onoma1);	/* Sugrisi tou onomatos me to onoma pou edose o xristis */							
		if (a==0) {
			printf("%s \n", number1);
		}
	 
	}

return fd;
}


/***********************-DELETE-***********************/

int diagrafi (int fd){

	/* Me tin diagrafi prota anazitoume to onoma pou 8eloume na giagrapsoume kai meta metakinoume to epomeno kai ola ta upoloipa mia grami pio pano */

	int bytes_name1,bytes_number1;			/* Oi metevlites bytes einai oi epistrofes ton sunartiseon write kai read */
	int bytes_name2,bytes_number2;
	int bytes_write1,bytes_write2,bytes_write3;
	int a,where,f,t,where1;			/* Oi metavlites where einai oi epistrofes ton sunartiseon lseek */
	char onoma[SIZE1];
	char onoma1[SIZE1],number1[SIZE2];
	char onoma2[SIZE1],number2[SIZE2];
	char formatstring[13];


	sprintf(formatstring, "%%%ds",SIZE1-1);		/* Eisagogi apo ton xristi tou onomatos pou thelei na dei */
	scanf(formatstring, onoma);
	
	
	where = lseek(fd, 0L, SEEK_SET);	/* Metakinisi tou fd stin arxi tou arxeiou */
	if (where < 0) { 			/* Elenxos gia to an i sinartisi lseek doulepse sosta */
		perror(NULL);
		close(fd);
		return 1;
	}
	
	f=0;
	t=0;

	while ( f == 0) {	
	/* Me tin while elenxoume seiriaka ka8e onoma tou arxeiou apo tin arxi pros to telos oste na vroume an uparxei mesa to onoma 
	pou pliktrologise o xristis */
	 
	  
		bytes_name1 = read(fd, onoma1, (SIZE1-1)*sizeof(char));		/* Antigrafi tou onomatos apo to arxeio se string */
		if (bytes_name1 < 0) {					/* Elenxos gia to an i sinartisi read doulepse sosta */
			perror("Error reading");
		}
		if (bytes_name1 >0)  {										
			onoma1[bytes_name1]='\0';		  
		}

	  	bytes_number1 = read(fd, number1, (SIZE2-1)*sizeof(char));		/* Antigrafi tou tilefonou apo to arxeio se string */
	  	if (bytes_number1 < 0) {
			perror("Error reading");
	  	}
	  	if (bytes_number1 > 0 ) {
			number1[bytes_number1]='\0';		  
	  	}
	
	  	  	  
		if ( ( bytes_name1 == 0) && (bytes_number1 == 0) )  {		/* Ta bytes1 kai bytes2 einai 0 diladi i sunartisi read diavase 0 grammata
																	ara i anazitisi eftase sto telos tou arxeiou */
			break;
		}
		else {
			where = lseek(fd,1, SEEK_CUR);	/* Metakinisi tou fd mia 8esi mprosta gia na prosperasoume to \n kai na pame stin epomeni epafi */
			if (where < 0) { 		/* Elenxos gia to an i lseek doulepse sosta */
					perror(NULL);
					close(fd);
					return 1;
			}
			if (where == 0) {	/* An to where einai 0 i lseek dn mporese na proxorisei mia 8esi ara ftasame sto telous tou arxeiou */
				break;
			}
		}
	    
		a = strcmp(onoma,onoma1);		/* Sugrisi tou onomatos pou edose o xristis me to onoma pou diavazoume se auti tin epanalipsi */
		if ( a == 0 ) {			/* An to onoma einai to idio me auto pou edose o xristis to diagrafoume me tin parakato diadikasia */
			
			while ( t == 0) {		/* Xrisimopoioume tin metavliti t os voi8itiki oste na termatizoume tin while otan i diagrafi ginei 
									kai meta na elenxoume an to onoma uparxei me diaforetiko tilefono*/
			
				bytes_name2 = read(fd, onoma2, (SIZE1-1)*sizeof(char));	/* Antigrafi tou onomatos apo to arxeio se string */
				if (bytes_name2 < 0) {					/* Elenxos gia to an i sinartisi read doulepse sosta */
					perror("Error reading");
				}
				if (bytes_name2 >0)  {										
					onoma2[bytes_name2]='\0';	
				}
				/* Xrisimopoioume ta name2 kai number2 gia na kratisoume to onoma kai to tilefono se string oste na ta pame stin 8esi tis 
				epafis pou 8eloume na diagrapsoume. Ta name2 kai number2 einai ta epomena autis tis epafis */

				bytes_number2 = read(fd, number2, (SIZE2-1)*sizeof(char));	/* Antigrafi tou tilefonou apo to arxeio se string */
				if (bytes_number2 < 0) {		/* Elenxos gia to an i sinartisi read doulepse sosta */
					perror("Error reading");
				}
				if (bytes_number2 > 0 ) {
					number2[bytes_number2]='\0';		  
				}
			
				if ( (bytes_name2 == 0) && ( bytes_number2 == 0 ) ) {
					break;		/* an oi metavlites einai 0 ftasame sto telos tou arxeiou */
				}
			
				where = lseek(fd,-61*((off_t)sizeof(char)), SEEK_CUR);		
				/* pame ton fd 61 theseis piso (30 gia to onomata kai to noumero tis proigoumenis
				grammis 1 gia to \n kai 30 gia to onoma kai to noumero tis grammis pou vriskomaste */
				
				if (where < 0) { 
					perror(NULL);
					close(fd);
					return 1;
				}
			
				bytes_write1= write(fd,onoma2,(SIZE1-1)*sizeof(char));
				if (bytes_write1 < 0) {					/* Elenxos gia to an i sinartisi write doulepse sosta */
					perror("Error reading");
				}
	
				bytes_write2 = write(fd,number2,(SIZE2-1)*sizeof(char));
				if (bytes_write2 < 0) {					/* Elenxos gia to an i sinartisi write doulepse sosta */
					perror("Error reading");
				}
				bytes_write3 = write(fd,"\n",1);
				if (bytes_write3 < 0) {					/* Elenxos gia to an i sinartisi write doulepse sosta */
					perror("Error reading");
				}
			
				/* Grafoume ta name2 kai number2 sti 8esi tis epafis pou 8eloume na diagrapsoume */
			
				where = lseek(fd,31,SEEK_CUR);	/* Pame ton fd 31 8esi mprosta gia na epanalavoume tin diadikasi gia tin epomeni epafi */
				if (where < 0) { 
					perror(NULL);
					close(fd);
					return 1;
				}
				if (where == 0) {
					t = 1;		/* To t ginite 1 otan to where ginete 0 diladi otan ftanoume sto telos tou arxeiou */
				
				}
			}
			t = 0; /* To t 3anaginete 0 gia na 3anaginei i anazitisi oste na elenksoume an uparxei to idio onoma me allo tilefono */
			
			
			where = lseek(fd, 0L, SEEK_END);	/* Pame ton fd sto telous tou arxeiou */
			if (where < 0) { 			/* Elenxos gia to an i sinartisi lseek doulepse sosta */
				perror(NULL);
				close(fd);
				return 1;
			}
			
			where1 = lseek(fd, -31, SEEK_CUR);		/* Girname ton fd 31 8eseis piso gia na ton pame sto simeio pou 8eloume na einai to telos tou arxeiou */
			if (where1 < 0) { 			/* Elenxos gia to an i sinartisi lseek doulepse sosta */
				perror(NULL);
				close(fd);
				return 1;
			}
			where = lseek(fd, 0, SEEK_SET);		/* Ksanagirname ton fd stin arxi tou arxeiou */
			if (where < 0) { 			/* Elenxos gia to an i sinartisi lseek doulepse sosta */
				perror(NULL);
				close(fd);
				return 1;
			}

			ftruncate(fd,where1);	/* Xrisimopoioume tin sunartisi ftruncate gia na diagrapsoume tin teleutaia epafi epeidi meta tis seiriakes antigrafes 
									einai i idia me tin proteleutaia. Kratisame tin metavliti whele1 gia na tin orisoume os to neo telos tou arxeiou */
			
		}
	}
			
	
	 

return fd;
}


/*************************-MAIN-*************************/

int main (int argc, char *argv[]) {

	int fd,c;

	c = 0;
	
	
	fd = open(argv[1], O_RDWR | O_CREAT, 0644 );		/* Anoigma h dimiourgia tou arxeiou */
	if (fd < 0) {											/* Elenxos gia to an to arxeio anoi3e sosta */
		perror("Error opening file");
		return 1;
	}
	
	printf("1 : prosthiki \n2 : anazitisi \n3 : diagrafi\n4 : exodos\n");	/* Provoli ton epilogon */
	printf("Eisagete ton arithmo tis leitourgias pou thelete na kanete\n");

	scanf(" %d",&c);

	if ( c == 1) {		/* Klisi tis katalilis sunartisis me vasi tin epilogi pou edose o xristis */
		printf("Doste to onoma kai to tilefono tis epafis pou 8elete na kataxorisete\n");
		fd =  prosthiki(fd);	/* Klisi sunartisis pros8ikis */
	}
	else if ( c == 2 ) {
		printf("Doste to onoma tis epafis pou 8elete na anazitisete\n");
		fd = search(fd);	/* Klisi sunartisis anazitisis */
	}
	else if ( c == 3 ) {
		printf("Doste to onoma tis epafis pou 8elete diagrafi\n");
		fd = diagrafi(fd);	/* Klisi sunartisis diagrafis */
	}
	else if ( c == 4 ) {
		close(fd);
		return(0);
	}
	else {
		printf("lathos eisagogi.prospathiste ksana\n");
	}

			
	close(fd);

return 0;
}

	
	
