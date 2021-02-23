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
#define SWAP_DOUBLE( x, y ){double t; t = x; x = y; y = t;}
#define MAX 2049

void readArray2(double [][MAX+1], const int);
void gauss(double [][MAX+1], double [], const int);
void printArray2(double [], const int);

double a[MAX][MAX+1];
double x[MAX];
int n, threads;

int main(int argc,char *argv[])
{
	struct timeval start, stop;
	unsigned long usec;
	assert(argc == 3);
	n = atoi(argv[1]);
	assert(n < MAX);
	threads = atoi(argv[2]);
	assert(threads>0);
	assert(!(threads & (threads-1)));
	readArray2(a, n);
	gettimeofday(&start, NULL);

	gauss(a, x, n);

	gettimeofday(&stop, NULL);
	usec = (stop.tv_sec - start.tv_sec) * 1e6;
	usec += (stop.tv_usec - start.tv_usec);
	printf("%d,%d,%.3g\n",n,threads,usec/(double)1e6);
	printArray2(x, n);
	return 0;
}

void readArray2(double a[][MAX+1], const int limit)
{
  int n;
  int i,j;
  int bigprime = 982451653;
  int smallprime = 32452843;
  int badrandom = bigprime%smallprime;
  n = limit;
  for(i = 1; i <= n; i++)
    for(j = 1; j <= n+1; j++) {
      a[i][j] = badrandom;
      badrandom = (badrandom*bigprime)%smallprime;
    }
}

void gauss(double a[][MAX+1], double x[MAX], const int n)
{
  int i,j,k,largest;
  double t;
  for(i = 1; i < n; i++){
    for(largest = i, j = i+1; j <= n; j++)
      if(abs( a[j][i] ) > abs( a[largest][i] ))
        largest = j;
    for(k = i; k <= n+1; k++)
      SWAP_DOUBLE( a[largest][k], a[i][k]);
    for( j = i+1; j <= n; j++)
      for( k = n+1; k >= i; k--)
        a[j][k] = a[j][k]-a[i][k]*a[j][i]/a[i][i];
  }
  for(i = n; i >= 1; i--){
    for(t = 0, j=i+1; j <= n; j++)
      t = t + a[i][j]*x[j];
    x[i] = (a[i][n+1] - t)/a[i][i];
  }
}

void printArray2(double x[MAX], const int n)
{
  int i;
  for(i = 1; i <= n; i++){
    fprintf(stderr,"x[%d] = %5.2lf  ",i,x[i]);
    if( i%3 == 0 ) fprintf(stderr,"\n");
  }
  if( i%3 != 1) fprintf(stderr,"\n");
}

