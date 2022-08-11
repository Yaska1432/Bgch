# include <stdio.h>
# include <string.h>
# include "record.h"
# include "command.h"
# include "condition.h"
# include "list_node.h"
# include "list.h"
# include "hash_list_.h"
# include "database.h"
# include "list2.h"
# include "list_node2.h"
# include "hash_list_node.h"
# include "container.h"

char * database::LookingForFileConfig (char *fileway)
{
	char *buf = nullptr;
	buf = strrchr(fileway,'/');
	if (buf == nullptr)
		return nullptr;
    
	fileway[(int)(buf-fileway)+1] = '\0';
	strcat(fileway,"config.txt");
	return fileway;
}

bool database::readConfig (char *fileway)
{
	char *new_fileway = nullptr;
	FILE *fp;
	if (fileway == nullptr)
		return false;
	new_fileway = LookingForFileConfig(fileway);
	if (new_fileway == nullptr)
	  {if (!(fp = fopen ("config.txt","r")))
	      return false;}
	else
	 {
	   if (!(fp = fopen (new_fileway,"r")))
	      return false;
	 }
	char buf[1234];
	int k = 0, i = 0;
	while (fgets(buf,LEN,fp))
	{
		if (parseConfig(buf, &k))
		 {
			switch(i)
			{
				case 0:	
				  TREE.set_m(k);m_tree = k;
				break;
					
				case 1:
				  HASH.set_k(k);k_hash = k;
				break;
					
				case 2:
				  HASH.set_m(k);m_hash = k;
			    break;
					
				default:;
			}
		  i++;
		  if (i>2)
		  {fclose(fp);return true;}
		}
	}
  fclose(fp);
  return false;
}


char* database::cutOutWord(char *string, int *i, char *b, int *fl)
{
  char *buf; 
  while (string[*i] == ' ' || string[*i] == '\n' || string[*i] == '\t')
		     (*i)++;
  buf = string+(*i);
  while (string[*i] && string[*i] != ' ' && string[*i] != '\n' &&  string[*i] != '\t')
         {
	       if (string[*i] == '#')
		      {*fl = 0;break;}
	      (*i)++;
         }
  *b = string[*i];
  string[*i] = '\0';	
  return buf;
}


bool database::parseConfig (char *buf, int *k)
{
	int i = 0;
	char *number;
	char b;
	int res, flag = 1;
	while (buf[i])
	    { 
		   number = cutOutWord(buf,&i,&b,&flag);
	       if (!number[0])
			   return false;
		   if (!flag)
			   return false;
		   res = getNumberByString(number);
		   buf[i] = b;
		   if (res<=0)
			   return false;
		   else 
		   {*k = res; return true;}
		}   
  return false;
}
	

int database::getNumberByString(char* buf)
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

