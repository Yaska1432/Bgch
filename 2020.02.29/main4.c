#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include "f.h"
#include "common_array.h"

int main(int argc, char * argv[])
{
    char * name;
    double x0, result;
    double * x, * y, * d;
    int n = 0;
    int res = 0;
    if ((argc != 4) || (!sscanf(argv[2], "%d", &n)))
    {
        printf ("Incoorrect input\n");
        return 1;
    }
    else
    {
        sscanf(argv[2], "%d", &n);
        sscanf(argv[3], "%lf", &x0);
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
        d = (double *) malloc (n * sizeof (double));
        if (!d) 
        {
            free(x);
            free(y);
            printf ("memory allocation error\n");
            return 1;
        }
    }
    name = argv[1];
    res = read_array_new(name, x, y, d, n);
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
        free(d);
        return 0;
    }
    result = f4 (n, x0, x, y, d);
    printf ("Result = %.18elf\n", result);
    free(x);
    free(y);
    free(d);
    return 0;
}
 
