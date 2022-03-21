/* Copyright 2016 Rose-Hulman
   But based on idea from http://cnds.eecs.jacobs-university.de/courses/caoslab-2007/
   */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

    void sighandler(){
                printf("Background command finished\n");
		int status;
		wait(&status);
        }

int main() {
    char command[82];
    char *parsed_command[2];
// signal(SIGCHLD,sighandler);    //takes at most two input arguments
    // infinite loop but ^C quits
    while (1) {
   signal(SIGCHLD,sighandler);
      	    printf("SHELL%% ");
//	 signal(SIGCHLD,sighandler);
        fgets(command, 82, stdin);
        command[strlen(command) - 1] = '\0';//remove the \n
        int len_1;
        for(len_1 = 0;command[len_1] != '\0';len_1++){
            if(command[len_1] == ' ')
                break;
        }
        parsed_command[0] = command;
	
        if(len_1 == strlen(command)){
            printf("Command is '%s' with no arguments\n", parsed_command[0]); 
            parsed_command[1] = NULL;

        }else{
            command[len_1] = '\0';
            parsed_command[1] = command + len_1 + 1;
            printf("Command is '%s' with argument '%s'\n", parsed_command[0], parsed_command[1]); 

	}
	int pid=fork();
//	if(pid==0){
	if(parsed_command[0][0]=='B'&&parsed_command[0][1]=='G'){
		 if(pid==0){	 
	       	execlp(parsed_command[0]+2,parsed_command[0]+2,parsed_command[1],(char*)NULL);
		 }
		 else if(pid>0){
			 int status;
			 waitpid(pid,&status,WNOHANG);
//printf("Background command finished");
		 }}
	else{
		 if(pid==0){
			 execlp(parsed_command[0],parsed_command[0],parsed_command[1],(char*)NULL);
		 }
		else if(pid>0){
				int status;
				wait(&status);
			//	printf("Background command finished\n");
		 }}
//	signal(SIGCHLD,sighandler);
//	 }
//	else if(pid>0){
//		int status;
//		if(parsed_command[0][0]=='B'&&parsed_command[0][1]=='G'){
	//		waitpid(pid,&status,WNOHANG);
		}
//		else{wait(&status);}
		
	int status;
                         waitpid(-1,&status,WNOHANG);
  }
