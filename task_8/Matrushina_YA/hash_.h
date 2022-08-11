#ifndef B_TREE_H
#define B_TREE_H
# include "hash_list_.h"
# include "ordering.h"
# include "list2.h"
# include "list_node2.h"
# include "condition.h"

template <class T> class b_tree;
template <class T>
class b_tree_node: public T
{
 private:
       T *values = nullptr;//2*m elements array
	   int size = 0;//number of children
	   b_tree_node **children = nullptr;//2*m+1 elements array
 public:
       enum ERRORS
	  {
	  SUCCESS = 0,
	  ERROR_READ = -1,
	  ERROR_OPEN = -2,
	  MEMORY_ERROR = -3,
	  ERROR_ALOCATED = -4,
	  FILE_END = -5,
	   };
       int get_size()
	   {return size;}
	   void set_size(int m)
	   {size = m;}
       friend class b_tree<T>;
       b_tree_node() = default;
	   int init (int m)
	   { 
	     size = 0;
	     if (!(values = new T[2*m]))
		     return MEMORY_ERROR;
		 if (!(children = new b_tree_node*[2*m+1]))
		     {delete[]values;return MEMORY_ERROR;}
		 for (int i = 0; i<2*m+1; i++)
		     {children[i] = nullptr;}
		return SUCCESS;
	   }
	   void removal()
	   {
	    if (values!=nullptr)
	       {delete[]values; values = nullptr;}
		 if (children!=nullptr)
		   {delete[]children; children = nullptr;}
	   }
	   ~b_tree_node()
	   { 
	     removal();
	   }
	 
	   b_tree_node &operator= (b_tree_node &&x)
	   { if (this == &x)
	         return *this;
	     size = x.size;x.size = 0;
		 removal();
         values = x.values;
		 x.values = nullptr;
         children = x.children;
		 x.children = nullptr;
		 return *this;
	   }
};

template <class T>
class b_tree
{
  private:
      b_tree_node<T> *root = nullptr;
	  int m; // B-tree base
	  
	  
	  int InitToSubtree (T &y,b_tree_node<T> *&first, b_tree_node<T> *&second)
	  {
	    int index; b_tree_node<T> *pos = nullptr;int res = 0, flag = 0;
		index = binary_search (first->values,y,first->size, &flag);
		if (flag == 1)
		  {
		   first->values[index].init(y);
		   return SUCCESS;
		  }
		pos = first->children[index];
		if (pos)
		{
		  res = InitToSubtree(y,pos,second);
		  if (res == SUCCESS) 
		      return SUCCESS;
		  if (res == MEMORY_ERROR)
		      return MEMORY_ERROR;
		}
		else 
		{
		second = nullptr;
		}
		if (first->size < 2*m)
        {
		  Insert(y,first,first->size,index,second);
		  ++(first->size);
		  return SUCCESS;
		 }
		else
		{
		   res = Separation(first,second,index,y);
		   if (res == MEMORY_ERROR)
		       return MEMORY_ERROR;
           return 1;
		}
      }
	 
	 
	   
	
	 
  public:
      enum ERRORS
     {
	  SUCCESS = 0,
	  ERROR_READ = -1,
	  ERROR_OPEN = -2,
	  MEMORY_ERROR = -3,
	  ERROR_ALOCATED = -4,
	  FILE_END = -5,
	   };
	    b_tree()=default;


	    b_tree_node<T> *get_root()
	     {return root;}
		 
	    void set_m(int k)
	    { m = k;}
	  
        void set_root(b_tree_node<T>* pos)
	   {root = pos;}
	  
