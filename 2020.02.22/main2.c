#include <stdio.h>
#include <string.h>
#include <time.h>

#include "f.h"

int main (int argc, char * argv[])
{
	int result;
    clock_t timer;
    
    if (argc != 5)
    {
        printf ("Usage: %s <file_for_open> <file_for_write> <stringS> <stringT>\n", argv[0]);
        return 1;
    }
    timer = clock();
    result = f2 (argv[1], argv[2], argv[3], argv[4]);
    if (result < 0)
    {
        switch (result)
        {
            case ERROR_OPEN:
                printf ("Can't open file to read\n");
                return 1;
            case ERROR_READ:
                printf ("Can't read the %s\n", argv[1]);
                return 1;
            default:
                printf ("Unknown error\n");
                return 1;
        }
    }
    printf("Success: %d\n", result);
    
    timer = clock() - timer;
    printf("Elapsed %.2lf\n", (double) timer/CLOCKS_PER_SEC);  
    return 0;
}
