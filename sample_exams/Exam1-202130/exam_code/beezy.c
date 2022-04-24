#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#include "say_hello.h"


#define MAX_HEATING_DEMONS 2
#define MAX_REPAIR_DEMONS 4
void sighandler(void){
	printf("Heating demon killed.... OUCH!\n");
	exit(0);
}
int
main(int argc, char **argv)
{
	/* Let beezy say hello to you, he's a polite devil! */
	//say_hello();
	int forkvalue;
	int heatingpid[MAX_HEATING_DEMONS];
	int repairpid[MAX_REPAIR_DEMONS];
	int pipes[MAX_REPAIR_DEMONS];
	int pipeResult[2];//read/write end
	/* you code goes here.... */
	for(int i=0;i<MAX_REPAIR_DEMONS;i++){
		forkvalue=fork();
		pipe(pipeResult);//pipe before forking so that it can communicate to parent pipe first
		if(forkvalue==0){//child process return zero while parent return pid of child is being forked
			//child level 1 for waiting have to fork another to exec repair
			forkvalue=fork();
			if(forkvalue==0){
				//exec repair here child level 2
				execlp("./repair_demon","./repair_demon",NULL);
				printf("error should change context due to execlp");
				exit(1);
			}
			else{//no wait for this manager currently
				//waiting for exec of repair
				int status;//need exit status of repair
				wait(&status);
				close(pipeResult[0]);//do not need read end since we gonna write it
				
				if(WEXITSTATUS(status)==2){//failure is 2
					//need cleanup specify to wait so another fork
					printf("JOB FAILED\n");
					forkvalue=fork();
					if(forkvalue==0){
						//cleanup
						printf("Triggering a cleanup demon\n");
						sleep(3);
						exit(0);
					}
					else{
						wait(NULL);
						//after this cleanup finish
						write(pipeResult[1],"FAILURE",7);
						close(pipeResult[1]);//close write after finish
					}
				}
				else{
					printf("JOB COMPLETED\n");
						write(pipeResult[1],"SUCCESS",7);
						close(pipeResult[1]);
				}
				pipes[i]=pipeResult[0];
				exit(0);
			}
		}
		else{
			//beezy main
			
		}
	}

	for(int i=0;i<MAX_HEATING_DEMONS;i++){
		//another separate loop
		forkvalue=fork();
		if(forkvalue==0){
			//first level to wait
			forkvalue=fork();
			if(forkvalue==0){
				signal(SIGTERM,sighandler);
				printf("Heating demon looping forever\n");
				while(1);//loop forever
			}
			else{//need to store at this level as it is a parent of heating
				heatingpid[i]=forkvalue;
			}
		}
		else{
			//beezy main
		}
	}
	int count=0;
	for(int i=0;i<MAX_REPAIR_DEMONS;i++){
		char buf[100];
		read(pipes[i],buf,100);
		close(pipes[i]);
		if(!(strncmp(buf,"SUCCESS",7))){
			count++;
		}
	}
	printf("Beezy recorded %d succesful operations",count);

	if(count>=MAX_REPAIR_DEMONS/2){
		printf("Beezy is happy, everything went well, hell is back in business\n");
		for(int i=0;i<MAX_HEATING_DEMONS;i++){
				kill(SIGTERM,heatingpid[i]);
				waitpid(heatingpid[i],NULL,0);
		}
		exit(0);
	}
	else{
		printf("Beezy is giving up, here is my resignation letter\n");
		exit(1);
	}
	exit(0);
	
}