read_status database::read (const char *filename)
	 {
       FILE *fp;
       read_status res;
	   list_node *curr;
	   if (!(fp = fopen (filename,"r")))
	      return read_status::open;
	   curr = new list_node;
         if (!curr)
         {
	      fclose(fp);
          return read_status::memory;
         }
       while ((res = curr->read(fp)) == read_status::success)
        {
         if (!Insert_LIST_TREE(curr))
         {
		  delete curr;
	      fclose(fp);
          return read_status::read;
         }
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


bool database::Insert_LIST_TREE(list_node *rec)
{
  int res, group;
  b_tree_list a,b;
  b_tree_list_node *buf1, *buf2;
  if (CONTAINERS == nullptr){
	  if (!(CONTAINERS = new container[1000]))
		  return false;
  }
  group = rec->get_group();
  if (group >= 1000 or group < 0)
	  return false;
  CONTAINERS[group].HASH.set_m(m_hash);
  CONTAINERS[group].HASH.set_k(k_hash);
  CONTAINERS[group].TREE.set_m(m_tree);
  if (!CONTAINERS[group].HASH.init(rec))
	  return false;
  if(!LIST.init(rec))
	  return false;
  if(!HASH.init(rec))
	  return false;
  if (!(buf1 = new b_tree_list_node))
	  return false;
  if (!(buf2 = new b_tree_list_node))
	  return false;
  buf1->set_node(rec);
  buf2->set_node(rec);
  a.set_head(buf1);
  a.set_tail(buf1);
  a.set_st(status::filled);
  b.set_head(buf2);
  b.set_tail(buf2);
  b.set_st(status::filled);
  res = TREE.init(TREE.get_root(),a);
  if(res != b_tree<b_tree_list>::SUCCESS)
	  return false;
  res = CONTAINERS[group].TREE.init(CONTAINERS[group].TREE.get_root(),b);
  if(res != b_tree<b_tree_list>::SUCCESS)
	return false;
  return true;
}


	
int database::APLY (command &y,FILE *fp)
     {
		switch (y.get_type())
		{
		    case command_type::quit:
			     return -1;
			
			case command_type::insert:
			     return Insert(y,fp);
				 
			case command_type::select:
			     return Select(y,fp);
				 
			case command_type::del:
			     return Delete(y,fp);
				
			default:;
		
		}
	   return 0;
     }
	 
	    
	 
int database::Insert(command &y, FILE *fp)
	 {
	    (void)fp;
	    b_tree_node<b_tree_list> *head = TREE.get_root();
	    if (!TREE.FindNode(y,head))
		   {return 0;}
	    list_node* tmp = new list_node;
	    if (!tmp)
		    return -1;
		tmp->init(y.get_name(),y.get_phone(),y.get_group());
	    Insert_LIST_TREE(tmp);
		return 0;
	 }
	 

	 
int database::Select(command &y, FILE *fp )
{
	  int res = 0;
	  b_tree_node<b_tree_list> *root = TREE.get_root();
	  if (LIST.get_head() == nullptr)
		     return 0;
	 
	  switch (y.order_by[0])
	  {
	    case ordering::none:
		  {
		    if (y.get_c_group() != condition::none && y.get_op() != operation::lor)
			  res = SearchAndOutputRecord(y,fp);
		    else{
			  if (y.get_c_name() != condition::none && y.get_op() != operation::lor)
			      res = TREE.SearchAndOutputRecord(y,root,fp);
			  else {
				  if (y.get_c_phone() != condition::none && y.get_op() != operation::lor)
					  res = HASH.SearchAndOutputRecord(y,fp);
				  else
				      res = LIST.SearchAndOutputRecord(y,fp);}
			}
		   }
		   break;
		default:
		  {  
	         list2 LIST2;
	       if (y.get_c_group() != condition::none && y.get_op() != operation::lor)
			  res = SearchSortAndOutputRecord(&LIST2,y);
		   else{
	         if (y.get_c_name() != condition::none && y.get_op() != operation::lor)
			      res = TREE.SearchSortAndOutputRecord(&LIST2,y,root);
			 else {
				  if (y.get_c_phone() != condition::none && y.get_op() != operation::lor)
					  res = HASH.SearchSortAndOutputRecord(&LIST2,y);
			      else res = LIST.SearchSortAndOutputRecord(&LIST2,y);}
		   }	  
			 if (res)
			 {
	           LIST2.mergeSort(y);
			   LIST2.print(y.order,fp);
			 }
		  }
		  break;
	  }
	
	  return res;
}
       	
	
int database::Delete(command &y, FILE *fp)
  {
    (void) fp;
	b_tree_node<b_tree_list> *iterator = TREE.get_root();
	list_node *head = LIST.get_head();
	if (head == nullptr)
		   return 0;
	if ( y.get_c_name() == condition::none && y.get_c_phone() == condition::none && y.get_c_group() == condition::none )
	     {TREE.delete_tree(iterator);TREE.set_root (nullptr);HASH.del_hash();
		  for ( int i = 0; i < 1000; i++)
		  {
			 iterator = CONTAINERS[i].TREE.get_root();
			 CONTAINERS[i].TREE.delete_tree(iterator);
			 CONTAINERS[i].TREE.set_root(nullptr);
			 CONTAINERS[i].HASH.del_hash();
			  
		  }
		  LIST.delete_list();
		  return 0;}
	
	deleteListTreeNode(y);
 
	return 0;
  }
  
void database::deleteListTreeNode(command &y)
{
  b_tree_node<b_tree_list> *parent = nullptr;
  int index_parent = 0, pos = 0;
  list_node *head = LIST.get_head();
  list_node *curr;
  list_node *buf;
  list_node *x;
  b_tree_list *spisok = nullptr;
  for (curr = head; curr; curr = buf)
  {
	  buf = curr->get_next();
	  b_tree_node<b_tree_list> *c = TREE.get_root();
	  if (y.apply(*curr))
	  {
		 x = curr;
		 pos = x->get_group();
		 HASH.del(x);
		 TREE.DeleteNode_2 (x,parent,c,index_parent,spisok);
		 parent = nullptr; spisok = nullptr; c = CONTAINERS[pos].TREE.get_root();index_parent = 0;
		 CONTAINERS[pos].HASH.del(x);
		 CONTAINERS[pos].TREE.DeleteNode_2 (x,parent,c,index_parent,spisok);
		 LIST.delete_list_node(curr);
	  }
  }
}

  
int database::SearchAndOutputRecord(command &y,FILE *fp)
{
   int res = 0, i = 0;
   int group = y.get_group();
   switch (y.get_c_group()){
		case condition::eq:
		  if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none)
			  res = CONTAINERS[group].TREE.OutputRecord(y,fp);
		   else{
		    if (y.get_c_name() == condition::none)
			   res = CONTAINERS[group].HASH.SearchAndOutputRecord(y,fp);
		    else
			   res = CONTAINERS[group].TREE.SearchAndOutputRecord(y,CONTAINERS[group].TREE.get_root(),fp);
		   }
		break;
				
		case condition::lt:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = 0; i < group; i++)
			     res += CONTAINERS[i].TREE.OutputRecord(y,fp);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = 0; i < group; i++)
			      res += CONTAINERS[i].HASH.SearchAndOutputRecord(y,fp);}
		 	  else
				  for (i = 0; i < group; i++)
			   		res += CONTAINERS[i].TREE.SearchAndOutputRecord(y,CONTAINERS[group].TREE.get_root(),fp);
			}
			}
		break;
				
		case condition::gt:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = group+1; i < 1000; i++)
			     res += CONTAINERS[i].TREE.OutputRecord(y,fp);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = group+1; i < 1000; i++)
			      res += CONTAINERS[i].HASH.SearchAndOutputRecord(y,fp);}
		 		else
				  for (i = group+1; i < 1000; i++)
			   		res += CONTAINERS[i].TREE.SearchAndOutputRecord(y,CONTAINERS[group].TREE.get_root(),fp);
			}
			}
		break;
				
		case condition::le:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = 0; i <= group; i++)
			     res += CONTAINERS[i].TREE.OutputRecord(y,fp);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = 0; i <= group; i++)
			      res += CONTAINERS[i].HASH.SearchAndOutputRecord(y,fp);}
		 	  else
				  for (i = 0; i <= group; i++)
			   		res += CONTAINERS[i].TREE.SearchAndOutputRecord(y,CONTAINERS[group].TREE.get_root(),fp);
			}
			}
		break;
				
		case condition::ge:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = group; i < 1000; i++)
			     res += CONTAINERS[i].TREE.OutputRecord(y,fp);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = group; i < 1000; i++)
			      res += CONTAINERS[i].HASH.SearchAndOutputRecord(y,fp);}
		 	  else
				  for (i = group; i < 1000; i++)
			   		res += CONTAINERS[i].TREE.SearchAndOutputRecord(y,CONTAINERS[group].TREE.get_root(),fp);
			}
			}
		break;
				
		case condition::ne:
			{
			for (i = 0; i < 1000; i++){
				if (i != group){
					if (y.get_c_name() == condition::none)
			   			res += CONTAINERS[i].HASH.SearchAndOutputRecord(y,fp);
		 			else
			   			res += CONTAINERS[i].TREE.SearchAndOutputRecord(y,CONTAINERS[group].TREE.get_root(),fp);
				}
			}
			}
		break;
				
		default:;
		}		
	return res;		 
}

