#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int a;
    const char* b;
} stuff_t;

void* threadfunc(void* vptr)
{
    stuff_t* stuff = (stuff_t*)vptr;
    fprintf(stdout,
        "Thread %p, a = %d, b='%s'\n",
        pthread_self(), stuff->a, stuff->b);
    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t thread1;
    pthread_t thread2;

    stuff_t first = { 1, "first" };
    stuff_t second = { 2, "second" };

    pthread_create(&thread1, NULL,
        threadfunc,
        &first);
    fprintf(stdout,
        "main after 1\n");

    pthread_create(&thread2, NULL,
        threadfunc,
        &second);
    fprintf(stdout,
        "main after 2\n");

    // wait for them to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    fprintf(stdout,
        "exiting\n");
    return 0;
}
