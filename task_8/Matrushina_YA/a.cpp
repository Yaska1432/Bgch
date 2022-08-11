#include <stdio.h>
#include <string.h>
#include <new>
#include <time.h>
#include "list_node.h" 
#include "list.h"
#include "condition.h"
#include "record.h"
#include "command.h"
# include "ordering.h"
# include "list2.h"
# include "list_node2.h"
# include "command_type.h"
# include "database.h"
# include "hash_list_node.h"
# include "hash_list.h"
# include "hash.h"
# include "container.h"


int main(int argc, char * argv[])
{
    char *file_in = nullptr;
    int res = 0;
    double time_;
	char *s = nullptr;
	char file_config[LEN];
	char buf[LEN];
	char BUF[LEN];
    read_status r;
	int k = 0;
	database DATA;
    if( !(argc == 2))
    {
        printf("Usage %s file_in\n", argv[0]);
        return -1;
    }
    
    file_in = argv[1];
	strcpy(file_config,argv[0]);
    if (!DATA.readConfig (file_config))
	   {printf("Read error in config.txt\n"); return -1;}
	//time_ = clock ();
    r = DATA.read(file_in);
	//time_ = (clock()-time_)/CLOCKS_PER_SEC;
	//printf ("Elapsed = %.2f\n",time_);
	if (r != read_status::success)
        {
            switch(r)
            {
				case read_status::open :
					printf("Open error\n");
                    break;
				case read_status::read :
					printf("Read error\n");
                    break;	
				case read_status::eof :
					printf("Eof error\n");
                    break;
				case read_status::memory :
					printf("Memory error\n");
                    break;	
                default:
                    printf("Unknown error\n");
                    break;
            }
            return 0;
        }
  time_ = clock ();
  while (fgets(buf,LEN,stdin))
  {  
	 for (int j = 0; buf[j] && k < LEN; j++, k++)
		 {
			 BUF[k] = buf[j];
			 if (buf[j] == '\n')
			     {BUF[k] = '\0';break;}
		 } 
	
	 k = 0; s = BUF; int ans = 0;
	 while(BUF[k])
	{
		 if (BUF[k] == ';')
		 {   
			 BUF[k] = '\0';
			 command com;
             if(com.PARSE(s))
	           { 
				 
				 ans = DATA.APLY(com);
				 
				 if (ans<0)
				     {break;}
                 res += ans;
			   }
             
			 BUF[k] = ';'; k++; s = BUF+k;
		 }
		 else k++;
	 }
	 if (ans<0)
		 break;
	 if(s[0])
	 {   
		 k = 0;
		 for (int j = 0; s[j] && k < LEN; j++, k++)
		 {
			 BUF[k] = s[j];
			 if (s[j] == '\n')
			   {BUF[k] = ' ';k++;break;}
		 }
		 BUF[k] = '\0';
		
		 
	 }
	 else k = 0;
	
    }
	time_ = (clock()-time_)/CLOCKS_PER_SEC;
	printf ("%s : Result = %d Elapsed = %.2f\n", argv[0],res, time_);
	return 0;
}

