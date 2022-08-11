#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix.h"

int main (int argc, char * argv[])
{
	int n, m;
	double * a, *b;
	double time, res;
	char * name1 = 0, * name2 = 0;
	if (!(((argc == 3) || (argc == 5)) && (m = atoi (argv[1])) > 0 && (n = atoi (argv[2])) > 0))
	{
		printf ("Incorrect input\n");
		return 1;
	}
	if (argc == 5)
	{
		name1 = argv[3];
		name2 = argv[4];
	}
	if (!(a = (double *)malloc(n*m*sizeof(double))))
	{
		printf ("Not enough memory1\n");
		return 2;
	}
	if (!((b = (double *)malloc(m*n*sizeof(double)))))
	{
		printf ("Not enough memory2\n");
		free(a);
		return 2;
	}
	if (name1)
	{
		int ret1, ret2;
		ret1 = read_matrix (a, m, n, name1);
		if (name2)
		{
			ret2 = read_matrix (b, n, m, name2);
			if (ret2 != SUCCESS) ret1 = ret2;
		}
		if (ret1 != SUCCESS)
		{
			switch (ret1)
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
			free(b);
			return 3;
		}
	}
	else
	{
		init_matrix(a, m, n);
		init_matrix (b, n, m);
	}
	print_matrix (a, m, n);
	printf("\n");
	print_matrix (b, n, m);
	printf("\n");
	time = clock();
	res = f5 (a, b, m, n);
	time = clock() - time;
	printf ("Result = %lf\n", res);
	printf ("Elapsed = %.2lf\n", time/CLOCKS_PER_SEC);
	free(a);
	free(b);
	return 0;
}
