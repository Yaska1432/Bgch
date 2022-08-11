#include "matrix.h"

void f10 (double * a, int m, int n)
{
	int i, j;
	double t;
	for (i = m - 2; i > 0; i--)
	{
		t = a[i*n];
		for (j = 1; j < n - 1; j++)
		{
			a[i*n+j] = (a[(i-1)*n+j] + a[(i+1)*n+j] + t + a[i*n+j+1])/5;
			t = a[i*n+j];
		}	
	}
}
