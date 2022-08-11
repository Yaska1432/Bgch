#include <stdio.h>
#include "matrix.h"

void f8 (double * a, int m, int n)
{
	int i, j;
	double t;
	for (i = m-2; i > 0; i--)
	{
		t = a[(i+1)*n-1];
		for (j = n-2; j > 0; j--)
		{
			a[i*n+j] = (a[(i-1)*n+j] + a[(i+1)*n+j] + a[i*n+j-1] + t)/5;
			t = a[i*n+j];
		}	
	}
}
