/*
 * pi_serial.c		3.1415926535897932384
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
	int i,n;
	double x, base, suma=0.0,pi;
	double inicio,fin;
	//~ printf("Ingrese n:");
	//~ scanf("%d",&n);
	//n=2000000000;

	if (argc != 2) {
		printf("No se ha especificado el valor de n\n");
		exit(1);
	}
	inicio = clock();
	n = atoi(argv[1]);
	base=1.0/(double)n;
	for(i=0;i<n;i++)
	{
		x= (i+0.5)*base;
		suma += 4.0/(1.0+x*x);
	}
	pi=suma*base;
	fin = clock();
	printf("%lf\n",(fin-inicio)/CLOCKS_PER_SEC);
	return 0;
}
