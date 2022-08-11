#include <math.h>
#include "matrix.h"

double f2 (double * a, int m, int n)
{
    int i, j;
    double max = 0, s = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            s += fabs(a[j * n + i]);
        }
        if (s > max) max = s;
        s = 0;
    }
    return max;
}
