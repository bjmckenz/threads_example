#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PROC_COUNT 10

void get_rand(void)
{
    int rand_num = rand();
    fprintf(stdout, "Process %d, random number = %d\n", getpid(), rand_num);
    exit(0);
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    for (int ix = 0; ix < PROC_COUNT; ix++) {
        if (fork() == 0)
            get_rand();
    }

    for (int ix = 0; ix < PROC_COUNT; ix++) {
        wait(NULL);
    }
    return 0;
}
