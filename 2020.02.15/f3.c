//  f3.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234
static int count = 0;

static int test_f3 (int lt, int ls, char * b, const char * s, const char * t)
{
    int i = 0, j, f = 0;
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
        f = 0;
        for (j = 0; j < lt; j++)
        {
            if (b[i] == t[j])
            {
                f = 1;
                break;
            }
        }
        if (f) i++;
        else
        {
            f = 0;
            for (j = 0; j < ls; j++)
            {
                if (b[i] == s[j])
                {
                    f = 1;
                    break;
                }
            }
            if (f) i++;
            else return 0;
        }
    }
    return 1;
}

int f3 (const char * name1, const char * name2, const char * s, const char * t)
{
    FILE * fp1;
    FILE * fp2;
    char buf[LEN];
    int i, j;
    int ls = (int)strlen(s);
    int lt = (int)strlen(t);
    char bufS[ls];
    for (i = 0, j = 0; s[j]; i++, j++)
    {
        j += strspn (s + j, t);
        bufS[i] = s[j];
    }
    bufS[i] = 0;
    if (!(fp2 = fopen(name2, "w")))
        return ERROR_OPEN;
    if (!(fp1 = fopen(name1, "r")))
    {
        fclose (fp2);
        return ERROR_OPEN;
    }
    
    while (fgets(buf, LEN, fp1))
    {
        if (test_f3(lt, ls, buf, bufS, t))
        {
            fprintf (fp2, "%s\n", buf);
            count++;
        }
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