	  int init(b_tree_node<T> *pos, T &y)
	 { 
	   b_tree_node<T>* newroot;int res;
       if (pos == nullptr)
	   {
	     if (!(newroot = new b_tree_node<T>))
		       return MEMORY_ERROR;
		 if (!(newroot->init(m) == SUCCESS))
		       {delete newroot;return MEMORY_ERROR;}
		 newroot->values[0].init(y);
		 newroot->size = 1;
		 root = newroot;
		 return SUCCESS;
	   }
	   b_tree_node<T> *first = pos, *second;
	   res = InitToSubtree (y,first,second);
	   root = first;
	   if (res==SUCCESS)
	       return SUCCESS;
	   if (res== MEMORY_ERROR)
	       return MEMORY_ERROR;
	    
	   if (!(newroot = new b_tree_node<T>))
	           return MEMORY_ERROR;
	   if (!(newroot->init(m) == SUCCESS))
		       {delete newroot;return MEMORY_ERROR;}
		 newroot->values[0].init(y);
		 newroot->children[0] = first;
		 newroot->children[1] = second;
		 newroot->size = 1;
		 root = newroot;
		 return SUCCESS;
	 }
	
	
	  
	  bool FindNode(command &y,b_tree_node<T> *curr)
	  {
	    int index; b_tree_node<T> *pos = nullptr;int flag = 0;
		if (curr == nullptr)
		    return true;
		index = poisk (curr->values,y,curr->size, &flag);
		if (flag)
		  {return curr->values[index].search(y);}
		pos = curr->children[index];
		if (pos)
		   return FindNode (y,pos);
		else return true;
      }

	 
  int SearchAndOutputRecord(command &y,b_tree_node<T> *curr,FILE *fp)
{
  int flag = 0, ans = 0, size, res = 0, index = 0;
  if (curr == nullptr)
	   return 0;
  size = curr->get_size();
  switch (y.get_c_name())
 {
 
      case condition::eq:
    {
     index = poisk (curr->values,y,curr->size, &flag);
	 if (flag)
	    ans = curr->values[index].SearchAndOutputRecord(y,fp);
	 else
        ans = SearchAndOutputRecord(y,curr->children[index],fp);
     return ans;
    }
    break;
      case condition::lt:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  for (int i = 0; i < index; i++)
	  {
	     ans += curr->values[i].SearchAndOutputRecord(y,fp);
		 res += SearchAndOutputRecord(y,curr->children[i],fp);
	  }
	  res += SearchAndOutputRecord(y,curr->children[index],fp);
	  return ans+res;
    }
	break;
	 case condition::gt:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  if (!flag)
	   {
	     if (index < size)
	         {ans += curr->values[index].SearchAndOutputRecord(y,fp);}
			 
		 res += SearchAndOutputRecord(y,curr->children[index],fp);
	   }
	  for (int i = index+1; i < size; i++)
	  {
	     ans += curr->values[i].SearchAndOutputRecord(y,fp);
		 res += SearchAndOutputRecord(y,curr->children[i],fp);
	  }
	  if (index < size)
	     res += SearchAndOutputRecord(y,curr->children[size],fp);
	  return ans+res;
    }
	break;
	case condition::le:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  if (flag)
		    ans += curr->values[index].SearchAndOutputRecord(y,fp);
	  for (int i = 0; i < index; i++)
	  {
	     ans += curr->values[i].SearchAndOutputRecord(y,fp);
		 res += SearchAndOutputRecord(y,curr->children[i],fp);
	  }
	  res += SearchAndOutputRecord(y,curr->children[index],fp);
	  return ans+res;
    }
	break;
	 case condition::ge:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  if (!flag)
	      res += SearchAndOutputRecord(y,curr->children[index],fp);
	  for (int i = index; i < size; i++)
	  {
	     ans += curr->values[i].SearchAndOutputRecord(y,fp);
		 res += SearchAndOutputRecord(y,curr->children[i+1],fp);
	  }
	  return ans+res;
    }
	break;
      default:
	{
	   for (int i = 0; i < size; i++)
	    {
	      ans += curr->values[i].SearchAndOutputRecord(y,fp); 
		  res += SearchAndOutputRecord(y,curr->children[i],fp);
		}
		res += SearchAndOutputRecord(y,curr->children[size],fp);
		return ans+res;
	}
   } 
}
	  
	  int SearchSortAndOutputRecord(list2 *LIST2,command &y,b_tree_node<T> *curr)
{
  int flag = 0, ans = 0, size, res = 0, index = 0;
  if (curr == nullptr)
	   return 0;
  size = curr->get_size();
  switch (y.get_c_name())
 {
 
      case condition::eq:
    {
     index = poisk (curr->values,y,curr->size, &flag);
	 if (flag)
	    ans = curr->values[index].SearchSortAndOutputRecord(LIST2,y);
	 else
        ans = SearchSortAndOutputRecord(LIST2,y,curr->children[index]);
     return ans;
    }
    break;
      case condition::lt:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  for (int i = 0; i < index; i++)
	  {
	     ans += curr->values[i].SearchSortAndOutputRecord(LIST2,y);
		 res += SearchSortAndOutputRecord(LIST2,y,curr->children[i]);
	  }
	  res += SearchSortAndOutputRecord(LIST2,y,curr->children[index]);
	  return ans+res;
    }
	break;
	 case condition::gt:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  if (!flag)
	   {
	     if (index < size)
	         {ans += curr->values[index].SearchSortAndOutputRecord(LIST2,y);}
			 
		 res += SearchSortAndOutputRecord(LIST2,y,curr->children[index]);
	   }
	  for (int i = index+1; i < size; i++)
	  {
	     ans += curr->values[i].SearchSortAndOutputRecord(LIST2,y);
		 res += SearchSortAndOutputRecord(LIST2,y,curr->children[i]);
	  }
	  if (index < size)
	     res += SearchSortAndOutputRecord(LIST2,y,curr->children[size]);
	  return ans+res;
    }
	break;
	case condition::le:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  if (flag)
	      ans += curr->values[index].SearchSortAndOutputRecord(LIST2,y);
	  for (int i = 0; i < index; i++)
	  {
	     ans += curr->values[i].SearchSortAndOutputRecord(LIST2,y);
		 res += SearchSortAndOutputRecord(LIST2,y,curr->children[i]);
	  }
	  res += SearchSortAndOutputRecord(LIST2,y,curr->children[index]);
	  return ans+res;
    }
	break;
	 case condition::ge:
	{
      index = poisk (curr->values,y,curr->size, &flag);
	  if (!flag)
	      res += SearchSortAndOutputRecord(LIST2,y,curr->children[index]);
	  for (int i = index; i < size; i++)
	  {
	     ans += curr->values[i].SearchSortAndOutputRecord(LIST2,y);
		 res += SearchSortAndOutputRecord(LIST2,y,curr->children[i+1]);
	  }
	  return ans+res;
    }
	break;
      default:
	{
	   for (int i = 0; i < size; i++)
	    {
	      ans += curr->values[i].SearchSortAndOutputRecord(LIST2,y); 
		  res += SearchSortAndOutputRecord(LIST2,y,curr->children[i]);
		}
		res += SearchSortAndOutputRecord(LIST2,y,curr->children[size]);
		ans += res;
		return ans;
	}
   } 
}
	  
	  
	 int poisk (T *node, command &x, int size, int *flag = nullptr)
   {
    (void) flag;
    int mid, r_bor, l_bor,res;
    r_bor = size; l_bor = 0;
    while (l_bor != r_bor)
    { 
	  mid=(int)((r_bor+l_bor)/2);
	  res = node[mid].get_head()->get_node()->com(x);
      if (res < 0)
          l_bor = ++mid;
	  else
	     {
		  if (res == 0)
		     *flag = 1;
          r_bor = mid;
		  }
		  
    }
    return r_bor;
   } 
	 
	 int DeleteNode_2 (list_node *y,b_tree_node<T> *&parent, b_tree_node<T> *&curr,int index_parent, T*& x)
	 {
	   b_tree_node<T> *left_neigh = nullptr, *right_neigh = nullptr, *left_child = nullptr, *right_child = nullptr, *pos = nullptr, *b = nullptr;
	   T *buf = nullptr;
	   int flag = 0,res = 0, k = 0;
	   if (curr == nullptr)
		     return -1;
	   int index = search (curr->values,y,curr->size, &flag);
	   if (!flag)
	   {
	      pos = curr->children[index];
		  if (pos)
		  { res = DeleteNode_2 (y,curr,pos,index,x);}
		  else return -1;
	   }
	   else
	   {
	    if (curr->children[index] == nullptr && curr->children[index+1] == nullptr) // deleting from a sheet
	   {  
		   if (x == nullptr)
		       delete_node(curr,curr->size,index,y);
		   else  delete_node_3(curr,curr->size,index,x);
		    
		   if (curr->size >= m)
	             {return 1;}
			if (index_parent > 0)
		   {
		     if (parent != nullptr)
			 {
		      left_neigh = parent->children[index_parent-1];
		     if (left_neigh && left_neigh->size > m) //the left neighbor with more than m keys
	             {
				    MoveTheKeyFromLeftToRight (left_neigh,curr,parent,index_parent-1);
					return 1;
				 }
			 }
	       }
		  
		   if (index_parent < 2*m)
		  {
		    if (parent != nullptr)
			{
		     right_neigh = parent->children[index_parent+1];
		     if (right_neigh && right_neigh->size > m) //the left neighbor with more than m keys
	             {
				    MoveTheKeyFromRightToLeft (right_neigh,curr,parent,index_parent);
				    return 1;
				 }
			}
	      }
		 
		  if (parent!=nullptr && left_neigh)
		     {
			  MargeNodes (parent,left_neigh,curr,index_parent-1); 
			  delete_node_4(parent,parent->size,index_parent-1);
			  return 0;
			 }
			 
		  if (parent!=nullptr && right_neigh)
		     { 
			   MargeNodes (parent,curr,right_neigh,index_parent);
			   delete_node_4(parent,parent->size,index_parent);
			   return 0;
			   }
		  if (parent!=nullptr)
		    {
			   MargeNodes (parent,curr,right_neigh,index_parent);
			   delete_node_4(parent,parent->size,index_parent);
			   return 0;}
			   
		 if (curr == root && root->size == 0)
		     {delete root; root = nullptr;return 1;}
	    }  
	  else 
	  {
		//delete key from the not sheet
	   left_child = curr->children[index];
	   right_child = curr->children[index+1];
	   
	   if (x == nullptr)
	     { 
		   k = delete_node_5(curr,index,y);
	       if (k == 1)
	          return 1;
		   buf = curr->values+index;
		   res = DeleteNode_2(left_child->values[left_child->size-1].get_head()->get_node(),curr,left_child,index,buf);
		  }
	  else
	       res = DeleteNode_2 (right_child->values[right_child->size-1].get_head()->get_node(),curr,right_child,index+1,x);
	  }
     }
      
	  if (res == 0)
	  {
	   if (curr->size >= m)
	            return 1;
	 
	   if (index_parent > 0)
		   { 
		     if (parent != nullptr)
			 {
		      left_neigh = parent->children[index_parent-1];
		       if (left_neigh && left_neigh->size > m) //the left neighbor with more than m keys
	             {
				    MoveTheKeyFromLeftToRight (left_neigh,curr,parent,index_parent-1);
					return 1;
				 }
			 }
	       }
		  
		   if (index_parent < 2*m)
		  {
		    if (parent != nullptr)
			{
		     right_neigh = parent->children[index_parent+1];
		     if (right_neigh && right_neigh->size > m) //the left neighbor with more than m keys
	             {
				    MoveTheKeyFromRightToLeft (right_neigh,curr,parent,index_parent);
				    return 1;
				 }
			}
	      }
		 
		  if (parent!=nullptr && left_neigh)
		     {
			   MargeNodes (parent,left_neigh,curr,index_parent-1); 
			   delete_node_4(parent,parent->size,index_parent-1);
			   return 0;}
			   
		  if (parent!=nullptr && right_neigh)
		     { 
			   MargeNodes (parent,curr,right_neigh,index_parent);
			   delete_node_4(parent,parent->size,index_parent);
			   return 0;}
			   
		  if (parent!=nullptr)
		    {
			   MargeNodes (parent,curr,right_neigh,index_parent);
			   delete_node_4(parent,parent->size,index_parent);
			   return 0;}
			}
			   
		  if (curr == root && root->size == 0)
		     {b = root;root = root->children[0]; b->children[0] = nullptr; delete b;return 1;}
		
	 return 1;	  
  }
	 
	
	
	
	 
	 void insert(T &y,b_tree_node<T> *&curr,int size,int index,b_tree_node<T> *&first)
	  {
	     int l = size-1;
		 curr->children[size+1] = curr->children[size];
		 while (l>=index)
	    {
		  curr->values[l+1]=(T&&)curr->values[l];
		  curr->children[l+1]=curr->children[l];
		  l--;
	    }
		curr->values[index] = (T&&)y;
		curr->children[index] = first;
		(curr->size)++;
	  }
	 
	 
	 void MoveTheKeyFromLeftToRight (b_tree_node<T> *&left,b_tree_node<T> *&right, b_tree_node<T> *&parent, int index)
	 {
	   insert(parent->values[index],right,right->size,0,left->children[left->size]);
	   left->children[left->size] = nullptr;
	   parent->values[index] = (T&&)left->values[left->size-1];
	   (left->size)--;
	 }
	 
	
	 void MoveTheKeyFromRightToLeft (b_tree_node<T> *&right,b_tree_node<T> *&left, b_tree_node<T> *&parent, int index)
	 {
	   (left->size)++;
	   left->values[left->size-1] = (T&&)parent->values[index];
	   left->children[left->size] = right->children[0];
	   right->children[0] = nullptr;
	   parent->values[index] = (T&&)right->values[0];
	   delete_node_2(right,right->size,0);
	 }
	 
	 
	 
	 void MargeNodes (b_tree_node<T> *&parent, b_tree_node<T> *&left, b_tree_node<T> *&right,int index_parent) 
	 {
	   int i = 0;
	   left->values[left->size] = (T&&)parent->values[index_parent];
	   (left->size)++;
	   for (i = 0; i < right->size; i++)
	   {
	     left->values[left->size] = (T&&)right->values[i];
		 left->children[left->size] = right->children[i];
		 (left->size) ++;
	   }
	     left->children[left->size] = right->children[i];
		 delete right;
		 right = nullptr;
		 parent->children[index_parent+1] = nullptr;
	}
		
	 
	 void delete_node(b_tree_node<T> *&curr, int size, int pos, list_node *y)
	 {
	   int l = pos;
	   curr->values[pos].delete_list_node(y);
	   if (curr->values[pos].get_st() == status::del)
	   {
	     
		 while (l<size-1)
	    {
		  curr->values[l]=(T&&)curr->values[l+1];
		  curr->children[l+1]=curr->children[l+2];
		  l++;
	    }
		curr->children[l+1] = nullptr;
		(curr->size) --;
	   }
	 }
	 
	 int delete_node_5(b_tree_node<T> *&curr,int pos, list_node *y)
	 {
	   curr->values[pos].delete_list_node(y);
	   if (curr->values[pos].get_st() == status::del)
	      return 0;
	   return 1;
	 }
	 
	 
	 
	 void delete_node_4(b_tree_node<T> *&curr, int size, int pos)
	 {
	   int l = pos;
		 while (l<size-1)
	    {
		  curr->values[l]=(T&&)curr->values[l+1];
		  curr->children[l+1]=curr->children[l+2];
		  l++;
	    }
		curr->children[l+1] = nullptr;
		(curr->size) --;
	 }
	 
	  void delete_node_2(b_tree_node<T> *&curr, int size, int pos)
	 {
	   int l = pos;
	   //curr->values[l].delete_b_tree_list();
		 while (l<size-1)
	    {
		  curr->values[l]=(T&&)curr->values[l+1];
		  curr->children[l]=curr->children[l+1];
		  l++;
	    }
		curr->children[l]=curr->children[l+1];
		curr->children[l+1] = nullptr;
		(curr->size) --;
		
	 }
	 
	  void delete_node_3(b_tree_node<T> *&curr, int size, int pos, T*& x)
	 {
	   int l = pos;
	   *x = (T&&)curr->values[l];
		 while (l<size-1)
	    {
		  curr->values[l]=(T&&)curr->values[l+1];
		  curr->children[l+1]=curr->children[l+2];
		  l++;
	    }
		curr->children[l+1] = nullptr;
		(curr->size) --;
	 }
	
	 int Separation (b_tree_node<T> *&first,b_tree_node<T> *&second,int index,T&y)
		 {
		   b_tree_node<T>* p;
		   if (!(p = new b_tree_node<T>))
		         return MEMORY_ERROR;
           if ( p->init(m) != SUCCESS)
		         return MEMORY_ERROR;
		   if (index == m){
		   for ( int i = 2*m-1;i>=m; i--)
		      {
			    p->values[i-m]=(T&&)first->values[i];
				p->children[i-m+1]=first->children[i+1];
				first->children[i+1] = nullptr;
			  }
		   p->children[0]=second;
		   second = p;
		   first->set_size (m);
		   second->set_size (m);
		   return 1;
		   }
		   if (index > m){
		   p->children[m]=first->children[2*m];
		   for (int i = 2*m-1;i>=index; i--)
		      {
			    p->values[i-m]=(T&&)first->values[i];
				p->children[i-m+1]=first->children[i+1];
				first->children[i+1] = nullptr;
			  }
		   p->children[index-m]=second;
		   p->values[index-m-1]=(T&&)y;
		   for (int i = index-1 ;i>m; i--)
		      {
			    p->values[i-m-1]=(T&&)first->values[i];
				p->children[i-m]=first->children[i+1];
				first->children[i+1] = nullptr;
			  }
		   p->children[0] = first->children[m+1];
		   first->children[m+1] = nullptr;
		   y = (T&&)first->values[m];
		   second = p;
		   second->set_size(m);
		   first->set_size(m);
		   return 1;
		   } 
		   if (index < m){
		   for ( int i = 2*m-1;i>=m; i--)
		      {
			    p->values[i-m]=(T&&)first->values[i];
				p->children[i-m+1]=first->children[i+1];
				first->children[i+1] = nullptr;
			  }
		   for ( int i = m; i>index; i--)
		     {
		     first->values[i] = (T&&) first->values[i-1];
		     first->children[i+1] = first->children[i];
		     }
		   first->children[index+1] = second;
		   first->values[index] = (T&&)y;
		   p->children[0] = first->children[m+1];
		   first->children[m+1] = nullptr;
		   y = (T&&)first->values[m];
		   second = p;
		   second->set_size(m);
		   first->set_size(m);
		   return 1;
		   }
		  return 1;
		 }



      void Insert(T &y,b_tree_node<T> *&first,int size,int index,b_tree_node<T> *&second)
	  {
	     int l = size-1;
		 while (l>=index)
	    {
		  first->values[l+1]=(T&&)first->values[l];
		  first->children[l+2]=first->children[l+1];
		  l--;
	    }
		first->values[index] = (T&&)y;
		first->children[index+1] = second;
	  }
  
      int binary_search (T *node, T &x, int size, int *flag = nullptr)
   {
    (void) flag;
    int mid, r_bor, l_bor,res;
    r_bor = size; l_bor = 0;
    while (l_bor != r_bor)
    { 
	  mid=(int)((r_bor+l_bor)/2);
	  res = x.get_head()->get_node()->COMPARE(node[mid].get_head()->get_node());
      if (res > 0)
          l_bor = ++mid;
	  else{
          r_bor = mid;
		  if (res == 0)
		     *flag = 1;
		  }
    }
    return r_bor;
   } 
   
    int search (T *node, list_node *x, int size, int *flag = nullptr)
   {
    (void) flag;
    int mid, r_bor, l_bor,res;
    r_bor = size; l_bor = 0;
    while (l_bor != r_bor)
    { 
	  mid=(int)((r_bor+l_bor)/2);
	  res = x->COMPARE(node[mid].get_head()->get_node());
      if (res > 0)
          l_bor = ++mid;
	  else{
          r_bor = mid;
		  if (res == 0)
		     *flag = 1;
		  }
    }
    return r_bor;
   } 
   


	/*  int read ( const char *name)
{
  FILE *fp;T x;b_tree_node<T> *pos = root;
  int res,ef;
  if (!(fp = fopen (name,"r")))
	  return T::ERROR_OPEN;

  while ((res = x.read(fp)) == T::SUCCESS)
{ 
  ef = init (pos,x);
  if ( ef != SUCCESS )
       return MEMORY_ERROR;
  pos = root;
}	  

  if (!feof(fp))
{
  fclose (fp);
  return ERROR_READ;
}	  

  fclose (fp);
  return SUCCESS;
}*/

	  ~b_tree()
	  {
		  delete_tree(root);
      }

