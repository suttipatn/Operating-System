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
		int status;
		wait(&status);
        }

int main() {
    char command[82];
    char *parsed_command[2];
     //takes at most two input arguments
 signal(SIGCHLD,sighandler);  
    // infinite loop but ^C quits
    while (1) {
      	    printf("SHELL%% ");
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
	if(parsed_command[0][0]=='B'&&parsed_command[0][1]=='G'){
		 if(pid==0){
			int pid2=fork();
			if(pid2==0){
	       			execlp(parsed_command[0]+2,parsed_command[0]+2,parsed_command[1],(char*)NULL);
				exit(1);
			}
			else if(pid2>0){
				int status;
				wait(&status);
				printf("Background command finished\n");
				exit(2);
			}
		 }}

	else{
		 if(pid==0){
			 execlp(parsed_command[0],parsed_command[0],parsed_command[1],(char*)NULL);
		exit(3);
		 }
		else if(pid>0){
				int status;
				wait(&status);
		 }}
		}
		
  }
