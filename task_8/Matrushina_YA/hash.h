#ifndef HASH_H
#define HASH_H
#include <math.h>
#include "hash_list.h"
#include "list_node.h"
# include "condition.h"
# include "list2.h"
template <class T>
class hash
{
	private:
		hash_list<T> *array = nullptr;
		int k = 1;
		int m = 1;
	public:
		hash() = default;
		~hash(){
			del_hash();
		}
		
		void del_hash(){
		if (array != nullptr)
				delete[]array;
		array = nullptr;
		}
			
		void set_k(int parameter)
		{ k = parameter;}
		
		void set_m(int parameter)
		{ m = parameter;}
		
		bool init (T *x)
		{
			if (array == nullptr){
				array = new hash_list<T>[(int)pow(10,k)];
				if (!array)
					return false;}
			int place = x->hash_value(k);
			array[place].set_m(m);
			return array[place].init(x);
		}

        void del (T *x)
		{
			if (array == nullptr)
				return;
			int place = x->hash_value(k);
			array[place].del(x);
		}
		
		
		int SearchAndOutputRecord(command &y,FILE *fp){
			int res = 0, i = 0, size = 0;
			int hash = y.hash_value(k);
			size = (int)pow(10,k);
			switch (y.get_c_phone()){
				case condition::eq:
					res = array[hash].SearchAndOutputRecord(y,fp);
				break;
				
				case condition::lt:
				{
					for (i = 0; i < size; i++)
						res += array[i].SearchAndOutputRecord(y,fp);
				}
				break;
				
				case condition::gt:
				{
					for (i = 0; i < size; i++) 
						res += array[i].SearchAndOutputRecord(y,fp);
				}
				break;
				
				case condition::le:
				{
					for (i = 0; i < size; i++)
						res += array[i].SearchAndOutputRecord(y,fp);
				}
				break;
				
				case condition::ge:
				{
					for (i = 0; i < size; i++) 
						res += array[i].SearchAndOutputRecord(y,fp);
				}
				break;
				
				case condition::ne:
				{
					for (i = 0; i < size; i++)
						res += array[i].SearchAndOutputRecord(y,fp);
				}
				break;
				
				default:;
			}		
			return res;		
		}
		
		int OutputRecord(command &y, FILE *fp){
			int res = 0, size = 0;
			size = (int)pow(10,k);
			for (int i = 0; i < size; i++)
				res += array[i].print_(y,fp);
		return res;
		}
		
		
		int SortOutputRecord(list2 *LIST2,command &y){
			int res = 0, size = 0;
			(void) y;
			size = (int)pow(10,k);
			for (int i = 0; i < size; i++)
				res += array[i].sortprint_(LIST2);
		return res;
		}
		
		
		int SearchSortAndOutputRecord(list2 *LIST2,command &y){
			int res = 0, i = 0, size = 0;
			int hash = y.hash_value(k);
			size = (int)pow(10,k);
			switch (y.get_c_phone()){
				case condition::eq:
					res = array[hash].SearchSortAndOutputRecord(LIST2,y);
				break;
				
				case condition::lt:
				{
					for (i = 0; i < size; i++)
						res += array[i].SearchSortAndOutputRecord(LIST2,y);
				}
				break;
				
				case condition::gt:
				{
					for (i = 0; i < size; i++) 
						res += array[i].SearchSortAndOutputRecord(LIST2,y);
				}
				break;
				
				case condition::le:
				{
					for (i = 0; i < size; i++)
						res += array[i].SearchSortAndOutputRecord(LIST2,y);
				}
				break;
				
				case condition::ge:
				{
					for (i = 0; i < size; i++) 
						res += array[i].SearchSortAndOutputRecord(LIST2,y);
				}
				break;
				
				case condition::ne:
				{
					for (i = 0; i < size; i++)
						res += array[i].SearchSortAndOutputRecord(LIST2,y);
				}
				break;
				
				default:;
			}		
			return res;		
		}
};

#endif //HASH_H