int database::SearchSortAndOutputRecord(list2 *LIST2, command &y)
{
   int res = 0, i = 0;
   int group = y.get_group();
   switch (y.get_c_group()){
		case condition::eq:
		   if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none)
			  res = CONTAINERS[group].TREE.SortOutputRecord(LIST2,y);
		   else{
		    if (y.get_c_name() == condition::none)
			   res = CONTAINERS[group].HASH.SearchSortAndOutputRecord(LIST2,y);
		    else
			   res = CONTAINERS[group].TREE.SearchSortAndOutputRecord(LIST2,y,CONTAINERS[group].TREE.get_root());
		   }
		break;
				
		case condition::lt:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = 0; i < group; i++)
			     res += CONTAINERS[i].TREE.SortOutputRecord(LIST2,y);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = 0; i < group; i++)
			      res += CONTAINERS[i].HASH.SearchSortAndOutputRecord(LIST2,y);}
		 	  else
				  for (i = 0; i < group; i++)
			   		res += CONTAINERS[i].TREE.SearchSortAndOutputRecord(LIST2,y,CONTAINERS[group].TREE.get_root());
			}
			}
		break;
				
		case condition::gt:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = group+1; i < 1000; i++)
			     res += CONTAINERS[i].TREE.SortOutputRecord(LIST2,y);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = group+1; i < 1000; i++)
			      res += CONTAINERS[i].HASH.SearchSortAndOutputRecord(LIST2,y);}
		 	  else
				  for (i = group+1; i < 1000; i++)
			   		res += CONTAINERS[i].TREE.SearchSortAndOutputRecord(LIST2,y,CONTAINERS[group].TREE.get_root());
			}
			}
		break;
				
		case condition::le:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = 0; i <= group; i++)
			     res += CONTAINERS[i].TREE.SortOutputRecord(LIST2,y);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = 0; i <= group; i++)
			      res += CONTAINERS[i].HASH.SearchSortAndOutputRecord(LIST2,y);}
		 	  else
				  for (i = 0; i <= group; i++)
			   		res += CONTAINERS[i].TREE.SearchSortAndOutputRecord(LIST2,y,CONTAINERS[group].TREE.get_root());
			}
			}
		break;
				
		case condition::ge:
			{
			if (y.get_c_phone() == condition::none && y.get_c_name() == condition::none){
			  for (i = group; i < 1000; i++)
			     res += CONTAINERS[i].TREE.SortOutputRecord(LIST2,y);}
		    else{
			  if (y.get_c_name() == condition::none){
			    for (i = group; i < 1000; i++)
			      res += CONTAINERS[i].HASH.SearchSortAndOutputRecord(LIST2,y);}
		 	  else
				  for (i = group; i < 1000; i++)
			   		res += CONTAINERS[i].TREE.SearchSortAndOutputRecord(LIST2,y,CONTAINERS[group].TREE.get_root());
			}
			}
		break;
				
		case condition::ne:
			{
			for (i = 0; i < 1000; i++){
				if (i != group){
					if (y.get_c_name() == condition::none)
			   			res += CONTAINERS[i].HASH.SearchSortAndOutputRecord(LIST2,y);
		 			else
			   			res += CONTAINERS[i].TREE.SearchSortAndOutputRecord(LIST2,y,CONTAINERS[group].TREE.get_root());
				}
			}
			}
		break;
				
		default:;
		}		
	return res;		 
}


