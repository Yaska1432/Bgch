#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define MAXIT 1000

int get_count (int count)
{return count;}

int f8 (double(*f)(double), double a, double b, double eps, double *x)
{
    double f0, f1, f2, x0, x1 = 0, x2 = 0, h;
    int it = 0, i;
    h = (b-a)/10;
    x0 = a;
    f0 = f(x0);
    x1 = a + h;
    f1 = f(x1);
    if (f0 > f1) {*x = f(a); return 0;}
    while (fabs(h) > eps)
    {
        it++;
        for (i = 2; i < 11; i++)
        {
            it++;
            if (fabs(h) < eps) break;
            x2 = a + i * h;
            f2 = f(x2);
            if (f1 > f2)
            {
                a = x0;
                b = x2;
                f0 = f2;
                h = (-h)/10;
                break;
            }
            else
            {
                x0 = x1;
                x1 = x2;
                f0 = f1;
                f1 = f2;
            }
            if ((fabs(x2-b) < eps) && (i == 10)) {*x = f(x2); return it;}
            else if (i == 10) return -3;
        }
    }
    *x = f(x1);
    return it;
}
