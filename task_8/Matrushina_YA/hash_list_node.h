#ifndef HASH_LIST_NODE_H
#define HASH_LIST_NODE_H
#include "list_node.h"
# include "ordering.h"
# include "list2.h"

template <class T> class hash_list;
template <class T>
class hash_list_node
{
	private:
		hash_list_node<T> *next = nullptr;
	    hash_list_node<T> *prev = nullptr;
		int curr_size = 0;
		int m = 1;
		T **array = nullptr;
	public:
		
		friend class hash_list<T>;
		hash_list_node() = default;
		~hash_list_node(){
			delete_hash_list_node();
		}
	
		hash_list_node* get_next()
	     {return next;}
	
		void set_next(hash_list_node *x)
	     {
		   next = x;
		 }
	
		hash_list_node* get_prev()
	     {return prev;}
	
		void set_prev(hash_list_node *x)
	     {
		   prev = x;
		 }
	
		void delete_hash_list_node(){
			if (array != nullptr)
				delete[]array;
			array = nullptr;
			curr_size = 0;
		}
	
		void set_m(int parameter)
		{ m = parameter;}
	
		int get_m()
		{return m;}
	
		int get_curr_size()
		{ return curr_size;}
	
		bool init (T *x){
			if (array == nullptr){
				if (!(array = new T*[m]))
					return false;
				else array[0] = x;
			}
			else{
				int place = binary_search (array,x,curr_size);
				for (int i = curr_size; i > place; i--)
					array[i] = array[i-1];
				array[place] = x;
			}
			curr_size++;
			return true;
		}
		
		int binary_search (T **arr, T *x, int size){
			int mid, r_bor, l_bor,res;
			r_bor = size; l_bor = 0;
			while (l_bor != r_bor)
			{ 
				mid=(int)((r_bor+l_bor)/2);
				res = x->full_compare(arr[mid]);
				if (res > 0)
					l_bor = ++mid;
				else
					r_bor = mid;
			}
			return r_bor;} 
	
		int search (T *x, int size){
			int mid, r_bor, l_bor,res,fl = 0;
			r_bor = size; l_bor = 0;
			while (l_bor != r_bor)
			{ 
				mid=(int)((r_bor+l_bor)/2);
				res = x->full_compare(array[mid]);
				if (res > 0)
					l_bor = ++mid;
				else{
					{if (res == 0)
						fl = 1;}
					r_bor = mid;}
			}
			if (fl == 1)
				return r_bor;
			else
				return -1;
		}
		
		int poisk (command &x){
			int mid, r_bor, l_bor,res;
			r_bor = curr_size; l_bor = 0;
			while (l_bor != r_bor)
			{ 
				mid=(int)((r_bor+l_bor)/2);
				res = array[mid]->_compare(x);
				if (res < 0)
					l_bor = ++mid;
				else
					r_bor = mid;
		  }
			return r_bor;
		} 
		
		
		
		 int poisk_first (command &x){
			int mid, r_bor, l_bor,res;
			r_bor = curr_size; l_bor = 0;
			while (l_bor != r_bor)
			{ 
				mid=(int)((r_bor+l_bor)/2);
				res = array[mid]->_compare(x);
				if (res < 0)
					l_bor = ++mid;
				else
					r_bor = mid;
		  }
			return r_bor;
		} 
		
		int poisk_last (command &x){
			int mid, r_bor, l_bor,res;
			r_bor = curr_size; l_bor = 0;
			while (l_bor != r_bor)
			{ 
				mid=(int)((r_bor+l_bor)/2);
				res = array[mid]->_compare(x);
				if (res <= 0)
					l_bor = ++mid;
				else
					r_bor = mid;
		  }
			return r_bor;
		} 
	
		bool del (T *x){
			int i = 0;
			if (array == nullptr)
				return false;
			int place = search (x,curr_size);
			if (place == -1)
				return false;
			for (i = place; i < curr_size-1; i++)
				array[i] = array[i+1];
			array[curr_size-1] = nullptr;
			curr_size--;
			return true;
		}
		
