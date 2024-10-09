#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t can_output = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int thread_number;
    int range_minimum;
    int range_maximum;
    char what_to_print;
} thread_input_t;

typedef struct {
    int thread_number;
    int generated_random_number;
} thread_output_t;

int rand_between(int min, int max) { return rand() % (max - min) + min; }

// input allocated by caller and freed here,
// output allocated by callee and freed by caller
void* do_something_random(void* input_ptr)
{
    thread_input_t* input = (thread_input_t*)input_ptr;

    int rand_num = rand_between(input->range_minimum, input->range_maximum);

    int success = pthread_mutex_trylock(&can_output);
    while (success != 0) {
        putchar('a'+input->thread_number);
        success = pthread_mutex_trylock(&can_output);
    }

    printf("[%2d]: ", input->thread_number);
    for (int ix = 0; ix < rand_num; ix++) {
        printf("%c", input->what_to_print);
    }
    printf("\n");

    pthread_mutex_unlock(&can_output);

    thread_output_t* output = (thread_output_t*)malloc(sizeof(thread_output_t));
    output->thread_number = input->thread_number;
    output->generated_random_number = rand_num;

    free(input);

    return (void*)output;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    pthread_mutex_init(&can_output, NULL);

    int number_of_threads;
    int string_length;
    if (argc < 2
        || 0 == sscanf(argv[1], "%d%n", &number_of_threads, &string_length)
        || string_length != strlen(argv[1])
        || number_of_threads < 1) {
        fprintf(stderr, "Usage: %s <number of threads>\n", argv[0]);
        return 1;
    }

    pthread_t *threads = (pthread_t*)malloc(number_of_threads * sizeof(pthread_t));

    for (int ix = 0; ix < number_of_threads; ix++) {
        thread_input_t* input = (thread_input_t*)malloc(sizeof(thread_input_t));
        input->thread_number = ix;
        input->range_minimum = 3+ix;
        input->range_maximum = 20-ix;
        input->what_to_print = 'A' + ix;

        pthread_create(&threads[ix], NULL, do_something_random, input);
    }

    for (int ix=0; ix<number_of_threads; ix++) {
        thread_output_t* output;
        pthread_join(threads[ix], (void**)&output);
        printf("[%3d]: %3d chars\n", output->thread_number, output->generated_random_number);
        free(output);
    }

    pthread_mutex_destroy(&can_output);

    return 0;
}
