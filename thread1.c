#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* all_my_thread_processing(void* vptr)
{
    fprintf(stdout, "I'm Thread id %p\n", pthread_self());
    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t thread1;

    fprintf(stdout, "I'm main before create\n");
    pthread_create(&thread1, NULL, all_my_thread_processing, NULL);
    fprintf(stdout, "I'm main after create\n");

    sleep(1);
    fprintf(stdout, "I'm main after sleep and now exiting\n");
    return 0;
}
