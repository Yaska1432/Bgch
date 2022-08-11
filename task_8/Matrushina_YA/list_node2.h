#ifndef LIST_NODE2_H
#define LIST_NODE2_H
#include "list_node.h"
class list_node2
{
 private:
	   list_node *node = nullptr;
       list_node2 *next = nullptr;
 public:
       friend class list2;
	   friend class list_node;
       list_node2* get_next()
	     {return next;}
	   list_node* get_node()
	     {return node;}
	   void set_next(list_node2 *x)
	     {
		   next = x;
		 }
	   void set_node(list_node *x)
	     {
		   node = x;
		 }
       list_node2() = default;
	   ~list_node2()
	   { node = nullptr;next = nullptr;}
};


#endif //LIST_NODE2_H

