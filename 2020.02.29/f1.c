#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

double f1 (int n, double x0, double * x, double * y)
{
    double g = 1, l = 0;
    int i, j;
    double eps = 10e-6;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (fabs(x[i]-x[j]) < eps) continue;
            g *= ((x0 - x[j])/(x[i] - x[j]));
        }
        l += g*y[i];
        g = 1;
    }
    return l;
}
