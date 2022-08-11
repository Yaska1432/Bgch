#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234
static int count = 0;

static int test_f6 (char * b, const char * s)
{
    int i = 0, j = 0, ks, kb;
    int lb = (int)strlen(b);
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
        if (b[i] == '+')
        {
            if ((s[j] == '\\') && (s[j+1] == '+'))
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
        
        else if ((s[j] == '+') && (b[i] == s[j-1]))
        {
            ks = 0; kb = 0;
            while ((s[j] == s[j-1]) || (s[j] == '+'))
            {
                if(!(s[j] == '+')) ks++;
                j++;
            }
            while (b[i] == s[j-1]) i++;
            kb+=i;
            if ((ks == kb) && (ks == 0)) i++;
            else if (kb >= ks)
            {
                i+=kb;
                if (i >= (lb-2)) return 1;
            }
            else if (!s[j]) return 0;
            i++;
        }
        else if (b[i] == s[j])
        {
            i++;
            j++;
        }
        else return 0;
    }
    if (s[j] == '+') return 1;
    if (s[j]) return 0; 
    else return 1;
}

int f6 (const char * name1, const char * name2, const char * s)
{
    FILE * fp1;
    FILE * fp2;
    char buf[LEN];
    if (!(fp2 = fopen(name2, "w")))
        return ERROR_OPEN;
    if (!(fp1 = fopen(name1, "r")))
    {
        fclose (fp2);
        return ERROR_OPEN;
    }
    
    while (fgets(buf, LEN, fp1))
    {
        if (test_f6(buf, s))
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
