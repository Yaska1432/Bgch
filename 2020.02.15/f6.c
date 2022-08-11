#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
#define LEN 1234

static int change_string6 (char *s,int s_len)
{ int flag1 = 0;int j = 0; int i = 0;int flag;
    if (((s[s_len-1])== '$')&&((s[s_len-2])!= '\\'))
 {flag1 = 1;s[s_len-1]='\0';}

    while (s[j]!='\0')
{
    s[i]=s[j];
    if (s[i]=='\\')
{ if (s[j+1]=='\\')
{if (flag==0)
{flag=1; j++;continue;}
else
{flag=0; i++;j++;continue;} }
if (s[j+1]=='$')
{j++;
if (flag==1)
{flag=0;i++;}
continue;}
j++;i++;flag=0;}
else {j++;i++;flag=0;}} s[i]='\0';
return flag1;
}



static int test_f6 (char *buf, char *s,FILE *name, int flag, int s_len)
{
   int buf_len = strlen (buf);
   if (flag==1)
   {
     if (strcmp(buf+buf_len - s_len,s)==0)
     {fprintf (name,"%s\n", buf);return 1; }}
   else
   { if (strstr(buf,s))
     {fprintf (name,"%s\n", buf);return 1; }}
return 0;
}



int f6 (const char *name1 ,const char *name2, char *s)
{
  FILE *fp;
  FILE *ff;int i = 0;
  int res = 0;int flag;int s_len;
  char buf [LEN];
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  s_len = strlen (s);
  flag=change_string6 (s,s_len);
  s_len = strlen (s);
  printf ("%s",s);
  while (fgets (buf, LEN, fp))
  {
    for (i=0;buf[i];i++)
       {if (buf[i]=='\n')
       { buf[i]='\0';break;}}

    if ( test_f6(buf,s,ff,flag,s_len))
    res ++;


  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
  printf("\n\n");
 return res;
}
