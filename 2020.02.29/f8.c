#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#include "f.h"
#include "common_array.h"

double f8 (double x, double eps)
{
    int i, f = 0, k = 0, sgn = -1;
    double f1, f2, a, y;
    if (x >= 2)
    {
        while (x >= pow_(2, k)) k++;
        k--;
        a = x/pow_(2, k);
    }
    else if (x < 1)
    {
        k=1;
        while (x <= 1/pow_(2, k-1)) k++;
        k--;
        f = 1;
        a = x*pow_(2,k);
    }
    else a = x;
    y = a - 1;
    f1 = y;
    f2 = sgn*pow_(y, 2)/2;
    f1+=f2;
    for (i = 3; fabs(f2) > eps; i++)
    {
        sgn*=(-1);
        f2 = sgn*pow_(y, i)/i;
        f1+=f2;
    }
    printf("f1 = %lf\n", f1);
    if (f) f1 -= k*M_LN2;
    else f1 += k*M_LN2;
    return f1;
}
