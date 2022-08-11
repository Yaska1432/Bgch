#ifndef LIST_NODE_H
#define LIST_NODE_H
#include <string.h>
//#include <math.h>
#include "record.h"

class list_node: public record
{
 private:
       list_node *next = nullptr;
	   list_node *prev = nullptr;
 public:
       friend class list;
       list_node* get_next()
	     {return next;}
	   void set_next(list_node *x)
	     {
		   next = x;
		 }
	   list_node* get_prev()
	     {return prev;}
	   void set_prev(list_node *x)
	     {
		   prev = x;
		 }
       list_node() = default;
	   ~list_node()
	   { next = nullptr;prev =nullptr;}
	   
	    int COMPARE(list_node *y)
       {
	     int res;
	     if ((*this).get_name() == nullptr && y->get_name() == nullptr)
		    return 0;
	     if ((*this).get_name() != nullptr && y->get_name() == nullptr)
		   return 1;
	     if ((*this).get_name() == nullptr && y->get_name() != nullptr)
		   return -1;
	    res = strcmp((*this).get_name(),y->get_name());	
		return res;
        }
		
		
		int key_compare(list_node *y)
       {
	     return (*this).get_phone()-y->get_phone();
       }
		
		
		bool Compare(list_node *y)
       {
	     if (strcmp((*this).get_name(),y->get_name()) != 0)
		   return false;
		
	     if ((*this).get_group() != y->get_group())
		   return false;
	 
	    if ((*this).get_phone() != y->get_phone())
		   return false;
		  
	     return true;
        }

		int full_compare(list_node *y)
       {
	     int res = 0;
		 res = (*this).get_phone()-y->get_phone();
	     if (res != 0)
		   return res;
		   
		 res = strcmp((*this).get_name(),y->get_name());
	     if (res != 0)
		   return res;
		   
	 	res = (*this).get_group() - y->get_group();
		  
	    return res;
        }

		/*int hash_value(int k)
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
		}*/
		
	   /*list_node &operator= (const list_node &x)
	   { *(record*)(this) = x; next = nullptr; prev = nullptr;return *this;}*/
	   
	   /*list_node &operator= (list_node &&x)
	   { *(record*)(this) = (record&&)x; next = x.next;prev = x.prev; x.prev = nullptr;x.next = nullptr; return *this;}*/
	   
};



#endif //LIST_NODE_H