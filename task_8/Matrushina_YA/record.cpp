# include <string.h>
# include <stdio.h>
#include <math.h>
# include "record.h"
# define LEN 1234

using namespace std;

read_status record::init (const char *n, int p, int g)
{
  phone = p;
  group = g;
  if (n)
  {
    name = std::make_unique<char []> (strlen (n) + 1);
    if (!name) return read_status::memory;
    strcpy (name.get(), n);
  }
  else
  name = nullptr;
  return read_status::success;
}

read_status record::init_name (const char *n)
{
  //phone = p;
  //group = g;
  if (n)
  {
    name = std::make_unique<char []> (strlen (n) + 1);
    if (!name) return read_status::memory;
    strcpy (name.get(), n);
  }
  else
  name = nullptr;
  return read_status::success;
}

read_status record::init_phone (int p)
{
  phone = p;
  return read_status::success;
}

read_status record::init_group (int g)
{
  group = g;
  return read_status::success;
}


read_status record::read (FILE *fp)
{
  char buf[LEN];
  read_status res;
  name = nullptr;
  if (fscanf (fp, "%s%d%d", buf, &phone, &group) != 3)
  {
   if (feof(fp)) 
	   return read_status::eof;
   return read_status::format;
  }
  if ((res=init (buf, phone, group)) != read_status::success)
     return read_status::memory;
  return read_status::success;
}
// Check condition ’x’ for field ’phone’ for ’this’ and ’y’
bool record::compare_phone (condition x,record& y)
{
  switch (x)
  {
   case condition::none: // not specified
      return true; // unspecified opeation is true
   case condition::eq:
// equal
     return phone == y.get_phone();
   case condition::ne:
// not equal
     return phone != y.get_phone();
   case condition::lt:
// less than
     return phone < y.get_phone();
   case condition::gt:
// less than
     return phone > y.get_phone();
   case condition::le:
     return phone <= y.get_phone();
   case condition::ge:
      return phone >= y.get_phone();
   case condition::like: // strings only: match pattern
      return false; // cannot be used for phone
   case condition::nlike: // strings only: match pattern
      return false;
  }
return false;
}		


bool record::compare_group (condition x,record& y)
{
  //y.print();
  switch (x)
  {
   case condition::none: // not specified
      return true; // unspecified opeation is true
   case condition::eq:
// equal
     return group == y.get_group();
   case condition::ne:
// not equal
     return group != y.get_group();
   case condition::lt:
// less than
     return group < y.get_group();
   case condition::gt:
// less than
     return group > y.get_group();
   case condition::le:
     return group <= y.get_group();
   case condition::ge:
      return group >= y.get_group();
   case condition::like: // strings only: match pattern
      return false; // cannot be used for phone
   case condition::nlike: // strings only: match pattern
      return false;
  }
return false;
}		

bool record::compare_name (condition x,record& y)
{
  int res = 0;
  switch (x)
  {
   case condition::none: // not specified
      return true; // unspecified opeation is true
   case condition::like:
		res = strcmp_name(name.get(),y.get_name());
		return res > 0;
   case condition::nlike:
		 res = strcmp_name(name.get(),y.get_name());
		return res == 0;
   case condition::eq:
// equal
	    res = strcmp(name.get(), y.get_name());
        return res == 0;
   case condition::ne:
// not equal
		res = strcmp(y.get_name(),name.get());
        return res != 0;
   case condition::lt:
// less than
		res = strcmp(name.get(),y.get_name());
        return res < 0;
   case condition::gt:
// less than
		res = strcmp(name.get(),y.get_name());
        return res > 0;
   case condition::le:
		res = strcmp(name.get(),y.get_name());
        return res <= 0;
   case condition::ge:
		res = strcmp(name.get(),y.get_name());
        return res >= 0;
  }
return false;
}		

/*void record::print (FILE *fp)
{
 if (get_name())
  fprintf(fp,"%s %d %d\n",name.get(),phone,group);	
 else
  fprintf(fp,"%d %d\n",phone,group);
}*/

 bool record::compare(record& y)
 {
	 if (strcmp(name.get(),y.get_name()) != 0)
		 return false;
		
	 if (group != y.get_group())
		 return false;
	 
	 if (phone != y.get_phone())
		 return false;
		  
	return true;	 
  }

 int record::com(record& y)
 {
	 return strcmp(name.get(),y.get_name());
 }

int record::_compare(record& y)
       {
	     int res = 0;
		 
		 res = (*this).get_phone()-y.get_phone();
	     /*if (res != 0)
		   return res;
		   
		 res = strcmp((*this).get_name(),y->get_name());
	     if (res != 0)
		   return res;
		   
	 	res = (*this).get_group() - y->get_group();*/
		  
	    return res;
        }


