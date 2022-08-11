# include <stdio.h>
# include <string.h>
# include "record.h"
# include "command.h"
# include "condition.h"
# include "list_node.h"



char* cutOutWord(char *string, int *i, char *b)
{
  char *buf; 
  while (string[*i] == ' ' || string[*i] == '\n' || string[*i] == '\t' || string[*i] == ',')
		     (*i)++;
  buf = string+(*i);
  while (string[*i] && string[*i] != ' ' && string[*i] != '\n' && string[*i] != ',' && string[*i] != '\t')
		     (*i)++;
  *b = string[*i];
  string[*i] = '\0';	
  return buf;
}

char* cutOutWordInsert(char *string, int *i, char *b)
{
  char *buf; 
  while (string[*i] == ' ' || string[*i] == '\n' || string[*i] == '\t' || string[*i] == ',' || string[*i] == '(')
		     (*i)++;
  buf = string+(*i);
  while (string[*i] && string[*i] != ' ' && string[*i] != '\n' && string[*i] != ',' && string[*i] != '\t' && string[*i] != ')')
		     (*i)++;
  *b = string[*i];
  string[*i] = '\0';	
  return buf;
}

bool command::PARSE (char *string)
{
	int i = 0;
	if (!string)
		return false;
	while ((string[i] && string[i]==' ') || (string[i] && string[i]=='\t') || (string[i] && string[i] =='\n'))
		   i++;
	
	if (strncmp(string+i,"quit",4)==0)
	    {type = command_type::quit; return true;}
	if (strncmp(string+i,"insert ",7)==0)
	    {
		 type = command_type::insert; 
		 return parseInsert(string+i+7);
	    }
	if (strncmp(string+i,"select ",7)==0)
	{   
		
		type = command_type::select;
		return parseSelect(string+i+7);
	}
	if (strncmp(string+i,"delete",6)==0)
	{
		type = command_type::del;
		return parseDelete(string+i+6);
	}
	return false;
}


bool command::parseDelete(char *string)
{
	int i = 0;
	while ((string[i] && string[i]==' ') || (string[i] && string[i]=='\t') || (string[i] && string[i] =='\n'))
		   i++;
	if(!string[i])
		return true;
	if (strncmp("where",string+i,5) == 0)
	   {i+=5;return parseSearch(string+i,&i);}
	else
		return true;
}





bool command::parseInsert(char *string)
{
	int i = 0, ans;
	char buf;
	char *BUF;
	read_status res;
	
	BUF = cutOutWordInsert(string,&i,&buf);//input name
	if (!BUF[0])
		return false;
	
	res = (*this).init_name(BUF);
	string[i] = buf;
    if (res != read_status::success)
	   {return false;}
	BUF = cutOutWordInsert(string,&i,&buf);//input phone
	if (!BUF[0])
		return false;
	ans = getNumberByString(BUF);
	if (ans < 0)
		return false;
	res = (*this).init_phone(ans);
	string[i] = buf;
	
	BUF = cutOutWordInsert(string,&i,&buf);//input group
	if (!BUF[0])
		return false;
	ans = getNumberByString(BUF);
	if (ans < 0)
		return false;
	res = (*this).init_group(ans);
	string[i] = buf;
	
 return true;
}


bool command::parseConditionOutputFields(char *string)
{
	char *buf;char b;
	int i = 0,j = 0,flag, count_name = 0, count_phone = 0, count_group = 0, count_spec = 0;
	while (string[i])
	{
	  flag = 0;
	  buf = cutOutWord(string,&i,&b);
	  if (!buf[0])
	  {
		  if (count_name == 0 && count_phone == 0 && count_group == 0 && count_spec == 0)
			  return false;
		  else {return true;}
	  }
	  if (buf[0])
	   {
	     if (strcmp(buf,"name") == 0)
		    {
			  if(count_name == 0 && count_spec == 0)
			  {count_name++;order[j] = ordering::name;flag = 1;}
			  else return false;
		    }
	     if (strcmp(buf,"phone") == 0)
		    {
			  if (count_phone == 0 && count_spec == 0)
			  {count_phone++;order[j] = ordering::phone;flag = 1;}
			  else return false;
		    } 
		 if (strcmp(buf,"group") == 0)
		    {
			  if (count_group == 0 && count_spec == 0)
			  {count_group++;order[j] = ordering::group;flag = 1;}
			  else return false;
		    }
		 if (strcmp(buf,"*") == 0)
		    { 
		     if (count_group == 0 && count_name == 0 && count_phone == 0 && count_spec == 0)
			  {count_spec++;flag = 1;}
			  else return false;
		    }
		} 
		 string[i] = b;
		 j++;	
	     if (!flag)
		  return false;
	  } 
  return true;
}
	

