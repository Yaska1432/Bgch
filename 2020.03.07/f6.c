#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define MAXIT 1000000

int get_count (int count)
{return count;}

int f6 (double(*f)(double), int m, double * d, double a, double b, double eps, double *x)
 {
     double x1 = 0, max, f1;
     int it = 0, i, imax;
     double *px = d, *pxx = d + m + 1, *py = d + 2*m + 2;
     for (i = 0; i < m+1; i++)
     {
        px[i] = a + i*(b-a)/m;
        pxx[i] = a + i*(b-a)/m;
        py[i] = f(a+i*(b-a)/m);
     }
     for (it = 0; it < MAXIT; it++)
     {
        it++;
        imax = 0;
        if (!Newt(pxx, py, m+1, &x1)) return -3;
        max = fabs(py[0]);
        for (i = 1; i < m+1; i++)
        {
            if (fabs(py[i]) > max) {max = fabs(py[i]); imax = i;}
        }
        f1 = f(x1);
        if (fabs(py[imax]) < fabs(f1)) return -3;
        px[imax] = x1;
        py[imax] = f1;
        if (fabs(f1) < eps)
        {
            x1 = px[imax];
            break;
        }
        rewrite(px, pxx, m+1);
     }
     *x = x1;
     return it;
}

int Newt (double * ar1, double * ar2, int n, double *p)
{
    int i, k, step = 1;
    double m = 0;
    double eps = 10e-20;
    for (k = n-1; k > 0; k--)
    {
        for (i = 0; i < k; i++)
        {
            if (fabs(ar2[n-1-i] - ar2[n-1-i-step]) < eps) return -1;
            ar1[n-1-i] = (ar1[n-1-i] - ar1[n-1-i-1])/(ar2[n-1-i] - ar2[n-1-i-step]);
        }
        step++;
    }
    m = ar1[n-1];
    for (i = n-1; i > 0; i--)
    {
        m *= (-ar2[i-1]);
        m += ar1[i-1];
    }
    *p = m;
    return 1;
}

void rewrite(double *a, double*b, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
}
