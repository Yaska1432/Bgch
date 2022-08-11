#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>
#include "list_node2.h"
#include "list_node.h"
#include "list2.h"

int list2::get_length() 
 {  int lenght = 0;
    list_node2 *curr;
	for (curr = head; curr; curr = curr->get_next())
	{
		lenght ++;
	}
  return lenght;
 }


list2::~list2()
{
	delete_list2();
}


void list2::delete_list2 ()
     {
      list_node2 *curr, *next_ = nullptr;
      for ( curr = head; curr; curr = next_ )
      {
       next_= curr->get_next();
       delete curr;
      }
	 head = nullptr;
     }


bool list2::init (list_node* a)
{
	list_node2 *buf = new list_node2;
	if (!buf)
		return false;
	buf->set_node(a);
	if (!head)
	   {head = buf;curr = buf;}
	else
	  {
		curr->set_next(buf);
		curr = buf;
	  }
	return true;
}


bool list2::CompareList_node2(list_node2& node1, list_node2& node2, ordering order[], int max)
{
  for(int j = 0; j<max; j++)
  {
	 
	  switch (order[j])
	  {  
		  case ordering::name:
			  if(node1.node->compare_name(condition::lt,*(node2.node)))
	             return true;
			  if(node1.node->compare_name(condition::gt,*(node2.node)))
	             return false;
			  break;
			  
		  case ordering::phone:
			  if(node1.node->compare_phone(condition::lt,*(node2.node)))
	             return true;
			  if(node1.node->compare_phone(condition::gt,*(node2.node)))
	             return false;
	          break;
			  
		  case ordering::group:
			  if(node1.node->compare_group(condition::lt,*(node2.node)))
	             return true;
			  if(node1.node->compare_group(condition::gt,*(node2.node)))
	             return false;
	  
		  default:;
	  }
  }
 return true;
}
		
  void list2::merger_sort (list_node2 *&A, list_node2 *& B, list_node2 *& C, list_node2 **curr_C,int n, int m, int max, ordering order_by[])
{  
   list_node2 *curr_A,*curr_B;
   int i,j;
   i = ( j = 0 );
   curr_A = A;
   curr_B = B;
   if (!*(curr_C))
   {
	  if(CompareList_node2(*curr_A,*curr_B,order_by,max))
	    {C = curr_A;curr_A=curr_A->get_next();i++;}
	  else
	    {C = curr_B;curr_B=curr_B->get_next();j++;}
     *curr_C = C;C->set_next(nullptr);
    }
while ((i<n)&&(j<m))
 {   
  if (CompareList_node2(*curr_A,*curr_B,order_by,max))//change
  {   
   (*curr_C)->set_next(curr_A);*curr_C = curr_A;curr_A=curr_A->get_next();
   i++;
  }
  else
  {   
   (*curr_C)->set_next(curr_B);*curr_C = curr_B;curr_B=curr_B->get_next();
    j++;
  }
 }
while (i<n)
 {   
  (*curr_C)->set_next(curr_A);*curr_C = curr_A;curr_A=curr_A->get_next();
  i++;
 }
while (j<m)
 {   
  (*curr_C)->set_next(curr_B);*curr_C = curr_B; curr_B=curr_B->get_next();
  j++;
 }
}

		
void list2::mergeSort(command &y)
{
  list_node2 *A = nullptr, *B = nullptr, *C = nullptr;
  list_node2 *curr_left_border, *curr_middle, *curr_A, *curr_B, *curr_C;
  int step,left_border,right_border,iter,middle,i,j,k,n;
  n = get_length();i = 0;j = 0;right_border = 0;curr_A = nullptr; curr_B = nullptr;
  for ( step =1; step < n; step *=2)
  {   curr_left_border = head;curr_middle = head; curr_C = nullptr;
      for (j = 0;j<step;j++)
	  {
		curr_middle = curr_middle->get_next();
	  }
	for (iter = 0; iter < (n-step) ; iter += 2*step)
	{ 
	  left_border = iter;
	  right_border = iter + 2*step;
	  right_border = (right_border < n) ? right_border : n;
	  middle = iter + step;
	  for (k = 0; k < middle-left_border && curr_left_border; k++)//Вырезаем список А
	      {
		    if (!k)
			{ A = curr_left_border;curr_A = curr_left_border;}
		    else 
			{ curr_A->set_next(curr_left_border);curr_A = curr_left_border;}
		   curr_left_border=curr_left_border->get_next();
		   curr_A->set_next(nullptr);
	      }
		for (j = 0;j<step && curr_left_border;j++)
	  {
		curr_left_border = curr_left_border->get_next();
	  }
	  for (k = 0; k < middle-left_border && curr_middle; k++)// Вырезаем список B
	      {
		    if (!k)
			{ B = curr_middle;curr_B = curr_middle;}
		    else 
			{ curr_B->set_next(curr_middle);curr_B = curr_middle;}
		   curr_middle=curr_middle->get_next();
		   curr_B->set_next(nullptr);
	      }	
	  for (j = 0;j<step && curr_middle;j++)
	  {
		curr_middle = curr_middle->get_next();
	  }
      merger_sort (A,B,C,&curr_C,middle-left_border,right_border-middle,3,y.order_by);
	}
  if (right_border < n && iter >= (n-step))
     for ( i = 0; right_border+i<n; i++)
  {curr_C->set_next(curr_left_border);curr_C=curr_left_border;curr_left_border=curr_left_border->get_next();}
   head = C;
  }
}   



void list2::print(ordering order[], FILE* fp)
{
    list_node2* curr;
    for(curr = head; curr; curr = curr->get_next())
        curr->node->print(order, fp);
}
