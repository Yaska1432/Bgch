//  f8.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234

static int count = 0;

static int test_f8 (int ls, int lr, FILE * fp2, char * b, const char * s, const char * r)
{
    int i, j, flag = 0;
    for (i = 0; b[i]; i++)
    {
        flag = 0;
        for (j = 0; j < ls; j++)
        {
            if (b[i] == s[j])
            {
                if (j < lr) 
                {
                    count++;
                    flag = 1;
                    fprintf (fp2, "%c", r[j]);
                }
            }
            if (flag) break;
        }
        if (!flag) fprintf (fp2, "%c", b[i]);
    }
    return 0;
}

int f8 (const char * name1, const char * name2, const char * s, const char * r)
{
    FILE * fp1;
    FILE * fp2;
    char buf[LEN];
    int ls = (int)strlen(s);
    int lr = (int)strlen(r);
    if (!(fp2 = fopen(name2, "w")))
        return ERROR_OPEN;
    if (!(fp1 = fopen(name1, "r")))
    {
        fclose (fp2);
        return ERROR_OPEN;
    }
    while (fgets(buf, LEN, fp1))
    {
        if ((test_f8 (ls, lr, fp2, buf, s, r) != 0)) return -4;
        fprintf(fp2, "\n");
    }
    if (!feof(fp1))
    {
        fclose(fp1);
        return ERROR_READ;
    }
    fclose (fp1);
    fclose (fp2);
    return count;
}
