#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int count=0;
void *thread(void *arg)
{
	pthread_mutex_lock(&lock);
	char *letter = (char *)arg;

	
	printf("%c wants to enter the critical section\n", *letter);
	count++;
	while(count>3){
		pthread_cond_wait(&cond,&lock);
	}
	printf("%c is in the critical section\n", *letter);
	pthread_mutex_unlock(&lock);
	sleep(1);
	pthread_mutex_lock(&lock);
	printf("%c has left the critical section\n", *letter);
	
	count--;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int
main(int argc, char **argv)
{
	pthread_t threads[8];
	int i;
	char *letters = "abcdefgh";

	for(i = 0; i < 8; ++i) {
		pthread_create(&threads[i], NULL, thread, &letters[i]);

		if(i == 4)
			sleep(4);
	}

	for(i = 0; i < 8; i++) {
		pthread_join(threads[i], NULL);
		
		
	}

	printf("Everything finished...\n");

	return 0;
}
