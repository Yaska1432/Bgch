#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "matrix.h"

int main (int argc, char * argv[])
{
	int n = 0, m = 0, i, k;
	double * a, * x0, * x, *b, *r;
	double time, r1, r2;
	char * nameA = 0, * nameX = 0;
	if (!(((argc == 3) || (argc == 5)) && (m = atoi (argv[1])) > 0 && (n = atoi (argv[2])) > 0))
	{
		printf ("Incorrect input\n");
		return 1;
	}
	if (argc == 5)
	{
		nameX = argv[4];
		nameA = argv[3];
	}
	if (!((a = (double *)malloc(n*n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		return 2;
	}
	if (!((x0 = (double *)malloc(n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		free(a);
		return 2;
	}
	if (!((x = (double *)malloc(n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		free(a);
		free(x0);
		return 2;
	}
	if (!((b = (double *)malloc(n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		free(a);
		free(x0);
		free(x);
		return 2;
	}
	if (!((r = (double *)malloc(n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		free(a);
		free(x0);
		free(x);
		free(b);
		return 2;
	}
	if (nameA && nameX)
	{
		int ret;
		ret = read_matrix (a, n, n, nameA);
		if (ret == SUCCESS) ret = read_matrix (x0, n, 1, nameX);
		if (ret != SUCCESS)
		{
			switch (ret)
			{
				case ERROR_OPEN:
				printf ("cannot open\n");
				break;
				case ERROR_READ:
				printf ("cannot read\n");
				break;
				default:
				printf ("unknown error\n");
			}
			free(a);
			free(x0);
			free(x);
			free(b);
			free(r);
			return 3;
		}
	}
	else
	{
		init_vector(x0, n);
		init_matrix(a, n, n);
	}
	for (i = 0; i < n; i++)
	{
		b[i] = 0;
		for (k = 0; k < (n+1)/2; k++)
		{
			b[i] += a[i*n + 2*k];
		}
	}
	for (i = 0; i < n; i++)
	{
		if (fabs(a[i*n+i]) < 10e-14)
		{
			printf ("Division by zero");
			return 0;
		}
	}
	printf ("\na:"); print_matrix (a, n, n);
	printf ("\nx:"); print_matrix (x0, n, 1);
	printf ("\nb:"); print_matrix (b, n, 1);
	time = clock();
	f5 (a, x0, b, x, r, n, m);
	time = clock() - time;
	r1 = norm1 (a, x0, b, n);
	r2 = norm2 (x0, n);
	printf ("\nres_vector:"); print_matrix (x0, n, 1);
	printf ("\nR1 = %e", r1);
	printf ("\nR2 = %e", r2);
	printf ("\nElapsed = %.2lf\n", time/CLOCKS_PER_SEC);
	free(a);
	free(x0);
	free(x);
	free(b);
	free(r);
	return 0;
}
