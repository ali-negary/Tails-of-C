/*
 * Your assignment is to parallelize a gaussian elimination algorithm to run on
 * 2, 4, or 8 processors using the PTHREADS library.  Use the handout files as 
 * a starting point.  The files implement gaussian elimination on a pseudo-
 * random input set that runs on a single processor.
 *    
 * The program takes two arguments: an input set size, and the number of threads 
 * that should be used to do the work. 
 *    
 * You can modify the code of the gauss() function and add global variables, 
 * header includes, or helper functions as needed, but you may not modify 
 * anything else in the program. You will need to adjust the compile line in the 
 * Makefile to link with the necessary library paths for your work environment. 
 * The included Makefile should be used to build, test, and time your 
 * implementation.
 *
 * Hand in a short report (PDF) that describes your implementation and 
 * optimizations performed.  The report should include all timing results output 
 * by the "make run" command.  In the report, include and analyze two graphs of 
 * your implementation's run time with an input size of 1024 with 1,2,4,8 
 * threads on two different multi-processors machines.
 *
 * Achieving best-in-class application scalability or best (lowest) time when 
 * running on the 2048 input set may earn extra credit.
 */


/* 
 * Adapted for class project from sources found at:
 *  http://www.den.rcast.u-tokyo.ac.jp/~suzuki/class/infosys/programs/gauss.c
 *
 */

/* gauss.c -- gaussian elimination */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>

#define SWAP_DOUBLE(x, y){double t; t = x; x = y; y = t;}
#define MAX 2049
#define Threshold 4700

void readArray2(double [][MAX + 1], const int);

void gauss(double [][MAX + 1], double [], const int);

void printArray2(double [], const int);

void *pivotRoutine(void *arguments);

double a[MAX][MAX + 1];
double x[MAX];
int n, threads;


int main(int argc, char *argv[]) {
    struct timeval start, stop;
    unsigned long usec;
    assert(argc == 3);
    n = atoi(argv[1]);
    assert(n < MAX);
    threads = atoi(argv[2]);
    assert(threads > 0);
    assert(!(threads & (threads - 1)));
    readArray2(a, n);
    gettimeofday(&start, NULL);

    gauss(a, x, n);

    gettimeofday(&stop, NULL);
    usec = (stop.tv_sec - start.tv_sec) * 1e6;
    usec += (stop.tv_usec - start.tv_usec);
    printf("%d,%d,%.3g\n", n, threads, usec / (double) 1e6);
    printArray2(x, n);
    return 0;
}

void readArray2(double a[][MAX + 1], const int limit) {
    int n;
    int i, j;
    int bigprime = 982451653;
    int smallprime = 32452843;
    int badrandom = bigprime % smallprime;
    n = limit;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n + 1; j++) {
            a[i][j] = badrandom;
            badrandom = (badrandom * bigprime) % smallprime;
        }
}


typedef struct {
    int baseIndex;
    int threadIndex;
    int lowerBound;
    int upperBound;
} pivotRoutineArguments;

void gauss(double a[][MAX + 1], double x[MAX], const int n) {
    int i, j, k, largest;
    double t;

    for (i = 1; i < n; i++) {
        for (largest = i, j = i + 1; j <= n; j++)
            if (abs(a[j][i]) > abs(a[largest][i]))
                largest = j;
        for (k = i; k <= n + 1; k++) SWAP_DOUBLE(a[largest][k], a[i][k]);

        // temp <= (n-i) * (n-i) / threshold and temp between 1 & threads
        int my_threads = (n-i) * (n-i) / Threshold;
        if(my_threads < 1) my_threads = 1;
        else if (my_threads > threads) my_threads = threads;
        if (my_threads > 1) {
            // define multi-threading variables.
            pthread_t thread_id[my_threads];
            int partition_size = (n - i) / my_threads; // 3 ==> 4,4,4,4,4,4,4,3
            int remainder = (n - i) % my_threads;      // 7 ==> 6,5,4,3,2,1,0
            int threadIndex;
            int result;
            int new_partition_size;
            pivotRoutineArguments thread_arguments[my_threads];
            // start thread
            // printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
            int lowerBound = i + 1;
            for (threadIndex = 0; threadIndex < my_threads; threadIndex++) {
                // printf("IN MAIN: Thread %d is created.\n", threadIndex);
                new_partition_size = partition_size;
                if (remainder != 0) {
                    new_partition_size = partition_size + 1;
                    remainder--;
                }
                thread_arguments[threadIndex] = (pivotRoutineArguments) {
                        .threadIndex = threadIndex,  // the use for this variable is for the debugging process.
                        .baseIndex = i,
                        .lowerBound = lowerBound,
                        .upperBound = lowerBound + new_partition_size - 1
                };
                // printf("i = %d, Rows %d and %d, Psize= %d, THindex = %d\n", i, lowerBound, lowerBound + new_partition_size - 1,new_partition_size, threadIndex);
                result = pthread_create(&thread_id[threadIndex], NULL, pivotRoutine, &thread_arguments[threadIndex]);
                assert(!result);
                lowerBound += new_partition_size;
            }

            // join thread
            for (threadIndex = 0; threadIndex < my_threads; threadIndex++) {
                result = pthread_join(thread_id[threadIndex], NULL);
                assert(!result);
                // printf("IN MAIN: Thread %d has ended.\n", threadIndex);
            }
            // printf("IN MAIN: All threads are done.\n");
            // printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
        } else {
            // printf("IN MAIN: NO MORE THREADS.\n");
            for (j = i + 1; j <= n; j++) {
                double ratio = a[j][i] / a[i][i];
                for (k = n + 1; k >= i; k--)
                    a[j][k] = a[j][k] - a[i][k] * ratio;
            }
        }
    }
    for (i = n; i >= 1; i--) {
        for (t = 0, j = i + 1; j <= n; j++)
            t = t + a[i][j] * x[j];
        x[i] = (a[i][n + 1] - t) / a[i][i];
    }
}

void *pivotRoutine(void *arguments) {
    pivotRoutineArguments *p = (pivotRoutineArguments *) arguments;
    int i = p->baseIndex;
    int lowerRowLimit = p->lowerBound;
    int upperRowLimit = p->upperBound;
    int j, k;
    for (j = lowerRowLimit; j <= upperRowLimit; j++) {
        double ratio = a[j][i] / a[i][i];
        for (k = n + 1; k >= i; k--)
            a[j][k] = a[j][k] - a[i][k] * ratio;
    }
}

void printArray2(double x[MAX], const int n) {
    int i;
    for (i = 1; i <= n; i++) {
        fprintf(stderr, "x[%d] = %5.2lf  ", i, x[i]);
        if (i % 3 == 0) fprintf(stderr, "\n");
    }
    if (i % 3 != 1) fprintf(stderr, "\n");
}