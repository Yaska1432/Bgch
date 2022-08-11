#include <stdio.h>
#include <string.h>
#define LEN 1234
#include "f.h"

static int isCorrect (char * s)
{
	char * pos;

	if (strlen (s) == 0)
		return 0;
	
	for (pos = strstr (s, "\\<"); pos; pos = strstr (pos + 2, "\\<"))
		if (pos && (s != pos))
			return 0;
	return 1;		
}

int f1 (char * name_a, char * name_b, char * s, char * t)
{
	FILE * fa, * fb;
	char buf[LEN], * pos;
	int count = 0;	

	fa = fopen (name_a, "r");
	if (!fa)
	{
		return ERROR_OPEN;	
	}
	fb = fopen (name_b, "w");
	if (!fb)
	{
		fclose (fa);
		return ERROR_OPEN;
	}
	if (!isCorrect (s))
	{
		fclose(fa), fclose (fb);
		return -3;
	}

	printf ("s - корректна\n");

	while (fgets (buf, LEN, fa))
	{
		if (strlen (s) == 1)
		{
                        if (strcspn (buf, s) == strlen (buf)) {}
			else
			{
				fprintf (fb, "%s", buf);
				count++;
			}

		}
		else
		{
			if ((s[0] == '\\') && (s[1] == '<'))
			{
				pos = strstr (buf, s + 2);

				if (pos)
				{
					if ((pos == buf) || (strspn (pos - 1, t) > 0))
					{
						fprintf (fb, "%s", buf);
						count++;
					}

				}
			}
			else 
			{
				if (strstr (buf, s))
				{
					fprintf (fb, "%s", buf);
					count++;
				}

			}

		}

	}

	if (!feof (fa))
	{
		fclose(fa), fclose (fb);
		return ERROR_READ;
	}

	return count;
}
