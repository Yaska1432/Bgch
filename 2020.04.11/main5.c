#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix.h"

int main (int argc, char * argv[])
{
	int n, m;
	double * a;
	double time;
	char * name = 0;
	if (!(((argc == 3) || (argc == 4)) && (m = atoi (argv[1])) > 0 && (n = atoi (argv[2])) > 0))
	{
		printf ("Incorrect input\n");
		return 1;
	}
	if (argc == 4) name = argv[3];
	if (!((a = (double *)malloc(n*m*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		return 2;
	}
	if (name)
	{
		int ret;
		ret = read_matrix (a, m, n, name);
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
			return 3;
		}
	}
	else init_matrix(a, m, n);
	print_matrix (a, m, n);
	time = clock();
	f5 (a, m, n);
	time = clock() - time;
	print_matrix (a, m, n-1);
	printf ("\nElapsed = %.2lf\n", time/CLOCKS_PER_SEC);
	free(a);
	return 0;
}