#if 1
      void delete_tree(b_tree_node<T> *&root)
	  {
       if (root == nullptr)
	      return;
       for (int i=0;i<2*m+1;i++)
	        if (root->children[i])
	            delete_tree(root->children[i]);
       delete root;
	   root = nullptr;
       }
#else
	 void delete_tree(b_tree_node<T> *root)
	  {
       if (root == nullptr)
	      return;
       for (int i=0;i<2*m+1;i++)
	  // {
			if (root->children)
			{
				 if (root->children[i])
					delete_tree(root->children[i]);
			}
		//}
       delete root;
	   this->root = nullptr;
       }
#endif
	  void print (int r)
	  {print_node(r,0,root);}
	  
	  
	  int OutputRecord (command &y,FILE *fp)
	  {return print_node_(y,fp,root);}
	  
	  int SortOutputRecord (list2 *LIST2, command &y)
	  {(void) y;
	  return sortprint_node(LIST2,root);
	  }
	  
	  
	  int  sortprint_node(list2 *LIST2,b_tree_node<T> *pos)
	  {   
	   int res = 0, ans = 0;
	   if (pos == nullptr)
	       return 0;
	   int j = pos->get_size();
	   for (int i=0; i<j; i++)
	   {
	     res += pos->values[i].sortprint_(LIST2);
	   }
       for (int i=0;i<(j+1);i++){
	        if (pos->children[i])
	            {ans += sortprint_node(LIST2,pos->children[i]);}}
	   return res+ans;
       } 
	   
	  int  print_node_(command &y,FILE *fp,b_tree_node<T> *pos)
	  {   
	   int res = 0, ans = 0;
	   if (pos == nullptr)
	       return 0;
	   int j = pos->get_size();
	   for (int i=0; i<j; i++)
	   {
	     res += pos->values[i].print_(y, fp);
	   }
       for (int i=0;i<(j+1);i++){
	        if (pos->children[i])
	            {ans += print_node_(y,fp,pos->children[i]);}}
		return res+ans;
       } 
	  
	  void print_node(int max_level, int level,b_tree_node<T> *pos)
	  {   
	   if (pos == nullptr)
	       return;
	   int spaces = level*2;
	   if (max_level <= level) return;
	   int j = pos->get_size();
	   for (int i=0; i<j; i++)
	   {
	     (pos->values[i]).print(spaces);
		 printf("\n");
	   }
       for (int i=0;i<(j+1);i++)
	        if (pos->children[i])
	            {print_node(max_level, level+1,pos->children[i]);}
       } 
	   
