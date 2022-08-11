#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

int matrix (double * a, int n, int k, const char * name)
{
	int ret;
	if (name)
	{
		ret = read_matrix (a, n, n, name);
		if (ret != SUCCESS)
		{
			switch (ret)
			{
				case ERROR_OPEN:
				printf ("Cannot open\n");
				break;
				case ERROR_READ:
				printf ("Cannot read\n");
				break;
				default:
				printf ("Unknown error\n");
			}
			return 0;
		}
	}
	else
	{
		init_matrix(a, n, n, k);
	}
	return 1;
}


int read_matrix (double * a, int n, int m, const char * name)
{
	FILE * fp;
	int i, len = n*m;
	if (!(fp = fopen (name, "r"))) return ERROR_OPEN;
	for (i = 0; i < len; i++)
	{
		if (fscanf (fp, "%lf", a + i) != 1)
		{
			fclose (fp);
			return ERROR_READ;
		}
	}
	fclose (fp);
	return SUCCESS;
}

double fun (int n, int i, int j, int k)
{
	i++; j++;
	if (k == 1) return n + 1 - (i > j ? i:j);
	if (k == 2) return (i > j ? i:j);
	if (k == 3) return ((i-j) > (j-i) ? (i-j):(j-i));
	if (k == 4) return (1.0/(i+j-1));
	else return 0;
}

void init_matrix (double * a, int m, int n, int k)
{
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			a[i*n + j] = fun(n,i,j,k);
}

void init_E (double * a, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i == j) a[i*n+i] = 1;
			else a[i*n+j] = 0;
}

void init_vector (double * a, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		a[i] = 1;
	}
}


void print_matrix (double * a, int m, int n)
{
	int i, j;
	printf ("\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			printf (" %10.3e", a[i*n + j]);
		}
		printf("\n");
	}
}

void print_vector (double * x, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf (" %10.3e", x[i]);
	}
}

double norm (double * a, double * x, int n)
{
    int i, j;
    double s = 0, max = 0, numen;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            s += fabs(a[j * n + i]);
        }
        if (s > max) max = s;
        s = 0;
    }
    numen = num (a, x, n);
    return numen/max;
}

double num (double * a, double * b, int n)
{
    int i, j, l;
    double s = 0, max = 0, t = 0;
    for (i = 0; i < n*n; i++)
    {
        for (j = 0; j < n; j++)
        {
            l = (int)(i/n);
            t += a[(i%n)*n+j] * b[j*n+l];
        }
        if (i == 0 || (i%(n+1) == 0 && i > n)) t--;
        s += fabs(t);
        t = 0;
        if (((i + 1)%n == 0) && (i > (n - 2)))
        {
        	if (s > max) max = s;
        	s = 0;
        }
    }
    return max;
}