		void print(){
			if (curr_size == 0)
				return;
			for (int i = 0; i<curr_size; i++)
				array[i]->Print();
		}
		
		
		int print_(command &y,FILE *fp){
			int res = 0;
			if (curr_size == 0)
				return 0;
			for (int i = 0; i<curr_size; i++)
				{array[i]->print(y.order,fp);res++;}
		return res;
		}
		
		int sortprint_(list2 *LIST2){
			int res = 0;
			if (curr_size == 0)
				return 0;
			for (int i = 0; i<curr_size; i++)
				{LIST2->init(array[i]);res++;}
		return res;
		}
		
		
		int SearchAndOutputRecord(command &y,FILE *fp){
			int pos_first = 0,pos_last = 0,res = 0;
			//print();
			switch (y.get_c_phone()){
				case condition::eq:
				{
					pos_first = poisk_first(y);
					pos_last = poisk_last(y);
					//printf("%d %d\n",pos_first, pos_last);
					
					for ( int i = pos_first; i < curr_size && i < pos_last; i++){
						if (y.apply(*(array[i])))
							{array[i]->print(y.order,fp);res++;}
					}
				}
				break;
				
				case condition::lt:
				{
					
					pos_first = poisk_first(y);
					//printf("%d \n",pos_first);
					for ( int i = 0; i < pos_first && i < curr_size; i++){
						if (y.apply(*(array[i])))
							{array[i]->print(y.order,fp);res++;}
					}
				}
				break;
				
				case condition::gt:
				{
					pos_last = poisk_last(y);
					//printf("%d \n",pos_last);
					for ( int i = pos_last; i < curr_size; i++){
						if (y.apply(*(array[i])))
							{array[i]->print(y.order,fp);res++;}
					}
				}
				break;
				
				case condition::le:
				{
					pos_last = poisk_last(y);
					//printf("%d \n",pos_last);
					for ( int i = 0; i < pos_last && i < curr_size; i++){
						if (y.apply(*(array[i])))
							{array[i]->print(y.order,fp);res++;}
					}
				}
				break;
				
				case condition::ge:
				{
					pos_first = poisk_first(y);
					//printf("%d \n",pos_first);
					for ( int i = pos_first; i < curr_size; i++){
						if (y.apply(*(array[i])))
							{array[i]->print(y.order,fp);res++;}
					}
				}
				break;
				
				case condition::ne:
				{
					for ( int i = 0; i < curr_size; i++){
						if (y.apply(*(array[i])))
							{array[i]->print(y.order,fp);res++;}
					}
				}
				break;
				
				default:;
			}
			return res;
		}
		
		
		int SearchSortAndOutputRecord(list2 *LIST2, command &y){
			int pos_first = 0,pos_last = 0,res = 0;
			switch (y.get_c_phone()){
				case condition::eq:
				{
					pos_first = poisk_first(y);
					pos_last = poisk_last(y);
					for ( int i = pos_first; i < curr_size && i < pos_last; i++){
						if (y.apply(*(array[i])))
							{LIST2->init(array[i]);res++;}
						else break;
					}
				}
				break;
				
				case condition::lt:
				{
					pos_first = poisk_first(y);
					for (int i = 0; i < pos_first && i < curr_size; i++){
						if (y.apply(*(array[i])))
							{LIST2->init(array[i]);res++;}
					}
				}
				break;
				
				case condition::gt:
				{
					pos_last = poisk_last(y);
					for ( int i = pos_last; i < curr_size; i++){
						if (y.apply(*(array[i])))
							{LIST2->init(array[i]);res++;}
					}
				}
				break;
				
				case condition::le:
				{
					pos_last = poisk_last(y);
					for ( int i = 0; i < pos_last && i < curr_size; i++){
						if (y.apply(*(array[i])))
							{LIST2->init(array[i]);res++;}
					}
				}
				break;
				
				case condition::ge:
				{
					pos_first = poisk_first(y);
					for ( int i = pos_first; i < curr_size; i++){
						if (y.apply(*(array[i])))
							{LIST2->init(array[i]);res++;}
					}
				}
				break;
				
				case condition::ne:
				{
					for ( int i = 0; i < curr_size; i++){
						if (y.apply(*(array[i])))
							{LIST2->init(array[i]);res++;}
					}
				}
				break;
				
				default:;
			}
			return res;
		}


};

#endif //HASH_H