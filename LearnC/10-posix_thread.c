#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define number_of_threads 10


void *sayHello (void *args)
{
    char hello[20] = "Hello";
    char bye[20] = "Bye Bye";
    int *incoming = (int *)args;
    int delay = 1 + rand() % number_of_threads;

    printf("IN THREAD ==> %s to thread number %d\n", hello, *incoming);
    printf("THREAD %d: Will be busy for %d seconds.\n", *incoming, delay);
    sleep(delay);
    printf("IN THREAD ==> %s to thread number %d\n", bye, *incoming);
}

int main()
{
    pthread_t thread_id[number_of_threads];
    int thread_arguments[number_of_threads];
    int iter;
    int result;

    for (iter = 0; iter < number_of_threads; iter++)
    {
        printf("IN MAIN: Creating thread %d.\n", iter);
        thread_arguments[iter] = iter;
        result = pthread_create(&thread_id[iter], NULL, sayHello, &thread_arguments[iter]);
        assert(!result);
    }

    printf("*********************************\n");
    printf("IN MAIN: All threads are created.\n");
    printf("*********************************\n");

    for (iter = 0; iter < number_of_threads; iter++)
    {
        result = pthread_join(thread_id[iter], NULL);
        assert(!result);
        printf("IN MAIN: Thread %d has ended.\n", iter);
    }

    printf("****************\n");
    printf("The job is done.\n");
    printf("****************\n");

    return 0;
}
