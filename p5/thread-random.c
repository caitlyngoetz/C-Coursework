
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
void * generateRandomNumbers(void *threadId);  
double getMilliSeconds();
long long int randoms = 0;
int threads = 0;


/* The main work routine */
void * generateRandomNumbers(void *threadId)  
{
	int i;
	long long int count;

	struct random_data *rdata = (struct random_data *) malloc(sizeof(struct random_data));
	char *statebuf = (char*)malloc(sizeof(char)*BUFSIZE);
	int32_t value;
	initstate_r = 0;
	initstate_r(*((int *)threadId), statebuf, BUFSIZE, rdata);

	int numRandom = (randoms/threads);
	
	if(threads == *((int *)threadId) + 1){
		numRandom += (randoms%threads);
	}
	for(i = 0; i <numRandom; i++){
		count = random_r(rdata, &value);
		if(count != 0){
			perror("random_r");
			exit(count);
		}
	//	printf("%d\n", value);
	}
	free(statebuf);
	free(rdata);
	pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    int i;
	int *value = 0;
	pthread_t *tid;

	double timeStart = 0;
	double timeElapsed = 0;

	if(argc < 2){
		fprintf(stderr, "Usage: thread-random <numberOfRandoms> <numThreads>\n");
		exit(1);
	}

	randoms = atoi(argv[1]);
	threads = atoi(argv[2]);

	tid = (pthread_t *)malloc(sizeof(pthread_t) * threads);
	for(i = 0; i < threads; i++){
		value = (int *)malloc(sizeof(int));
		*value = i;
		pthread_create(&tid[i], NULL, generateRandomNumbers, (void *)value);
	}

	for(i = 0; i < threads; i++)
		pthread_join(tid[i], NULL);

	timeStart = getMilliSeconds();
	printf("generated %lld random numbers\n", randoms);

	timeElapsed = getMilliSeconds() - timeStart;
	printf("Elapsed time: %lf seconds\n", (double)(timeElapsed/1000.0));
	fflush(stdout);

	free(value);
	free(tid);
	exit(0);
	return 0;
}
