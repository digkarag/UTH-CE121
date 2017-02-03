#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define SIZE 80

//domi dedomenon struct gia tis plirofories ton diergasion
struct list{
	int pid;
	char exec[SIZE];
	char state[SIZE];
	struct list *next;
};

/**********MAIN********************************************/
int main (int argc ,char* argv[] ) {
	
	char c,str[SIZE],command[SIZE],progname[SIZE],*result,*tok[SIZE],**ar,execstate;
	int flag,flag2,i,j,lentok1,lentok2,pid;
	int c1,c2,c3,c4,c5,c6,c7;
	int fd[2],p1,bytes;
	struct list *curr,*root,*prev;
	
	//desmeysi mnimis gia tin kefali tis listas
	root = (struct list*)malloc(sizeof(struct list));
	root->next = root;
	
	//anoigma anonimoy agogou
	p1 = pipe(fd);
	//elegxos gia sfalmata
	if (p1<0) {                                  
		perror("pipe");
		exit(1);
	}
	
	do{
		//arxikopoiisi metabliton
		i = 0,j = 0,flag = 0,flag2 = 0,lentok1 = 0,lentok2 = 0;
		c1 = c2 = c3 = c4 = c5 = c6 = c7 = 5;
		do{
			//anagnosi xaraktiron apo tin othoni
			c = getchar();
			//elegxos gia akiri isagogi "'\n'"
			if ((i == 0)&&(c == '\n')){
				while(c == '\n') {
					c = getchar();
				}
			}
			//elegxos gia kathe xaraktira
			if ( ( c >= 32 ) && ( c <= 126 ) ) {
				if (i==5){
					if ((str[0] == 'e')&&(flag == 0) ) {
						str[5] = '.';
						str[6] = '/';
						i=i+2;
						flag = 2;
					}
				}
				str[i] = c;
				i++;
			}
			else{
				str[i] = ' ';
				i++;
			}
		}while ( c != '\n' );
		
		//metatropi tis entolis toy xristi se string
		str[i-1] = '\0';
		
		i = 0;
		//xorismos toy string se lexis kai eisagogi ston tok
		result = strtok( str," " );
		while( result != NULL ) {
			tok[i] = result;
			result = strtok( NULL," ");
			i++;
		}
		
		//apothikeusi megethous pinaka tok
		lentok1 = i;
		
		//antigrafi tis entolis kai tou deyteroy orismaos tou xristi
		strcpy(command,tok[0]);
		strcpy(progname,tok[1]);
		
		//elexgos gia tin entoli tou xristi
		c1 = strcmp(command,"exec");
		c2 = strcmp(command,"kill");
		c3 = strcmp(command,"stop");
		c4 = strcmp(command,"cont");
		c5 = strcmp(command,"list");
		c6 = strcmp(command,"quit");
		c7 = strcmp(command,"info");
		
		//***command exec*****
		if (c1 == 0) {
			
			//desmeysi mnimis gia tis grammes tou pinaka orismaton
			ar = (char**)malloc((lentok1-2)*sizeof(char*));
			
			//desmeysi mnimis gia to kathe orisma
			j = 2;
			for (i = 0; i<=(lentok1-3); i++) {
				lentok2 = strlen(tok[j]);
				ar[i] = (char*)malloc(lentok2*sizeof(char));
				strcpy(ar[i],tok[j]);
				j++;
			}
			
			//anoigma diergasias
			pid = fork();
			
			//dimioyrgia kombou sti lista gia ti nea diergasia 
			curr = (struct list*)malloc(sizeof(struct list));
			
			//eisagogi dedomenon tis deirgasias sti lista
			curr->pid = pid;
			strcpy(curr->exec,progname);
			strcpy(curr->state,"running");
			
			curr->next = root->next;
			root->next = curr;
			
			//elegxos gia ti diergasia paidi
			if (pid == 0) {
				bytes = write(fd[1],"s",1);
				//allagi kodika diergasias
				execvp(progname,ar);
				perror("execvp");
				//diabasma apo ton agogo
				bytes = read(fd[0],&execstate,1);         
				//elegxos gia sfalma
				if (bytes < 0) {                      
					perror("Error writing");
					close(fd[0]);
					close(fd[1]);
					return (1);		
				}
				//eisagogi xaraktira ston pipe
				bytes = write(fd[1],"f",1);          
				//elegxos gia sfalma
				if (bytes < 0) {
					perror("Error writing");
					close (fd[1]);
					close (fd[0]);
					return (1);
				}
				fsync(fd[1]);
				return(1);
			}
			//elegxos gia sfalma
			if (pid < 0 ){
				perror("fork");
				return(1);
			}
			
			//anamoni gia tin eisagogi ton xaraktiron ston pipe apo to paidi
			sleep(1);
			
			//diabasma apo ton pipe
			bytes = read(fd[0],&execstate,1);         
			//elegxos gia sfalma
			if (bytes < 0) {                      
				perror("Error writing");
				close(fd[0]);
				close(fd[1]);
				return (1);		
			}
			//elegxos gia to an i exec epestrepse
			if ( execstate == 'f' ){
				//termatismos tis akiris diergasias
				kill(pid,SIGTERM);
				//anamoni gia termatismo tis deirgasias(elegxos gia diergasia zombi)
				waitpid(pid,NULL,0);
				//sbhsimo ton pliroforion tis akiris diergasias apo ti lista
				strcpy(root->exec,progname);
				for(prev = root,curr = root->next; strcmp(curr->exec,progname)!=0;  prev = curr,curr = curr->next);
				if (curr != root) {
					prev->next = curr->next;
					free(curr);
				}
			}
			
			//eleutherosi tis mnimis toy pinaka orismaton
			for( i = 0; i<=(lentok1-3); i++) {
				free(ar[i]);
			}
			free(ar);
		}

		//***command kill*****
		if (c2 == 0) {
			pid = atoi(progname);
			root->pid = pid;
			for(prev = root,curr = root->next; curr->pid!=pid; prev = curr,curr = curr->next);
			if (curr != root) {
				prev->next = curr->next;
				free(curr);
				kill(pid,SIGTERM);
				kill(pid,SIGCONT);
				waitpid(pid,NULL,0);
				
			}
			else{
				printf("process dont exist\n");
			}
		}
		
		//***command stop*****
		if (c3 == 0) {
			pid = atoi(progname);
			root->pid = pid;
			for(curr = root->next; curr->pid!=pid; curr = curr->next);
			if (curr != root) {
				strcpy(curr->state,"stopping");
				kill(pid,SIGSTOP);
			}
			else{
				printf("process dont exist\n");
			}
		}
		
		//***command cont*****
		if (c4 == 0) {
			pid = atoi(progname);
			root->pid = pid;
			for(curr = root->next; curr->pid!=pid; curr = curr->next);
			if (curr != root) {
				strcpy(curr->state,"running");
				kill(pid,SIGCONT);
			}
			else{
				printf("process dont exist\n");
			}
		}
		
		//***command list*****
		if (c5 == 0) {
			for (curr = root->next; curr!=root; curr = curr->next){
				printf("id : %d\nprog : %s\nstate : %s\n",curr->pid,curr->exec,curr->state);
			}
			if (root->next == root) {
				printf("no current process\n");
			}
		}
		
		//***command quit*****
		if (c6 == 0){
			flag2 = 1;
			for (curr = root->next,prev = root->next; curr!= root; curr = curr->next,prev=prev->next){
				prev = curr;
				kill(curr->pid,SIGTERM);
				free(curr);
				curr = prev;
			}
			free(root);
		}
		
		//***command info****
		if (c7 == 0){
			pid = atoi(progname);
			root->pid = pid;
			for(curr = root->next; curr->pid!=pid; curr = curr->next);
			if (curr != root) {
				kill(pid,SIGUSR1);
			}
			else{
				printf("process dont exist\n");
			}
			
		}
		
	}while(flag2 == 0);
	
	close(fd[0]);
	close(fd[1]);
	
	//anamoni gia termatismo diergasion kai apofigi diergasion zombi
	waitpid(0,NULL,0);
	
	return(0);
}
	
