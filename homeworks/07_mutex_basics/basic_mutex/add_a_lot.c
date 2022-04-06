/* Copyright 2016 Rose-Hulman */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 10
/*
 * You can use the provided makefile to compile your code.
*/
int total;
pthread_mutex_t mutex;
void *add10000(void *arg) {
    for (int i = 0; i < 10000; i++) {
        pthread_mutex_lock(&mutex);
        total++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char **argv) {
    total = 0;
    pthread_mutex_init(&mutex,0);
    pthread_t threads[NUM_THREADS];

    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        
        pthread_create(&threads[i], NULL, add10000, NULL);
        
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Everything finished.  Final total %d\n", total);

    return 0;
}
