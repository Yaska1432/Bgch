#include <stlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix.h"

int main (int argc, char * argv[])
{
	int n, res;
	double * a;
	double time;
	char * name = 0;
	if (!((argc == 2 || (argc == 3) && (n = atoi (argv[1])) > 0)))
	{
		printf ("Incorrect input\n");
		return 1;
	}
	if (argc == 3) name = argv[2];
	if (!((a = (double *)malloc(n*n*sizeof(double)))))
	{
		printf ("Not enough memory\n");
		return 2;
	}
	if (name)
	{
		int ret;
		ret = read_matrix (a, n, n, name);
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
	else init_matrix(a, n, n);
	print_matrix (a, n, n);
	time = clock();
	res = f1 (a, n);
	time = clock() - time;
	printf ("Elapsed = %.2lf\n", time/CLOCKS_PER_SEC);
	printf ("Result = %d\n", res);
	free(a);
	return 0;
}