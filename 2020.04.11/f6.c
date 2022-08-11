#include <math.h>
#include <stdio.h>
#include "matrix.h"

void f6 (double * a, int m, int n)
{
	int i, j, i_max = 0, shift = 0;
    	double max = 0, s = 0;
    	for (i = 0; i < n; i++)
    	{
        	for (j = 0; j < m; j++)
        	{
        	    if (i != j) s += fabs(a[j * n + i]-a[i * n + i]);
        	}        	
        	if (s > max)
        	{
        		max = s;
        		i_max = i;
        	}
        	s = 0;
    	}
    	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j == i_max) shift++;
			else a[i*n+j-shift] = a[i*n+j];
		}
	}
}

