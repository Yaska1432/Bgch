#include <stdio.h>
#include <stdlib.h>
#include "f.h"
#include "common_array.h"

int main(int argc, char * argv[])
{
    char * name;
    double x0, result;
    double * x, * y;
    int n = 0;
    int res = 0;
    if ((argc != 3) || (!sscanf(argv[2], "%d", &n)))
    {
        printf ("Incoorrect input\n");
        return 1;
    }
    else
    {
        sscanf(argv[2], "%d", &n);
        printf ("Input x0 = ");
        scanf("%lf", &x0);
        if (n < 0) {printf ("error, n < 0\n"); return -3;}
        x = (double *) malloc (n * sizeof (double));
        if (!x) 
        {
            printf ("memory allocation error\n");
            return 1;
        }
        y = (double *) malloc (n * sizeof (double));
        if (!y) 
        {
            free(x);
            printf ("memory allocation error\n");
            return 1;
        }
    }
    name = argv[1];
    res = read_array(name, x, y, n);
    if (res < 0)
    {
        switch (res)
        {
            case ERROR_OPEN:
                printf ("cannot open\n");
                break;
            case ERROR_READ:
                printf ("cannot read\n");
                break;
            default:
                printf ("unknown error\n");
        }
        free(x);
        free(y);
        return 0;
    }
    result = f2 (n, x0, x, y);
    printf ("Result = %lf\n", result);
    free(x);
    free(y);
    return 0;
}
 
 
