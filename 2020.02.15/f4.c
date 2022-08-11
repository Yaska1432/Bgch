//  f4.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234
static int count = 0;

static int test_f4 (int ls, int lt, char * b, const char * s, const char * t)
{
    int i = 0, k = 0, j, f = 0;
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
        if (f)
        {
            i++;
        }
        else
        {
            if (k == ls) return 1;
            if (b[i] == s[k])
            {
                if (k == ls) return 1;
                i++;
                k++;
            }
            else
            {
                i++;
                k = 0;
            }
        }
    }
    if (k == ls) return 1;
    return 0;
}

int f4 (const char * name1, const char * name2, const char * s, const char * t)
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
        bufS[i] = '\0';
        bufS[i+1] = s[j];
        i++
    }
    bufS[i] = 0;
    printf ("%s", bufS);
    if (!(fp2 = fopen(name2, "w")))
        return ERROR_OPEN;
    if (!(fp1 = fopen(name1, "r")))
    {
        fclose (fp2);
        return ERROR_OPEN;
    }
    
    while (fgets(buf, LEN, fp1))
    {
        if (test_f4(ls, lt, buf, bufS, t))
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
