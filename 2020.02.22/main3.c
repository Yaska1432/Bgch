#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "f.h"

int main(int argc, const char * argv[])
{
    const char * name1, * name2;
    const char *s;
    const char *t;
    int res = 0, ls;
    double timer;
    if (argc != 5)
    {
        printf ("Not enough information");
        return 1;
    }
    name1 = argv[1];
    name2 = argv[2];
    s = argv[3];
    t = argv[4];
    ls = (int)strlen(s);
    timer = clock();
    res = f3 (ls, name1, name2, s, t);
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
 