/*int record::compare_(record &y)
{
  int res = 0;
  ordering order[3] = {ordering::phone, ordering::name, ordering::group};
  if (y.get_name() == nullptr)
	  order[1] = ordering::none;
  for(int j = 0; j<3; j++)
  {
	  switch (order[j])
	  {  
		  case ordering::name:
			  res = strcmp(name.get(), y.get_name());
			  if(res != 0)
	             return res;
			  break;
			  
		  case ordering::phone:
			  res = phone - y.get_phone();
			  if(res != 0)
	             return res;
	          break;
			  
		  case ordering::group:
			  res = group - y.get_group();
			  if(res != 0)
	             return res;
			  break;
		  default:;
	  }
  }
 return res;
}*/


void record::print (const ordering order[], FILE *fp)
{
  const int max_items = 3;
  const ordering default_ordering[max_items] = {ordering::name, ordering::phone, ordering::group};
  const ordering * p = (order && order[0] != ordering::none ? order : default_ordering);
  for (int i = 0; i < max_items; i++)
  {
      switch (p[i])
      {
        case ordering::name:
          fprintf (fp," %s", name.get()); break;
        case ordering::phone:
          fprintf (fp," %d", phone); break;
        case ordering::group:
          fprintf (fp," %d", group); break;
        case ordering::none:
          continue;
	  }
  }
 fprintf (fp, "\n");
}

void record::Print ()
{
  const int max_items = 3;
  const ordering default_ordering[max_items] = {ordering::name, ordering::phone, ordering::group};
  for (int i = 0; i < max_items; i++)
  {
      switch (default_ordering[i])
      {
        case ordering::name:
          printf (" %s", name.get()); break;
        case ordering::phone:
          printf (" %d", phone); break;
        case ordering::group:
          printf (" %d", group); break;
        case ordering::none:
          continue;
	  }
  }
 printf (" ");
}


int strcmp_name(char* str_1, char* str_2)
{
   int i=0 ,j = 0, res;
	while (str_1[j] && str_2[i])
	{
	  if (str_1[j] == '\\')
	  {
		if (str_2[i] == '\\' && str_2[i+1] =='\\')
			{i += 2; j++;continue;}
	  }
		
	  if (str_1[j] == '[')
	  {
		if (str_2[i] == '\\' && str_2[i+1] =='[')
			{i += 2; j++;continue;}
	  }
		
	  if (str_1[j] == ']')
	  {
		if (str_2[i] == '\\' && str_2[i+1] ==']')
			{i += 2; j++;continue;}
	  }
		
	  if (str_1[j] == '_')
	  {
		if (str_2[i] == '\\' && str_2[i+1] =='_')
			{i += 2; j++;continue;}
	  }
		
	  if (str_1[j] == '^')
	  {
		if (str_2[i] == '\\' && str_2[i+1] =='^')
			{i += 2; j++;continue;}
	  }
		
	  if (str_1[j] == '%')
	  {
		if (str_2[i] == '\\' && str_2[i+1] =='%')
			{i += 2; j++;continue;}
	  }
		
	  if (str_1[j] == str_2[i] && str_2[i] != '%'&& str_2[i] != '\\')
	      {i++;j++;continue;}
		
	  switch ((int)str_2[i])
	  {
		  case 95:
			  {i++;j++;}
			  break;
		  case 37:
			  {
				if (str_2[i+1] == '\0')
			        return 1; 
		        while(str_1[j])
		        {
			     res = strcmp_name(str_1+j,str_2+i+1);
			     if(res)
				    return 1;
			     j++;
		        }
			  }
			  break;
		  case 91:
			 {
				res = strcmp_spec_sym(str_2+i,str_1+j,&i,&j);
				if (!res)
					return 0;
			 }
			 break;
		  default:
			  return 0;
	 }
    }
	
	 while(str_2[i] == '%')
		{
		   i++;
		}
	
	if ((!str_2[i] && str_1[j]) || (str_2[i] && !str_1[j]))
		return 0;
			  
  return 1;
}



int strcmp_spec_sym (char* str_2,char* str_1, int* i, int* j)
{
	if (str_2[0] == '[' && str_2[1] != '\0' && str_2[1] != '^' && str_2[2] == '-' && str_2[3] != '\0' && str_2[4] == ']')
		  {
			  if (((int)str_1[0] >= (int)str_2[1] && (int)str_1[0] <= (int)str_2[3])) 
			     {(*j)++; (*i) +=5;return 1;}
			  else return 0;
		  }
	if (str_2[0] == '[' && str_2[1] == '^' && str_2[2] != '\0' && str_2[3] == '-' && str_2[4] != '\0' && str_2[5] == ']')
		  {
			  if ((int)str_1[0] < (int)str_2[2] || (int)str_1[0] > (int)str_2[4]) 
			     {(*j)++; (*i) +=6;return 1;}
			  else return 0;
		  }
return 0;
}



int record::hash_value(int k)
		{
			int res = 0;
			int number = (*this).get_phone();
			int buf = number;
			int d = 0;
			buf = (int)buf/10;
			if (buf >= 1)
			    d++;
			while ( buf >= 1)
			{
			   d++;
			   buf = (int)buf/10;
			}
			if ( d <= k)
			    res = number;
		 	else
				res = (int)number/(int)pow(10,d-k);
			return res;
		}















		