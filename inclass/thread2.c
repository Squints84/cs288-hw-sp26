#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *helloworld(void *id){
	long *myid = (long *)id;
	printf("I'm a thread: %ld \n", *myid);
	return NULL;
}

int main(int argc, char *argv[]){
	long nthreads = strtol(argv[1], NULL, 10);

	pthread_t *thread_array = malloc(nthreads * sizeof(pthread_t));

	long *thread_ids = malloc(nthreads * sizeof(long));

	// create the threads
	for (int i = 0; i < nthreads; i++){
		thread_ids[i] = i;
		pthread_create(&thread_array[i], NULL, helloworld, &thread_ids[i]);
	}

	for (int i = 0; i < nthreads; i++)
	{
		pthread_join(thread_array[i], NULL);
	}
}