//Непосредственно задачи 	   
  int f1(int k,b_tree_node<T> *pos = nullptr)
{
  int res,n,count;
  res = 0;count = 0;
  if (pos == nullptr)
	  pos = root;
  n = pos->get_size();
 for (int i = 0; i < n+1; i++)
 {
      if (pos->children[i])
	  {
	    count ++;
		res += f1(k,pos->children[i]);
	  }
 }
 if ( count == k )
    return res+n;
 return res;	  
}


int f2(int k,int *stud,int *node, b_tree_node<T> *pos = nullptr)
{
  int res = 0;int n;int step = 0;
  if (pos == nullptr)
	  pos = root;
  if (k == 0)
      return 0;
  n = pos->get_size();
  for (int i = 0; i < n+1; i++)
  {
	  int stud_level = 0;int node_level = 0;
	  if (pos->children[i])
	    {  
		   step += f2(k,&stud_level,&node_level,pos->children[i]);
	       (*stud) += stud_level;
		   (*node) += node_level;
		}
  }
  (*node)++; (*stud)+= n;
  if ((*node)<= k)
     res = step + (*stud);
  else res = step;
  return res;
}

	
 int f3(int k,int *stud,int *deep, b_tree_node<T> *pos = nullptr)
{
  int res = 0;int n;int step = 0;
  if (pos == nullptr)
	  pos = root;
  if (k == 0)
      return 0;
  n = pos->get_size();
  for (int i = 0; i < n+1; i++)
  {
	  int stud_level = 0;int node_level = 0;
	  if (pos->children[i])
	    {  
		   step += f3(k,&stud_level,&node_level,pos->children[i]);
	       (*stud) += stud_level;
		   if ((*deep) < node_level)
		       (*deep) = node_level;
		}
  }
  (*deep)++; (*stud)+= n;
  if ((*deep)<= k)
     res = step + (*stud);
  else res = step;
  return res;
}
	
 
		
  int f4(int k,b_tree_node<T> *pos = nullptr)
{
	int res1=1;int res2=0;int max = 0;
	if (pos ==nullptr)
	    pos = root;
	if (k==0)
		return 0;
	for (int i=1;res1; i++)
	{
	 res1 = Maximum(k,i,1,pos);
	 if (res1 > k)
	 {break;}
	}
	if (res1)
	{ 
	   int n = pos->size;
	   for (int i = 0; i< n+1; i++)
	  { 
	    if (pos->children[i])
	      res2 += f4(k,pos->children[i]);
	  }
	  return res2;
	}
	else
	{
	  res1 = count_node_of_tree(&max,pos);
	}
  return res1;
}

