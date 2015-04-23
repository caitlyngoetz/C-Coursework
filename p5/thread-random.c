//TURN OFF PRINT STATEMENTS!!!!!!!!!!!!!!!!!!!
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>  // must include stdio  for pvm3.h to compile correctly
#include <sys/times.h> /* for times system call */
#include <sys/time.h>  /* for gettimeofday system call */
#include <pthread.h>

/*#define DEBUG 1*/
#define BUFSIZE 32

//The main work routine
void * generateRandomNumbers(void *args);  
double getMilliSeconds();
long long int count;
long int threads;


/* The main work routine */
void * generateRandomNumbers(void *args)  
{
	void * threadId = args;
	struct random_data *rdata = (struct random_data *) malloc(sizeof(struct random_data));
	char *statebuf = (char*) malloc(sizeof(char) * BUFSIZE);

	int32_t value;
	
	initstate_r(*(int *) threadId, statebuf, BUFSIZE, rdata);
	int i;
	int status = 0;
	for(i = 0; i < count/threads; i++){
		status = random_r (rdata, &value);
	}
	if(status != 0){
		perror("random_r");
		exit(status);
	}
	return NULL;
}


int main(int argc, char **argv)
{
    double timeStart = 0;
    double timeElapsed = 0;

    if (argc < 3) {
    	fprintf(stderr, "Usage: thread-random <numberOfRandoms> <numThreads>\n");
    	exit(1);
    }
    sscanf(argv[1],"%lld",&count); /* lld for long long int */

    timeStart = getMilliSeconds();	//And we are off

	int i;
	int *value = 0;
	threads = atoi(argv[2]);
	int n = atoi(argv[1]);
	pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * n);
	for(i = 0; i < n; i++){
		value = (int *) malloc(sizeof(int));
		*value = i;
		pthread_create(&tid[i], NULL, generateRandomNumbers, (void *)value);
	}
	for(i = 0; i < n; i++){
		pthread_join(tid[i], NULL);
	}

    timeElapsed = getMilliSeconds() - timeStart;
    printf("Elapsed time:  %lf seconds\n",(double)(timeElapsed/1000.0));
    fflush(stdout);

    return 0;
}
