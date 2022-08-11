#ifndef B_TREE_LIST_H
#define B_TREE_LIST_H
#include "command.h"
# include "list2.h"
# include "list_node2.h"
enum class status
{
	none,
	filled,
	del,
};
class b_tree_list_node
{
 private:
   list_node *node = nullptr;
   b_tree_list_node *next = nullptr;
   b_tree_list_node *prev = nullptr;

 public:
   b_tree_list_node()=default;
   friend class b_tree_list;
   ~b_tree_list_node()
   {next = nullptr; prev = nullptr; node = nullptr;}
    b_tree_list_node* get_next()
   {return next;}
    b_tree_list_node* get_prev()
   {return prev;}
   list_node* get_node()
   {return node;}
   void set_next(b_tree_list_node *x)
   {next = x;}
   void set_prev(b_tree_list_node *x)
   {prev = x;}
   void set_node(list_node *x)
   {node = x;}
};
class b_tree_list
{
 private:
   b_tree_list_node *head = nullptr;
   b_tree_list_node *tail = nullptr;
   status st = status::none;
 public:
   status get_st()
   {return st;}
   void set_st(status x)
   {st = x;}
   b_tree_list()=default;
   ~b_tree_list()
   { delete_b_tree_list();}
   b_tree_list_node* get_head()
   {return head;}
   void set_head(b_tree_list_node *x)
   {head = x;}
   b_tree_list_node* get_tail()
   {return tail;}
   void set_tail(b_tree_list_node *x)
   {tail = x;}
   
   b_tree_list& operator= (b_tree_list &x)
   { 
     b_tree_list_node* current = x.get_head();
	 if (current != nullptr)
	 {
	   b_tree_list_node *new_node = new b_tree_list_node;
	   new_node = current;
	   head = (tail = new_node);
	 }
     while (current->next)
    {
     current = current->get_next();
     b_tree_list_node* newlink = new b_tree_list_node;
	 newlink = current;
     tail->set_next(newlink);
     newlink->set_prev(tail);
     tail = newlink;
    }
	return *this;
   }
	
   b_tree_list& operator= (b_tree_list &&x)
   {
	 (*this).delete_b_tree_list();
	 b_tree_list_node* curr = x.get_head();
	 b_tree_list_node* buf = x.get_tail();
	 head = curr;
	 tail = buf;
	 st = x.get_st();
	 x.set_head(nullptr);
	 x.set_tail(nullptr);
	 x.set_st(status::none);
	return *this;
   }   
	
   void delete_b_tree_list()
     {
      b_tree_list_node *curr, *next_ = nullptr;
	  if (head == nullptr)
		  return;
      for ( curr = head; curr; curr = next_ )
      {
       next_= curr->get_next();
       delete curr;
      }
	 head = nullptr;
	 tail = nullptr;
	 st = status::none;
     }
	
 void delete_b_tree_list_node(b_tree_list_node *x)
   {
	 b_tree_list_node *buf_prev,*buf_next;
	 if (x == head && x == tail)
	 {
		 delete x;
		 head = (tail = nullptr);
		 st = status::del;
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
	
void delete_list_node(list_node *y)
{
  b_tree_list_node *buf_prev,*buf_next, *x;
 for (x = head; x; x = x->get_next())
 {
   if (x->get_node()->Compare(y))
  {       
    if (x == head && x == tail)
	 {
		 delete x;
		 x = nullptr;
		 head = (tail = nullptr);
		 st = status::del;
		 return;
	 }
	 if (x == head)
	 {
	   buf_next = x->get_next();
	   buf_next->set_prev(nullptr);
	   delete head;
	   head = buf_next;
	   st = status::filled;
	   return;
	 }
	 if (x == tail)
	 {
	    buf_prev = x->get_prev();
		buf_prev->set_next(nullptr);
		delete x;
		tail = buf_prev;
		st = status::filled;
		return;
	 }
	 buf_prev = x->get_prev();
	 buf_next = x->get_next();
	 buf_prev->set_next(buf_next);
	 buf_next->set_prev(buf_prev);
	 st = status::filled;
	 delete x;
	 return;
  }
 }
}

   bool search (command &y)
   {
     b_tree_list_node *x;
     for (x = head; x; x = x->get_next())
    {
	  if (x->get_node()->compare(y))
          {return false;}
	}
    return true;
   }
   
  int SearchAndOutputRecord(command &y,FILE *fp)
 {
    b_tree_list_node *x;
	int res = 0;
     for (x = head; x; x = x->get_next())
    {
	  if (y.apply(*(x->get_node())))
          {x->get_node()->print(y.order,fp);res++;}
	}
    return res;
 }
 
 int SearchSortAndOutputRecord(list2 *LIST2,command &y)
 {
    b_tree_list_node *x;
	int res = 0;
     for (x = head; x; x = x->get_next())
    {
	  if (y.apply(*x->get_node()))
          {LIST2->init(x->get_node());res++;}
	}
    return res;
 }
   
   bool init_list_node(list_node *x)
  {
	b_tree_list_node *buf = new b_tree_list_node;
	if (!buf)
		return false;
	buf->set_node(x);
	if (!head)
	   {head = buf;tail = buf; st = status::filled;}
	else
	  {
	    st = status::filled;
		tail->set_next(buf);
		buf->set_prev(tail);
		tail = buf;
	  }
	return true;   
   }
   
  
   
   bool init(b_tree_list &x)
   {
	
	if (!head)
	   {head = x.get_head();tail = x.get_tail();st = status::filled;}
	else
	  {
	    st = status::filled;
		tail->set_next(x.get_head());
		x.get_head()->set_prev(tail);
		tail = x.get_head();
	  }
	x.set_head(nullptr);
	x.set_tail(nullptr);
	return true;   
   }
	
   void print(int spaces)
   {
	 b_tree_list_node *curr;
	 for (int i = 0; i<spaces; i++)
		 printf(" ");
     for (curr = head; curr; curr = curr->get_next())
    {
	  curr->get_node()->Print(); 
    }
   printf(";"); 
   }  
   
   int print_(command &y,FILE *fp)
   {
	 b_tree_list_node *curr;
	 int res = 0;
     for (curr = head; curr; curr = curr->get_next())
    {
	  curr->get_node()->print(y.order,fp); 
	  res ++;
    }
	return res;
   }  
   
   int sortprint_(list2 *LIST2)
   {
	 b_tree_list_node *curr;
	 int res = 0;
     for (curr = head; curr; curr = curr->get_next())
    {
	  LIST2->init(curr->get_node());res++;
    }
	return res;
   }  
    
};
#endif //B_TREE_LIST_H