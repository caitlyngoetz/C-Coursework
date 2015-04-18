#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *run(void *ptr);

int main(int argc, char **argv){
	int i;
	int n;
	int seed;
	pthread_t *tid;

	if(argc != 3){
		printf("Usage: thread-random <numberOfRandoms> <numThreads>");
		exit(0);
	}
	seed = atoi(argv[1]);
	n = atoi(argv[2]);
	tid = (pthread_t *) malloc(sizeof(pthread_t) * n);
	for (i=0; i<n; i++){
		value = (int *) malloc(sizeof(int));
		*value = i;
		pthread_create(&tid[i], NULL, run, (void *) value);
	}
	for (i=0; i<n; i++){
		pthread_join(tid[i], NULL);
	}
	exit(0);
}

void *run(void *ptr){
	printf("I am thread %d with thread id %X\n", *(int *)ptr, (unsigned int) pthread_self());
	pthread_exit(NULL);
}
