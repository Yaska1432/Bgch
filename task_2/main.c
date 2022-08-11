#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix.h"

int main (int argc, char * argv[])
{
	int n = 0, m = 0, k;
	double * a, * x, *b;
	double time;
	char * name = 0;
	if (!((argc == 5 || argc == 4) && (n = atoi (argv[1])) > 0 && (m = atoi (argv[2])) > 0 && (sscanf(argv[3], "%d", &k))))
	{
		printf ("Incorrect input\n");
		return 1;
	}
	if ((k == 0 && argc == 5) || (k < 5 && k > 0))
	{
		name = argv[4];
	}
	else
	{
		printf ("Incorrect input\n");
		return 1;
	}
	if (!((a = (double *)malloc(n*n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		return 2;
	}
	if (!((x = (double *)malloc(n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		free(a);
		return 2;
	}
	if (!((b = (double *)malloc(n*n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		free(a);
		free(x);
		return 2;
	}
	if (!(matrix (a, n, k, name)))
	{
		free(a);
		free(x);
		free(b);
		return 0;
	}

	printf ("\nA =");
	print_matrix (a, m, n);
	time = clock();
	if (!(f(n, a, x, b)))
	{
		free(a);
		free(x);
		free(b);
		return 0;
	}
	time = clock() - time;
	matrix (a, n, k, name);
	printf ("\nresult =");
	print_vector(x, n);
	//res = norm (a, x, n);
	//printf ("\nA^{-1} =");
	//print_matrix (x, m, n);
	//printf ("\nResidual = %e\n", res);

	printf ("\nElapsed = %.2lf\n", time/CLOCKS_PER_SEC);
	free(a);
	free(x);
	free(b);
	return 0;
}
