
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
long long int numRandoms = 0;
int numThreads = 0;


/* The main work routine */
void * generateRandomNumbers(void *threadId)  
{
	int i;
	long long int x;

	struct random_data *rdata = (struct random_data *) malloc(sizeof(struct random_data));
	char *statebuf = (char*)malloc(sizeof(char)*BUFSIZE);
	int32_t value;
	initstate_r(*((int *)threadId), statebuf, BUFSIZE, rdata);

	int nRandom = (numRandoms/numThreads);
	
	if(numThreads == *((int *)threadId) + 1){
		nRandom += (numRandoms%numThreads);
	}
	for(i = 0; i <nRandom; i++){
		x = random_r(rdata, &value);
		if(x != 0){
			perror("random_r");
			exit(x);
		}
	//	printf("%d\n", value);
	}
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

	numRandoms = atoi(argv[1]);
	numThreads = atoi(argv[2]);

	tid = (pthread_t *)malloc(sizeof(pthread_t) * numThreads);
	for(i = 0; i < numThreads; i++){
		value = (int *)malloc(sizeof(int));
		*value = i;
		pthread_create(&tid[i], NULL, generateRandomNumbers, (void *)value);
	}

	for(i = 0; i < numThreads; i++)
		pthread_join(tid[i], NULL);

	timeStart = getMilliSeconds();
	printf("generated %lld random numbers\n", numRandoms);

	timeElapsed = getMilliSeconds() - timeStart;
	printf("Elapsed time: %lf seconds\n", (double)(timeElapsed/1000.0));
	fflush(stdout);

	exit(0);
	return 0;
}
