#include <stdio.h>
#include <string.h>
#define LEN 1234
#include "f.h"

static int isCorrect (char * s)
{
	char * pos;

	if (strlen (s) == 0)
		return 0;
	pos = strstr (s, "\\>");
	if (pos && ((s + strlen (s) - 2) != pos))
		return 0;
	return 1;		
}

int f2 (char * name_a, char * name_b, char * s, char * t)
{
	FILE * fa, * fb;
	char buf[LEN], s2[LEN], * pos;
	int count = 0, slen = strlen (s);	
	int difShift = 1;	

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

	strcpy (s2, s);
	s2[slen - 2] = '\0';


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
			if ((s[slen - 2] == '\\') && (s[slen - 1] == '>'))
			{

				for (pos = strstr (buf, s2); pos; pos = strstr (pos + difShift, s2))
				{
					if (((pos + strlen (s2) + 1) == (buf + strlen(buf))) || (strspn (pos + strlen (s2), t) > 0))
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
