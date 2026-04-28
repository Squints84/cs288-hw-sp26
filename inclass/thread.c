#include <pthread.h>
#include <stdio.h>

void *computation(void *id);

int main(){

	// create a thread
	// pthread_create(pthread_t *thread_name, pthread_attrs_t *args, void *func_name, void *func_args);
	// join is pause execution until threads finish
	// pthread_join(pthread_t thread_name, void *retval);
	
	/*
	pthread_t thread1;
	pthread_t thread2;
	*/
	long value1=1, value2=2;
	/*
	pthread_create(&thread1, NULL, computation, (void *)&value1);
	pthread_create(&thread2, NULL, computation, (void *)&value2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL); */

	computation((void *)&value1);
	computation((void *)&value2);
}

void *computation(void *id){
	long *myid = (long *)id;
	int sum = 0;
	for(int i=0; i<1000000000; i++){
		sum += *myid;
	}
	return NULL;
}

