#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// create the function to be executed as a thread
void* thread(void* vptr)
{
    int *ptr = (int*)vptr;
    int type = *ptr;
    fprintf(stderr, "Thread - %d\n", type);
    for (int ix=0; ix<10; ix++)
    {
        fprintf(stderr, "sleep1\n");
        sleep(1);
    }
    return ptr;
}

int main(int argc, char** argv)
{
    // create the thread objs
    pthread_t thread1, thread2;
    int *thr = (int*)malloc(sizeof(int));
    int *thr2 =  (int*)malloc(sizeof(int));
    *thr = 1;
    *thr2 = 2;
    // start the threads
    pthread_create(&thread1, NULL, thread, thr);
    pthread_create(&thread2, NULL, thread, thr2);

    // wait for threads to finish
   // pthread_join(thread1, NULL);
   // pthread_join(thread2, NULL);

//    free(thr);
 //   free(thr2);

    fprintf(stderr, "Main exiting\n");
    return 0;
}