bool command::parseSearch(char *string, int *i)
{
   int j = 0;
   char *buf;
   char b;
   int ans;
   field res;
   condition n;
   int counter_and = 0, counter_or = 0;
   while (string[j])
{
	while (string[j] == ' ' || string[j] == '\t' || string[j] == '\n')
	      j++;
	
	if (!string[j])
		return false;
	res = strncmp_field(string+j);
	if (f_field != field::none and f_field == res)
		return false;
	f_field = res;
	switch(f_field)
	{
		case field::name:
			 j += 4;
			 break;
		case field::phone:
			 j += 5;
			 break;
		case field::group:
			 j += 5;
	         break;
		default:
			return false;
	}
	
	if (!string[j])
		return false;
	
	while (string[j] == ' ' || string[j] == '\t' || string[j] == '\n')
	      j++;
	
	if (!string[j])
		return false;
	n = strcmp_condition(string+j, f_field, &j);
	if ( n == condition::none)
		return false;
	
	switch (f_field)
	{
		case field::name:
			c_name = n;
			break;
		case field::phone:
			c_phone = n;
			break;
		case field::group:
			c_group = n;
			break;
		default:
			return false;
	}
	
	while (string[j] == ' ' || string[j] == '\t' || string[j] == '\n')
	      j++;
	 
	 buf = string+j;
	 if (!string[j])
		 return false;
	
	 while (string[j] && string[j]!= ' ' && string[j] != '\t' && string[j] != '\n')
	      j++;
	
	 b = string[j];
	 string[j] = '\0';
	 switch(f_field)
	 {
		 case field::name:
			  if((*this).init_name(buf)==read_status::success)
			      break;
			  else
				  return false;
		 case field::phone:
			  ans = getNumberByString(buf);
			  if (ans < 0)
				  return false;
			  if((*this).init_phone(ans)==read_status::success)
			      break;
			  else
				  return false;
		case field::group:
			  ans = getNumberByString(buf);
			  if (ans < 0)
				  return false;
			  if((*this).init_group(ans)==read_status::success)
			     break;
			  else
				  return false;
			 break;
		default:
			 return false;
	 }

	 string[j] = b;
	 while (string[j] == ' ' || string[j] == '\t' || string[j] == '\n')
	      j++;
	 if (string[j])
	 {
		  if (strncmp(string+j,"order by",8) == 0)
		    {break;}
		 
		 if (strncmp("and",string+j,3)==0)
		    {
			  if (counter_or)
				  return false;
			 op = operation::land; j+=3; counter_and ++;continue;
		    }
		 
	     if (strncmp("or",string+j,2)==0)
		    {
			 if (counter_and)
				  return false;
			 op = operation::lor; j+=2; counter_or ++; continue;
	        }
		 
	  return false;
	 }
  }
	
 if (c_name != condition::none && c_phone == condition::none && c_group == condition::none)// condition and(or)
 {
	 if (op != operation::none)
		 return false;
 }
 if (c_name == condition::none && c_phone != condition::none && c_group == condition::none)
 {
	 if (op != operation::none)
		 return false;
 }
 if (c_name == condition::none && c_phone == condition::none && c_group != condition::none)
 {
	 if (op != operation::none)
		 return false;
 }
	
 if (c_name != condition::none && c_phone != condition::none && c_group == condition::none)// condition and(or) condition and(or)
 {
	 if (counter_and>1 || counter_or>1)
		 return false;
 }
 if (c_name == condition::none && c_phone != condition::none && c_group != condition::none)
 {
	 if (counter_and>1 || counter_or>1)
		 return false;
 }
 if (c_name != condition::none && c_phone == condition::none && c_group != condition::none)
 {
	if (counter_and>1 || counter_or>1)
		 return false;
 }
	
 if (counter_and>2 || counter_or>2)// condition and(or) condition and(or) condition and(or)
	 return false;
	
 (*i) += j;
 return true;
}
	


