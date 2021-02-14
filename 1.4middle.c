#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 586
#define CHUNKSIZE 75
int main(int argc, char **argv) {
  //omp_set_num_threads(2);//set number of threads here
  int i, j, k, loop;
  double sum;
  double start, end; // used for timing
  double A[N][N], B[N][N], C[N][N];

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = j*1;
      B[i][j] = i*j+2;
      C[i][j] = j-i*2;
    }
  }
  int chunk = CHUNKSIZE;
  start = omp_get_wtime(); //start time measurement
  for(loop = 0; loop < 10; loop++){
    for (i = 0; i < N; i++) {
#pragma omp parallel for shared(A,B,C,i) private(j,k,sum) schedule(static) 
      for (j = 0; j < N; j++) {
        sum = 0;
        for (k=0; k < N; k++) {
          sum += A[i][k]*B[k][j];
        }
        C[i][j] = sum;
      }
    }
    end = omp_get_wtime(); //end time measurement
  }
  printf("Time of computation: %f seconds\n", (end-start)/10);
  /*  
      for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
      printf("%f", C[i][j]);
      }
      printf("\n");
      }
   */
  return(0);
}
