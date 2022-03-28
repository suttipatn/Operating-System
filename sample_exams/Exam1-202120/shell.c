#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
void sighandler(){
                int status;
                wait(&status);
                if(WEXITSTATUS(status)==1){
                        printf("Order is aborted\n");
                }
        }
int main(int argc, char** argv) {
        int max=3;
        int order_num=1;
        signal(SIGCHLD,sighandler);
        char command[10];
        while (1) {
                fgets(command, 10, stdin);
                if (command[0] == 'O') {
                        if(order_num>max){
                                printf("Accepting No More Orders. Closing system now.\n");
                                exit(0);
                        }
                        //plug your code here
                        char buf[10];
                        sprintf(buf,"%d",order_num);
                        order_num++;
                        int pid=fork();
                        if(pid==0){//child
                                int pid2=fork();
                                if(pid2==0){
                                        execlp("./order.bin","./order.bin",buf,NULL);
                                }
                                else if(pid2>0){
                                        int status;
                                        wait(&status);
                                        int pid3=fork();
                                        if(pid3==0){
                                                execlp("./cook.bin","./cook.bin",buf,NULL);
                                        }
                                        else if(pid3>0){
                                                wait(&status);
                                                if(WEXITSTATUS(status)==1){
                                                        printf("Order %d  is aborted\n",order_num);}
                                        }
                                }
                        }
                } else if(command[0] == 'D'){
                        //add code here for part 5
                        int input_num = atoi(command+2);
                }
                else {
                        printf("Invalid command. Shell terminated.\n");
                        break;
                }
        }
        return 0;
}
