#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234
static int count = 0;

static int test_f4 (int ls, char * b, const char * s)
{
    int i = 0, j = 0;
    for (i = 0; b[i]; i++)
    {
        if (b[i] == '\n')
        {
            b[i] = '\0';
            break;
        }
    }
    i = 0;
    j = 0;
    while (b[i])
    {
        if (j == ls) return 0;
        if (s[j] == '.')
        {
            j++;
            i++;
        }
        else if (b[i] == '.')
        {
            if ((s[j] == '\\') && (s[j+1] == '.'))
            {
                i++;
                j+=2;
            }
            else return 0;
        }
        else if (b[i] == '\\')
        {
            if ((s[j] == '\\') && (s[j+1] == '\\'))
            {
                i++;
                j+=2;
            }
            else return 0;
        }
        else if (s[j] == b[i]) 
        {
            j++;
            i++;
        }
        else return 0;
    }
    if (s[j]) return 0;
    else return 1;
}

int f4 (const char * name1, const char * name2, const char * s)
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
        if (test_f4(ls, buf, s))
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
