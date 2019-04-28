#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

#define THREAD_NUM 2
sem_t synch;
// Need to use the following functions in the right place
// sem_init(&synch,?,?) // Figure out what parameter should be used for ?,?
// sem_wait(&synch)
// sem_post(&synch)

void *count_down(void *param) {
    int i;
    /* acquire the semaphore */
    sem_wait(&synch);
    
    //critical section
	for(i = 10; i > 0; i--){
		printf("%d\n", i);
		sleep(1);
	}
    
    pthread_exit(0);
}

void *boom(void *param) {
	printf("<<<<<<<<< BOOM >>>>>>>>\n");
    
    /* release the semaphore */
    sem_post(&synch);
    
    pthread_exit(0);
}

int main() {
	int i;
    //sem_init(&synch, 1, 1);
    // create a semaphore and initialize it
    sem_init(&synch, 1, i);
    //sem_init(&synch, 0, i);
    pthread_t tid[THREAD_NUM]; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */
    pthread_create(&tid[0], &attr, count_down, NULL);
    pthread_create(&tid[1], &attr, boom, NULL);

    /* now wait for the thread to exit */
    for (i = 0; i < THREAD_NUM; i++)
            pthread_join(tid[i], NULL);

	printf("Parent Done\n");
}