bool command::parseConditionSorting(char *string)
{
	char *buf;char b;
	int i = 0,j = 0,flag, count_name = 0, count_phone = 0, count_group = 0;
	while (string[i])
	{
	  flag = 0;
	  buf = cutOutWord(string,&i,&b);
	  
	  if (!buf[0])
	  {
		  if (count_name == 0 && count_phone == 0 && count_group == 0)
			  return false;
		  else {return true;}
	  }
	  if (buf[0])
	   {
	     if (strcmp(buf,"name") == 0)
		    {
			  if(count_name == 0)
			  {count_name++;order_by[j] = ordering::name;flag = 1;}
			  else return false;
		    }
	     if (strcmp(buf,"phone") == 0)
		    {
			  if (count_phone == 0)
			  {count_phone++;order_by[j] = ordering::phone;flag = 1;}
			  else return false;
		    } 
		 if (strcmp(buf,"group") == 0)
		    {
			  if (count_group == 0)
			  {count_group++;order_by[j] = ordering::group;flag = 1;}
			  else return false;
		    }
		} 
		 string[i] = b;
		 j++;	
	     if (!flag)
		  return false;
	} 
  return true;
}


bool command::parseSelect(char *string)	
{
	bool res;
	char buf;
	char *str = nullptr;
	int i = 0;
	if (!string)
		return false;
	str = strstr(string,"where");
	if (str)
	{
	   i = (int)(str-string);
	   buf = string[i-1];
	   string[i-1] = '\0';
	   res = parseConditionOutputFields(string);
	   if (!res)
	       return false;
	   string[i-1] = buf;
	   i+=5;
	   res = parseSearch(string+i,&i);
	   if (!res)
		  return false;
	   if (string[i])
	   {
	   str = strstr(string+i,"order by");
	   if (str)
	   {
	     res = parseConditionSorting(str+8);
	     if (!res)
		  return false;
	   }
	   }
	 }
	else
	{
	  
	  str = strstr(string,"order by");
		if (str)
	   {
		  i = (int)(str-string);
	      buf = string[i-1];
	      string[i-1] = '\0';
	      res = parseConditionOutputFields(string);
	      if (!res)
		     return false;
	      string[i-1] = buf;
	      res = parseConditionSorting(str+8);
	      if (!res)
		     return false;
	   }
	   else
	   {
		  
		 res = parseConditionOutputFields(string);
	      if (!res)
		     return false;
	   }
		   
	}

  return true;
}

	
	




field strncmp_field(char *s)
{
   if (strncmp("name",s,4)==0)
	   return field::name;
   if (strncmp("phone",s,5)==0)
	   return field::phone;
   if (strncmp("group",s,5)==0)
      return field::group;
   return field::none;
}
		

condition strcmp_condition(char* s,field f_field, int *i)
{
  condition res = condition::none;
  if (strncmp(s,"=",1)==0)
     {(*i)++;res =condition::eq;}
  if (strncmp(s,"<",1)==0)
     {(*i)++;res = condition::lt;}
  if (strncmp(s,">",1)==0)
     {(*i)++;res = condition::gt;}
  if (strncmp(s,"<>",2)==0)
     {(*i)++;res=condition::ne;}
  if (strncmp(s,"<=",2)==0)
     {(*i)++;res = condition::le;}
  if (strncmp(s,">=",2)==0)
     {(*i)++;res = condition::ge;}
  
  if (f_field == field::name)
  {
	  if (strncmp(s,"like",4)==0)
	     {(*i)+=4;res = condition::like;}
	  if (strncmp(s,"not",3)==0)
	  {   int j = 3;(*i) += 3;
		  while (s[j] == ' ')
		         {(*i)++;j++;}
	      
	      if (s[j])
		  {
			  if (strncmp(s+j,"like",4)==0)
			     {(*i) +=4;res = condition::nlike;}
		  }
	  }
  }			  
return res;
}


