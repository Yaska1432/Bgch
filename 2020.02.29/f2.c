#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

double f2 (int n, double x0, double * x, double * y)
{
    int i, k, step = 1;
    double m = 0;
    for (k = n-1; k > 0; k--)
    {
        for (i = 0; i < k; i++)
        {
            y[n-1-i] = (y[n-1-i] - y[n-1-i-1])/(x[n-1-i] - x[n-1-i-step]);
        }
        step++;
    }
    m = y[n-1];
    for (i = n-1; i > 0; i--)
    {
        m *= (x0 - x[i-1]);
        m += y[i-1];
    }
    return m;
}
