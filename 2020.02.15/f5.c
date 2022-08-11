#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234

static int test_f5 (const char * b, const char * s)
{
    int i, j;
    if (s[0] == '^')
    {
        for (i = 0, j = 1; b[i] && s[j]; i++, j++)
        {
            if ((b[i] == '\\') || (b[i] == '^'))
            {
                if ((s[j] == '\\') && (s[j + 1] == b[i]))
                {
                    j++;
                    continue;
                }
                else return 0;
            }
            if (b[i] != s[j]) return 0;
        }
        if (s[j]) return 0;
        else return 1;
    }
    else
    {
        if ((strlen(b) == strlen(s)) == strcspn(b, s) + 1) return 1;
        for (i = 0; b[i]; i++)
        {
            for (j = 0; s[j]; i++, j++)
            {
                if ((b[i] == '\\') || (b[i] == '^'))
                {
                    if ((s[j] == '\\') && (s[j + 1] == b[i]))
                    {
                        j++;
                        continue;
                    }
                    else return 0;
                }
                if (b[i] != s[j]) break;
            }
            if (!s[j]) return 1;
        }
        return 0;
    }
}


int f5 (const char * name1, const char * name2, const char * s)
{
	FILE * fp1, * fp2;
    char buf[LEN];
	int count = 0;
	if (!(fp1= fopen (name1, "r"))) return ERROR_OPEN;
	if (!(fp2 = fopen (name2, "w")))
	{
		fclose (fp1);
		return ERROR_OPEN;
	}

    while (fgets (buf, LEN, fp1))
    {
        if (test_f5 (buf, s))
        {
            count++;
            fprintf (fp2, "%s", buf);
        }
    }
        
	if (!feof (fp1))
    {
        fclose (fp1);
        fclose (fp2);
        return ERROR_READ;
    }
    fclose (fp1);
    fclose (fp2);
    return count;
}
