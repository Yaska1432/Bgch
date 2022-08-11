#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define MAXIT 1000000

int get_count (int count)
{return count;}
int f1 (double(*f)(double), double a, double b, double eps, double *x)
{
    double fa, fb, c = 0, fc;
    int it;
    fa = f(a); fb = f(b);
    for (it = 1; (it < MAXIT) && (fabs(a - b) > eps); it++)
    {
        if (fabs(fa) < eps)
        {c = a; break;}
        if (fabs(fb) < eps)
        {c = b; break;}
        c = (a + b)/2;
        if (((a <= c) && (a >= c)) || ((b <= c) && (b >= c))) return c;
        fc = f(c);
        if (fabs(fc) < eps) break;
        if (fc*fa < 0)
        {
            b = c;
            fb = fc;
        }
        else if (fc*fb < 0)
        {
            a = c;
            fa = fc;
        }
        else break;
    }
    *x = c;
    return it;
}
