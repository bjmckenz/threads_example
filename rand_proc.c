#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define RESEED_NOT 0
#define RESEED_WITH_TIME 1
#define RESEED_WITH_TIMENPROC 2

int main(int argc, char** argv)
{
    unsigned seed = 0;
    int reseed = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [noseed|time|<seed>] [T|P]\n", argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "noseed")) {
        ;
    } else if (!strcmp(argv[1], "time")) {
        seed = (unsigned)time(NULL);
    } else {
        sscanf(argv[1], "%u", &seed);
    }

    if (seed)
        srand(seed);

    if (argc > 2) {
        if (argv[2][0] == 'T') {
            reseed = RESEED_WITH_TIME;
        } else if (argv[2][0] == 'P') {
            reseed = RESEED_WITH_TIMENPROC;
        }
    }

    for (int ix = 0; ix < 10; ix++) {
        if (fork() == 0) {
            if (reseed == RESEED_WITH_TIME)
                srand(time(NULL));
            else if (reseed == RESEED_WITH_TIMENPROC)
                srand(time(NULL) ^ (getpid() << 16));

            printf("rand() = %u\n", rand());
            exit(0);
        }
    }
    return 0;
}
