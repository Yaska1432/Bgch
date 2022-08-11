#include <stdio.h>
#include <math.h>
#include "matrix.h"

double f6 (double * a, double * b, int m, int n)
{
    int i, j, l;
    double s = 0, max = 0, t = 0;
    for (i = 0; i < m*m; i++)
    {
        for (j = 0; j < n; j++)
        {
            l = (int)(i/m);
            t += a[(i%m)*n+j] * b[j*m+l];
        }
        if (i == 0 || (i%(m+1) == 0 && i > m)) t--;
        s += fabs(t);
        t = 0;
        if (((i + 1)%m == 0) && (i > (m - 2)))
        {
        	if (s > max) max = s;
        	s = 0;
        }
    }
    return max;
}
