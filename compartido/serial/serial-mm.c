#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* modo de uso: ./serial-mm n
 * n es un entero DIM
 * matrix multiply
 * *
 * * c[i][j]= a_row[i] dot b_col[j] for all i,j
 * * a_row[i] -> a[i][0 .. DIM-1]
 * * b_col[j] -> b[0 .. DIM-1][j]
 * *
 * */

int main(int argc, char const *argv[])
{
  long inicio,fin;
  if (argc!=2)
  {
	  printf("usage: %s n\n",argv[0]);
	  exit(1);
  }

  int n = atoi(argv[1]);
  //allocate memory for matrices
  int **a = (int **)malloc(n*sizeof(int *)); 
  int **b = (int **)malloc(n*sizeof(int *));
  int **c = (int **)malloc(n*sizeof(int *));
  for (int i=0; i<n; i++)
  {
	  a[i] = (int *)malloc(n*sizeof(int));
	  b[i] = (int *)malloc(n*sizeof(int));
	  c[i] = (int *)malloc(n*sizeof(int));
  }

  int i,j,k;
  float dot;  
  for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			a[i][j] = (int)(rand()%4)+1;
			b[i][j] = (int)(rand()%4)+1;
		}
	}
  inicio = clock();
  for(i=0;i<n;i++) {
    for(j=0;j<n;j++) {
		dot=0.0;
		for(k=0;k<n;k++)
			dot += a[i][k]*b[k][j];
		c[i][j]=dot;
	}
  }
  fin = clock();
  printf("%lf\n",(double)(fin-inicio)/CLOCKS_PER_SEC);
  //free the memory allocated for the matrix
  for(int i=0; i<n; i++)
  {
	  free(a[i]);
	  free(b[i]);
	  free(c[i]);
  }
  free(a);
  free(b);
  free(c);
}
