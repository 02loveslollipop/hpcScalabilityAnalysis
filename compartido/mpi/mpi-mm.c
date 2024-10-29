/**********************************************************************                                                                                      
 * MPI-based matrix multiplication AxB=C                                                                                                                     
 *********************************************************************/

#include <stdio.h>
#include <time.h>
#include "mpi.h"
#include <stdlib.h>

MPI_Status status;

int main(int argc, char *argv[])
{

  int numtasks,taskid,numworkers,source,dest,rows,offset,i,j,k;

  double start, stop;
  float dot;

  int N = atoi(argv[1]);
  //allocate memory for matrices
  int **a = (int **)malloc(N*sizeof(int *));
  int **b = (int **)malloc(N*sizeof(int *));
  int **c = (int **)malloc(N*sizeof(int *));

  for (int i=0; i<N; i++)
  {
	  a[i] = (int *)malloc(N*sizeof(int));
	  b[i] = (int *)malloc(N*sizeof(int));
	  c[i] = (int *)malloc(N*sizeof(int));
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  numworkers = numtasks-1;
  /*---------------------------- master ----------------------------*/
  if (taskid == 0) {
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
          a[i][j] = (int)(rand() % 4) + 1;
          b[i][j] = (int)(rand() % 4) + 1;
      }
    }

    start = MPI_Wtime();

    /* send matrix data to the worker tasks */
    rows = N/numworkers;
    offset = 0;

    for (dest=1; dest<=numworkers; dest++)
    {
      MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&a[offset][0], rows*N, MPI_INT,dest,1, MPI_COMM_WORLD);
      MPI_Send(&b[0][0], N*N, MPI_INT, dest, 1, MPI_COMM_WORLD);
      offset = offset + rows;
    }

    /* wait for results from all worker tasks */
    for (i=1; i<=numworkers; i++)
    {
      source = i;
      MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&c[offset][0], rows*N, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
    }

    stop = MPI_Wtime();

    // //printf("Here is the result matrix:\n");
    // for (i=0; i<N; i++) {
    //   for (j=0; j<N; j++)
    //     //printf("%6.2f   ", c[i][j]);
    //   //printf ("\n");
    // }

    printf("%lf\n", stop - start);
  }

  /*---------------------------- worker----------------------------*/
  if (taskid > 0) {
    int **aW = (int **)malloc(N*sizeof(int *));
    int **bW = (int **)malloc(N*sizeof(int *));
    int **cW = (int **)malloc(N*sizeof(int *));

    for (int i=0; i<N; i++)
    {
      aW[i] = (int *)malloc(N*sizeof(int));
      bW[i] = (int *)malloc(N*sizeof(int));
      cW[i] = (int *)malloc(N*sizeof(int));
    }

    source = 0;
    MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&aW[0][0], rows*N, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&bW[0][0], N*N, MPI_INT, source, 1, MPI_COMM_WORLD, &status);

    

    /* Matrix multiplication */
    for (i=0; i<N; i++)
      for (j=0; j<rows; j++) {
        dot = 0.0;
        for (k=0; k<N; k++){
          dot += aW[i][k] * bW[k][j];
        }
        cW[i][j] = (int)dot;
      }


    MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&cW[0][0], rows*N, MPI_INT, 0, 2, MPI_COMM_WORLD);
  }
  //free the memory allocated for the matrix
  for(int i=0; i<N; i++)
  {
	  free(a[i]);
	  free(b[i]);
	  free(c[i]);
  }
  free(a);
  free(b);
  free(c);
  MPI_Finalize();
}
