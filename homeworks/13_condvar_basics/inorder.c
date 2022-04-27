#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_cond_t conarr[3];
int done[3];
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void *thread(void *arg)
{
        pthread_mutex_lock(&lock);
        
        int *num = (int *)arg;
        if(*num!=1){
                while(!done[*num-2]){
                        pthread_cond_wait(&conarr[*num-2],&lock);
                }
        }
        printf("%d wants to enter the critical section\n", *num);

        printf("%d is finished with the critical section\n", *num);
        
        if(*num!=4){
                done[(*num)-1]=1;
                pthread_cond_signal(&conarr[*num-1]);
        }
        
        pthread_mutex_unlock(&lock);
        return NULL;
}

int
main(int argc, char **argv)
{
        for(int i=0;i<3;i++){
                pthread_cond_init(&conarr[i],NULL);
        }
        pthread_t threads[4];
        int i;
        int nums[] = {2, 1, 4, 3};

        for(i = 0; i < 4; ++i) {
                pthread_create(&threads[i], NULL, thread, &nums[i]);

                if(i == 2)
                        sleep(3);
        }

        for(i = 0; i < 4; ++i) {
                pthread_join(threads[i], NULL);
        }

        printf("Everything finished\n");

        return 0;
}