void command::print (FILE *fp)
{
  if (c_name != condition::none)
  {   
	  if (c_name == condition::like)
        {fprintf(fp,"command::name = %s, command::condition = like\n",(*this).get_name());}
	  if (c_name == condition::nlike)
        {fprintf(fp,"command::name = %s, command::condition = not like\n",(*this).get_name());}
	  if (c_name == condition::eq)
        {fprintf(fp,"command::name = %s, command::condition = equal\n",(*this).get_name());}
	  if (c_name == condition::ne)
        {fprintf(fp,"command::name = %s, command::condition = not equal\n",(*this).get_name());}
	  if (c_name == condition::lt)
        {fprintf(fp,"command::name = %s, command::condition = less than\n",(*this).get_name());}
	  if (c_name == condition::gt)
        {fprintf(fp,"command::name = %s, command::condition = great than\n",(*this).get_name());}
	  if (c_name == condition::le)
        {fprintf(fp,"command::name = %s, command::condition = less equal\n",(*this).get_name());}
	  if (c_name == condition::ge)
        {fprintf(fp,"command::name = %s, command::condition = great equal\n",(*this).get_name());}
  }
  if (c_phone != condition::none)
  {
	  if (c_phone == condition::eq)
	     {fprintf(fp,"command::phone = %d, command::condition = equal\n", (*this).get_phone());}
	  if (c_phone == condition::ne)
	     {fprintf(fp,"command::phone = %d, command::condition = not equal\n", (*this).get_phone());}
	  if (c_phone == condition::lt)
	     {fprintf(fp,"command::phone = %d, command::condition = less than\n", (*this).get_phone());}
	  if (c_phone == condition::gt)
	     {fprintf(fp,"command::phone = %d, command::condition = great than\n", (*this).get_phone());}  
	  if (c_phone == condition::le)
	     {fprintf(fp,"command::phone = %d, command::condition = less equal\n", (*this).get_phone());}
	  if (c_phone == condition::ge)
	     {fprintf(fp,"command::phone = %d, command::condition = great equal\n", (*this).get_phone());}
  }		
  if (c_group != condition::none)
  {   
	  if (c_group == condition::eq)
	     {fprintf(fp,"command::group = %d, command::condition = equal\n", (*this).get_group());}
	  if (c_group == condition::ne)
	     {fprintf(fp,"command::group = %d, command::condition = not equal\n", (*this).get_group());}
	  if (c_group == condition::lt)
	     {fprintf(fp,"command::group = %d, command::condition = less than\n", (*this).get_group());}
	  if (c_group == condition::gt)
	     {fprintf(fp,"command::group = %d, command::condition = great than\n", (*this).get_group());}  
	  if (c_group == condition::le)
	     {fprintf(fp,"command::group = %d, command::condition = less equal\n", (*this).get_group());}
	  if (c_group == condition::ge)
	     {fprintf(fp,"command::group = %d, command::condition = great equal\n", (*this).get_group());}
  }
}
	
	
int getNumberByString(char* buf)
{
  int len = strlen(buf);
  int i = 0, res = 0, d = 1;
  for (int j = 1; j < len; j++)
		   d *= 10;
  while (buf[i])
  {
	  if ( (int)buf[i] < 48 || (int)buf[i] > 57 )
		    return -1;
	  res += ((int)buf[i]-48)*d;
	  i++; d /= 10;
  }
  return res;
}
	
bool command::apply (record& x)
{
  bool res_name = true,res_phone = true,res_group = true, res = true;
	
  switch (op)
	{
	  case operation::none:
			break;
	  case operation::land:
		    res_name = (res_phone = (res_group = true));
		    break;
	  case operation::lor:
		    res_name = (res_phone = (res_group = false));  
    }	  
		  
	if (c_name != condition::none)
	{
		res = (res_name = x.compare_name(c_name,(*this)));
	}
	
	if (c_phone != condition::none)
	{
		res = (res_phone = x.compare_phone(c_phone,(*this)));
	}
	
	if (c_group != condition::none)
	{
		res = (res_group = x.compare_group(c_group,(*this)));
	}
	
	switch (op)
	{
		case operation::none:
			 return res;
		case operation::land:
			return res_name&res_phone&res_group;
		case operation::lor:
			return res_name|res_phone|res_group;
	}	
  return false;
}


/*int APLY (list_node<T>* head, FILE *fp)
{
	int res = 0;
	list_node<T> *curr = nullptr;
	if (head == nullptr)
		return 0;
	for (curr = head; curr; curr = curr->get_next())
	{
	  if (apply(curr))
	     {curr->print(fp);res++;}
	}
 return res;
}*/

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	