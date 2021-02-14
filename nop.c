#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 586
int main(int argc, char **argv) {
  int i, j, k;
  double sum;
  struct timeval start, end; // used for timing
  double A[N][N], B[N][N], C[N][N];

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = j*1;
      B[i][j] = i*j+2;
      C[i][j] = j-i*2;
    }
  }
  gettimeofday(&start, NULL); //start time measurement
  for (i = 0; i < N; i++) {
    {
      for (j = 0; j < N; j++) {
        sum = 0;
        for (k=0; k < N; k++) {
          sum += A[i][k]*B[k][j];
        }
        C[i][j] = sum;
      }
    }
  }
  gettimeofday(&end, NULL); //end time measurement
//  printf("Time of computation: %ld microseconds\n", end.tv_sec*1000000+end.tv_usec-start.tv_sec*1000000 -start.tv_usec);
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      printf("%f", C[i][j]);
    }
    printf("\n");
  }
  return(0);
}
