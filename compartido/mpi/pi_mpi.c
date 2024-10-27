/*
 * pi_serial.c		3.1415926535897932384
 * 
 */
#include <stdio.h>
#include <mpi.h>
#include <time.h>

int main(int argc,char **argv)
{
	int i,n,npr,pid;
	double x, base, suma=0.0,pi,pi_loc;
	
	
	double start, stop;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&pid);
	MPI_Comm_size(MPI_COMM_WORLD,&npr);

	start = MPI_Wtime();

	if(pid==0){
	//~ printf("\n Ingrese n:");
	//~ scanf("%d",&n);
	//n=2000000000;
	n = atoi(argv[1]);
	}
	
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	
	base=1.0/(double)n;
	for(i=pid;i<n;i+=npr)
	{
		x= (i+0.5)*base;
		suma += 4.0/(1.0+x*x);
	}
	pi_loc=suma*base;
	
	MPI_Reduce(&pi_loc,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(pid==0){
		stop = MPI_Wtime();
		printf("%lg\n",stop-start);
	}
	
	MPI_Finalize();
	return 0;
}
