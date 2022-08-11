//  f1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234
static int count = 0;

static int test_f1 (int ls, FILE * fp2, char * b, const char * s, const char * r)
{
    int i, flag = 0;
    char * position;
    for (i = 0; b[i]; i++)
    {
        if (b[i] == '\n')
        {
            b[i] = '\0';
            break;
        }
    }
    i = 0;

    while (b[i])
    {
        position = strstr (b + i, s);
        if (position)
        {
            flag = 1;
            while ((b + i) != position)
            {
                fprintf (fp2, "%c", b[i]);
                i++;
            }
            fprintf (fp2, "%s", r);
            i += ls;
        }
        else
        {
            fprintf (fp2, "%s", b + i);
            break;
        }
    }
    fprintf (fp2, "\n");
    if (flag) return 1;
    return 0;
}


int f1 (const char * name1, const char * name2, const char * s, const char * r)
{
    FILE * fp1;
    FILE * fp2;
    char buf[LEN];
    int ls = (int)strlen(s);
    if (!(fp2 = fopen(name2, "w")))
        return ERROR_OPEN;
    if (!(fp1 = fopen(name1, "r")))
    {
        fclose (fp2);
        return ERROR_OPEN;
    }
    while (fgets(buf, LEN, fp1))
    {
        if (test_f1 (ls, fp2, buf, s, r))
            count++;
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
