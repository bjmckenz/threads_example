#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lock;

void* first(void* vptr)
{
    printf("first, locked and sleeping\n");
    sleep(2);
    pthread_mutex_unlock(&lock);
    printf("first, unlocked\n");

    return NULL;
}

void* second(void* vptr)
{
    printf("second, trying to lock\n");
    pthread_mutex_lock(&lock);
    printf("second, got the lock and exiting\n");
    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_init(&lock, NULL);

    // starts off locked for this example
    pthread_mutex_lock(&lock);

    pthread_create(&thread1, NULL,
        first,
        NULL);
    pthread_create(&thread2, NULL,
        second,
        NULL);

    printf("main, joining\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    fprintf(stdout,
        "exiting\n");
    return 0;
}
