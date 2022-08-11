#ifndef LIST_H
#define LIST_H
#define LEN 256
#define max_print 20
#include "record.h"
# include "command.h"
# include "ordering.h"
# include "list2.h"
# include "list_node2.h"

class list
{
  private:
      list_node *head = nullptr;
	  list_node *tail = nullptr;
  public:
  
      list()=default;
	  
	  list_node* get_head()
	     {return head;}
		 
	  list_node* get_tail()
	     {return tail;}
		 
	  
	
	  ~list()
	  { delete_list();}
	 
	  void delete_list ()
     {
	  if (head == nullptr)
	      return;
      list_node *curr, *next_ = nullptr;
      for ( curr = head; curr; curr = next_ )
      {
       next_= curr->get_next();
       delete curr;
      }
	 head = nullptr;
	 tail = nullptr;
     }
		 
	  read_status read (const char *filename)
	 {
       FILE *fp;list_node *tail,*curr;
       read_status res;
       if (!(fp = fopen (filename,"r")))
	      return read_status::open;
       head = new list_node;
       if (!head)
         {
	     fclose(fp);
         return read_status::memory;
         }
       if (head->read(fp) != read_status::success)
         {
         fclose(fp);
         return read_status::read;
         }	   
         tail = head;	
         curr = new list_node;
         if (!curr)
         {
	      fclose(fp);
          return read_status::memory;
         }
       while ((res = curr->read(fp)) == read_status::success)
        {
         tail->set_next(curr);
         curr->set_prev(tail);
         tail = curr;
         curr = new list_node;
         if (!curr)
         {
	      fclose(fp);
          return read_status::memory;
         }
        }	  
        delete curr;
	
       if (!feof(fp))
      {
       fclose (fp);
       return read_status::read;
       }	  

      fclose (fp);
      return read_status::success;
    } 

	  void print (command &y,FILE *fp = stdout)
	  { 
        
        list_node *curr;
        for (curr = head; curr; curr = curr->get_next())
        {
	     curr->print(y.order,fp); 
        }
      }
	  
	  
	  int get_length()
        {  int lenght = 0;
           list_node *curr;
	       for (curr = head; curr; curr = curr->get_next())
	       {
		    lenght ++;
	       }
          return lenght;
        }
		
		int APLY (command &y,FILE *fp = stdout)
     {
	    
	   
		switch (y.get_type())
		{
		    case command_type::quit:
			     return -1;
			
			case command_type::insert:
			     return ListInsert(y,fp);
				 
			case command_type::select:
			     return ListSelect(y,fp);
				 
			case command_type::del:
			     return ListDelete(y,fp);
				
			default:;
		
		}
	   return 0;
     }
	 
	    bool init (list_node* a)
     {
	  
	    if (!head)
	     {head = a;tail = a;}
	    else
	    {
		tail->set_next(a);
		a->set_prev(tail);
		tail = a;
	   }
	 return true;
    } 
	
	
	 void delete_list_node(list_node *x)
   {
	 list_node *buf_prev,*buf_next;
	 if (x == head && x == tail)
	 {
		 delete x;
		 x = nullptr;
		 head = (tail = nullptr);
		 return;
	 }
	 if (x == head)
	 {
	   buf_next = x->get_next();
	   buf_next->set_prev(nullptr);
	   delete head;
	   head = buf_next;
	   return;
	 }
	 if (x == tail)
	 {
	    buf_prev = x->get_prev();
		buf_prev->set_next(nullptr);
		delete x;
		tail = buf_prev;
		return;
	 }
	 buf_prev = x->get_prev();
	 buf_next = x->get_next();
	 buf_prev->set_next(buf_next);
	 buf_next->set_prev(buf_prev);
	 delete x;
   }
	 
	    int ListInsert(command &y, FILE *fp)
	 {
	    (void)fp;
	    list_node* prev_ = head;
	    for (list_node* curr = head; curr; prev_= curr,curr = curr->get_next())
		    if (curr->compare(y))
			    return 0;
		list_node* tmp = new list_node;
		if (!tmp)
		    return -1;
		tmp->init(y.get_name(),y.get_phone(),y.get_group());
		if (head == nullptr)
		    head = tmp;
		else
		{
	    prev_->set_next(tmp);
		tmp->set_prev(prev_);
		}
		//print(y,fp);
		return 0;
	 }
	 
	 
	   int ListSelect(command &y, FILE *fp )
	 {
	  int res = 0;
	  if (head == nullptr)
		     return 0;
	  switch (y.order_by[0])
	  {
	    case ordering::none:
		  {
		   
		   for (list_node* curr = head; curr; curr = curr->get_next())
	           if (y.apply(*curr))
	              {curr->print(y.order,fp);res++;}
		   }
		   break;
		default:
		  {  
	         list2 LIST;
	        
	         for (list_node* curr = head; curr; curr = curr->get_next())
	         {
	           if (y.apply(*curr))    
		            {res++;LIST.init(curr);}
				
	         }
			 
			 if (res)
			 {
	           LIST.mergeSort(y);
			   LIST.print(y.order,fp);
			 }
		  }
		  break;
	  }
	  return res;
	}
	
	int SearchAndOutputRecord(command &y,FILE *fp)
	{
	   int res = 0;
	   for (list_node* curr = head; curr; curr = curr->get_next())
	           if (y.apply(*curr))
	              {curr->print(y.order,fp);res++;}
	   return res;
	}
	
	int SearchSortAndOutputRecord(list2 *LIST2, command &y)
	{
	   int res = 0;
	   for (list_node* curr = head; curr; curr = curr->get_next())
	           if (y.apply(*curr))
	              {LIST2->init(curr);res++;}
	   return res;
	}
	
	
	int ListDelete(command &y, FILE *fp)
  {
    (void) fp;
	if (head == nullptr)
		   return 0;
	if ( y.get_c_name() == condition::none && y.get_c_phone() == condition::none && y.get_c_group() == condition::none )
	     {delete_list();return 0;}
	list_node *buf = head;
	for (list_node* curr = head; curr; curr = buf )
	     {
		       buf = curr->get_next();
	           if (y.apply(*curr))
	              {  
				     if (curr == head)
					 {  head = curr->get_next();
					    delete_head(curr);
					 }
					 else
					    delete_node(curr);
					    
				  }
			
		 }
	//if (head)
	   //print(y,fp);
	return 0;
  }
  
  void delete_head(list_node *head)
  {
    list_node* buf;
     {
      buf = head;
      head = buf->get_next();
	  if (buf->get_next())
	       buf->get_next()->set_prev(nullptr);
      delete buf;
     }
   }
   
   void delete_node(list_node *x)
{
  list_node* buf,* nextt;
  if (!(x->get_next()))
     {
      buf = x->get_prev();
	  tail = buf;
      buf->set_next(x->get_next());
      delete x;
     }
  else 
     {
	  buf = x->get_prev();
	  nextt = x->get_next();
      buf->set_next(nextt);
      nextt->set_prev(buf);
      delete x;
     }
}
		
};

#endif //LIST_H