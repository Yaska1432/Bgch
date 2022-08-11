#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234
static int count = 0;

static int test_f3 (int num, char * b, char * s, const char * t)
{
    int i = 0, k = 0, j = 0, pos;
    for (i = 0; b[i]; i++)
    {
        if (b[i] == '\n')
        {
            b[i] = '\0';
            break;
        }
    }
    for (i = 0; b[i]; i++)
    {
        pos = strspn (b + i, t);
        if (pos)
        {
            b[i] = '\0';
            i--;
        }
        i += pos;
    }
    pos = strlen(b);
    for (i = 0; b[i]; i++)
    {
        i += strspn(b + i, t);
        for (k = 0; k < num; k++)
        {
            if (!strcmp(b + i, s + j)) return 1;
            else j+=strlen(s + j)+1;
        }
        i+=strlen(b + i)+1;
        j = 0;
        i+=strspn(b+i+1, t);
    }
    return 0;
}

int f3 (int ls, const char * name1, const char * name2, const char * s, const char * t)
{
    FILE * fp1;
    FILE * fp2;
    char buf[LEN];
    char bufS[ls];
    char b[LEN];
    int i, j, num = 0, pos = 0, fl = 0, shift = 0, f = 1, flag = 0;
    for (i = 0, j = 0; s[j]; i++, j++)
    {
        flag = 0;
        pos = strspn (s + j, t);
        j += pos;
        if (pos)
        {
            bufS[i] = '\0';
            j--;
        }
        else
        {
            bufS[i] = s[j];
            flag = 1;
            num++;
        }
    }
    if (flag)
    {
        bufS[i] = '\0';
    }
    fl = 0;
    {
        if (bufS[i] == 0) shift++;
        else if (f)
        {
            bufS[i-shift] = bufS[i];
            f = 0;
            fl = 0;
        }
        else 
        {
            if (fl) bufS[i-shift] = bufS[i];
            else
            {
                bufS[i-shift] = '\0';
                bufS[i-shift+1] = bufS[i];
                fl = 1;
            }
        }
    }
    if (!(fp2 = fopen(name2, "w")))
        return ERROR_OPEN;
    if (!(fp1 = fopen(name1, "r")))
    {
        fclose (fp2);
        return ERROR_OPEN;
    }    
    while (fgets(buf, LEN, fp1))
    {
        strcpy(b, buf);
        if (test_f3(num, b, bufS, t))
        {
            fprintf (fp2, "%s\n", buf);
            count++;
        }
    }
    count++;
    if (!feof(fp1))
    {
        fclose(fp1);
        return ERROR_READ;
    }
    fclose (fp1);
    fclose (fp2);
    return count;
}
