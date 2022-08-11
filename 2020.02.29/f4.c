#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include "f.h"

double f4 (int n, double x0, double * x, double * y, double * d)
{
    int i, j, d_ = 0, y_=0;
    double l = 0, p = 1;
    for (i = n-1; i > 0; i--)
    {
        y[i] = (y[i] - y[i-1])/(x[i] - x[i-1]);
    }

    for (j = 1; j < 2*n - 1; j++)
    {
        for (i = 2*n - 1; i > j; i--)
        {
            if (i & 1)
            {
                d[i/2] = (d[i/2] - y[i/2])/(x[i/2] - x[i/2 - 1 - d_]);
            }
            else
            {
                y[i/2] = (y[i/2] - d[i/2])/(x[i/2] - x[i/2 - 1 - d_]);
            }
            if (j & 1) y_++;
            else d_++;
        }
        l = y[0]; p = x0 - x[0];
        for (i = 2; i <= 2*n; i++)
        {
            if (i & 1)
            {
                l+=(y[(int)(i/2)]*p);
                p*=(x0 - x[(int)(i/2)]);
            }
            else
            {
                l+=(d[(int)(i/2)-1]*p);
                p*=(x0 - x[(int)(i/2)-1]);
            }
        }
    }
    return l;
}
