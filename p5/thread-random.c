//TURN OFF PRINT STATEMENTS!!!!!!!!!!!!!!!!!!!
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>  // must include stdio  for pvm3.h to compile correctly
#include <sys/times.h> /* for times system call */
#include <sys/time.h>  /* for gettimeofday system call */
#include <pthread.h>

/*#define DEBUG 1*/

//The main work routine
void generateRandomNumbers(void *args);  
double getMilliSeconds();
long long int count;

/* The main work routine */
void generateRandomNumbers(void *args)  
{
	long long int i;
	long int x;

	//srandom(RANDOM_SEED);
    for (i = 0; i < count; i++) {
		x = random_r (count, &args);
  	}
	pthread_exit(NULL);
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
	int *value;
	int n = atoi(argv[1]);
	pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * n);
	for(i = 0; i < n; i++){
		value = (int *) malloc(sizeof(int));
		*value = i;
		pthread_create(&tid[i], NULL, generateRanomNumbers(), (void *) value);
	}
	for(i = 0; i < n; i++){
		pthread_join(tid[i], NULL);
	}

    timeElapsed = getMilliSeconds() - timeStart;
    printf("Elapsed time:  %lf seconds\n",(double)(timeElapsed/1000.0));
    fflush(stdout);

    return 0;
}
