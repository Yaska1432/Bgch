#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "f.h"

int main(int argc, const char * argv[])
{
    const char * name1, * name2;
    const char *s;
    const char *r;
    int res = 0;
    double timer;
    if (argc != 5)
    {
        printf ("Not enough information");
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    r = argv[4];
    timer = clock();
    res = f1 (name1, name2, s, r);
    timer = (clock() - timer)/CLOCKS_PER_SEC;
    if (res < SUCCESS)
    {
        switch (res)
        {
            case ERROR_OPEN:
                printf ("cannot open");
                break;
            case ERROR_READ:
                printf ("cannot read");
                break;
            default:
                printf ("unknown error");
        }
    }
    printf ("Result = %d\n", res);
    printf("Elapsed = %.2lf\n", (double) timer);
    return 0;
}
