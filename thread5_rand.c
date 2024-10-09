#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 10

void* get_rand(void* vptr)
{
    int rand_num = rand();
    fprintf(
        stdout, "Thread %p, random number = %d\n", pthread_self(), rand_num);
    return NULL;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    pthread_t threads[THREAD_COUNT];
    for (int ix = 0; ix < THREAD_COUNT; ix++) {
        pthread_create(&threads[ix], NULL, get_rand, NULL);
    }

    for (int ix = 0; ix < THREAD_COUNT; ix++) {
        pthread_join(threads[ix], NULL);
    }
    return 0;
}