int count_node_of_tree (int *stud,b_tree_node<T> *pos)
{   
	int count = 0;int n;
	if (!pos)
		return 0;
	n = pos->size;
    for (int i = 0; i < n+1; i++)
    {
	  int stud_level = 0;
	  if (pos->children[i])
	    {  
		   count += count_node_of_tree(&stud_level,pos->children[i]);
	       (*stud) += stud_level;
		}
     }
  (*stud)+= n;
  return count+(*stud);
}


int Maximum(int k,int level,int j,b_tree_node<T> *pos)
{ 
  int count = 0;int n;
  if (!pos)
	  return 0;
  n = pos->size;
  if (j==level)
    { 
	  for (int i = 0; i < n+1; i++)
	      if (pos->children[i])
		      count++;
    }
  else
    {
      for (int i = 0; i < n+1; i++)
	  {
          count += Maximum(k,level, j+1,pos->children[i]);
	  }
    }
 return count;
}


int f5(int k)
{ 
   int res;
   res = maximum(k,0,root);	
 return res;
}


int maximum(int level,int j,b_tree_node<T> *pos)
{ 
  int count = 0;int n;
  if (!pos)
	  return 0;
  n = pos->size;
  if (j==level)
	  {return n;}
  else
  {
    for (int i = 0; i<n+1; i++)
	  {  
        count += maximum(level,j+1,pos->children[i]);
	  }
  }
 return count;
}

int f6 (int k,int count,int stud,b_tree_node<T> *pos)
{	
  int res = 0;int n;int flag = 0;
  n = pos->size;
  for (int i = 0; i < n+1; i++)
  {
     if (pos->children[i])
	    {flag = 1;res += f6(k,count+1,stud + pos->children[i]->size,pos->children[i]);}
  }
  if (!flag)
     {
	   if (count == k)
	      return stud;
	   else return 0;
	  }
  
 return res;
}

};

#endif //B_TREE_H