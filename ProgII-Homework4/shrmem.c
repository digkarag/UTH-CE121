#include "shrmem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 10

typedef struct{
	int in;
	int out;
	int free;
	char mem[SIZE];
}info;

info *ptr;
int memid;

/*sunartisi gia tin dimiourgia tis mnimis */
int buf_init(){
	
	int shmid;
	
	key_t key;
	char *path = "/hw4";
	int id = 'S';

	key = ftok(path, id);
	
	shmid = shmget(key,sizeof(info),IPC_CREAT|0777);
	if (shmid == -1) {
		perror("shmget");
		return(-1);
	}
	
	memid = shmid; 
	ptr = (info *)shmat(shmid,NULL,0);
	if ( ptr == (void*)-1 ) {
		perror("shmat");
		return(-1);
	}
	
	ptr->free = SIZE;
	
	return(1);
}

/*sunartisi gia tin katastrofi tis koinoxristis mnimis */
int buf_destroy(){
	
	int shmid;
	
	shmid = shmdt(ptr);
	if (shmid == -1){
		return(-1);
	}
	
	shmid = shmctl(memid,IPC_RMID,NULL);
	if (shmid == -1){
		return(-1);
	}
	
	return(1);
}

/*sunartsi gia tin eisagogi twn xaraktiron*/
int buf_put(char c){
	
	if (ptr->in - ptr->out < 2){	/* Sunthiki gia ton sunxronismo tou test1 me to test2 */
		ptr->mem[ptr->in] = c;
		ptr->in = ((ptr->in) +1) % SIZE;
		ptr->free --;
	}
	else{
		return(0);
	}
	return(1);
}

/*sunartisi gia ektuposi twn xaraktiron*/
int buf_get (char *c){
	
	if (ptr->in != ptr->out) {
		*c = ptr->mem[ptr->out];
		ptr->out = ((ptr->out) +1) % SIZE;
		ptr->free ++;
	}
	else {
		return(0);
	}
	return(1);
}


