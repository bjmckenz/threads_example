#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv)
{
    unsigned seed = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [noseed|time|<seed>]\n", argv[0]);
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

    for (int ix = 0; ix < 10; ix++) {
        printf("rand() = %u\n", rand());
    }
    return 0;
}
