#include <math.h>
#include <stdio.h>
#include "matrix.h"

void f10 (double * a, int m, int n)
{
	int i, j, i_min = 0, j_min = 0, shift = 0, k;
    	double min = 0, s = 0, sum1 = 0, sum2 = 0;
    	for (i = 0; i < n*m; i++)
    	{
    		if (i%n == 0)
    		{
    			for (j = 0; j < n; j++) sum1 += a[(i/n) * n + j];
    			sum1 /= n;
    		}
    		for (j = 0; j < m; j++)
    		{
    			sum2 += a[j * n + (i%n)];
    			sum2 /= m;
    		}
    		for (j = 0, k = 0; j < n || k < m; j++, k++)
    		{
    			if (j < n) s += pow(a[(int)i/n * n + j] - sum1, 2);
    			if (k < m) s += pow(a[k * n + (i%n)] - sum2, 2);
    		}
    		if (i == 0) min = s;
    		else if (s < min)
    		{
    			min = s;
    			i_min = (int)i/n;
    			j_min = i%n;	
    		}
    		s = 0;
        }
        for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == i_min || j == j_min) shift++;
			else a[i*n+j-shift] = a[i*n+j];
		}
	}
}

