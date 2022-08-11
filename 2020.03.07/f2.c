#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define MAXIT 1000000

int get_count (int count)
{return count;}

int f2 (double(*f)(double), double(*d)(double), double x0, double eps, double *x)
{
    double f0;
    int it;
    f0 = f(x0);
    for (it = 0; (it < MAXIT) && (fabs(f0) > eps); it++)
    {
        if (fabs(f0) < eps) break;
        if ((d(x0) <= 0) && (d(x0) >= 0)) return -3;
        x0 = x0 - f0/d(x0);
        f0 = f(x0);
    }
    *x = x0;
    return it;
}
