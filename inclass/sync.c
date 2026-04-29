#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// global scope
int cnt = 0;

// declare global non-negative variable for semaphore
sem_t mysem;

pthread_mutex_t mymutex;

// the problem with semapphores is that any thread can decrement (unlock), which
// becomes harder to manage.
// if possible, always use mutex -> ONLY a locked thread can unlock.
void *worker(){
    for(int i = 0; i < 5000000; i++){
        // sem_wait(&mysem); // lock the thread
        pthread_mutex_lock(&mysem);
        cnt++;
        // sem_post(&mysem); // unlock the thread
        pthread_mutex_unlock(&mysem);
    }
    return NULL;
}

int main(){
    // sem_init(sem_t *sem, int pshared, unsigned int value);
    // pshare => how is the semaphore shared among the threads
    // 0 to share among threads and 1 to share among processes
    sem_init(&mysem, 0, 1);
    pthread_t thread_array[2];
    for (int i = 0; i < 2; i++){
        pthread_create(&thread_array[i], NULL, worker, NULL);
    }
    for (int i = 0; i < 2; i++){
        pthread_join(thread_array[i], NULL);
    }
    printf("cnt: %d\n", cnt);
    return 0;
}