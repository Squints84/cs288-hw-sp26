#include <stdio.h>
#include <pthread.h>

// global scope => shared among the threads
long *array, nthreads, s, length;

// thread func
void *scalar(void *id){
	long *myid = (long *)id;

	// calculate the chunk/subset for each thread to procss
	long chunk = length / nthreads;

	// calculate the start index position for each thread to process
	long start = *(myid)*chunk;

	// calculate the end index position for each thread to process
	long end = start + chunk;

	// perform the scalar multiplication
	for (int i=start; i<end; i++){
		array[i] *= s;
	}

}

int main(int argc, char *argv[])
{
	pthread_t *thread_array;
	long *thread_ids;

	// parse commandline args
	nthreads = strtol(argv[1], NULL, 10);
	length = strtol(argv[2], NULL, 10);
	s = strtol(argv[3], NULL, 10);

	// allocate memory
	thread_array = malloc(nthreads * sizeof(pthread_t));
	thread_ids = malloc(nthreads * sizeof(long));

	// create threads
	for(int i = 0; i<nthreads; i++){
		thread_ids[i] = i;
		pthread_create(&thread_array[i], NULL, scalar, thread_ids[i]);
	}

	// join threads
	//
	for 


