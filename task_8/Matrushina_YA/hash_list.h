#ifndef HASH_LIST_H
#define HASH_LIST_H
#include "hash_list_node.h"
#include "list_node.h"
# include "list2.h"

template <class T> class hash;
template <class T>
class hash_list
{
	private:
		hash_list_node<T> *head = nullptr;
		int m = 1;
	public:
		friend class hash<T>;
		
		hash_list() = default;
	
		~hash_list(){
			delete_hash_list();
		}
		
		void set_m(int parameter)
		{ m = parameter;}
	
		void delete_hash_list(){
			hash_list_node<T> *curr = nullptr, *next = nullptr;
			for (curr = head; curr; curr = next)
			{
				next = curr->get_next();
				delete curr;
			}
			head = nullptr;
		}
	
		bool init (T *node){
			hash_list_node<T> *curr = nullptr;
			hash_list_node<T> *prev = nullptr;
			if (head == nullptr){
				if (!(head = new hash_list_node<T>))
					return false;
				else {head->set_m(m);head->init(node);}
			}
			else {
				for (curr = head; curr; curr = curr->get_next()){
					prev = curr;
					if (curr->get_curr_size() < curr->get_m()){
						return curr->init(node);}
				}
				if (curr == nullptr){
					if (!(curr = new hash_list_node<T>))
						return false;
				 	else{
					prev->set_next(curr);
					curr->set_prev(prev);
					curr->set_m(m);
					return curr->init(node);
					}
				}
			}
		return true;
		}
		
		void del (T *node){
		    int size = 0;
			hash_list_node<T> *curr = nullptr;
			if (head == nullptr)
				return;
			for (curr = head; curr; curr = curr->get_next()){
					if (curr->del(node)){
						size = curr->get_curr_size();
						if (size == 0)
							{del_hash_list_node(curr);}
						return;
						 }
			}
		}
		
		void del_hash_list_node(hash_list_node<T> *x){
			hash_list_node<T> *buf_prev,*buf_next;
			if (x == head){
				buf_next = x->get_next();
				if (buf_next != nullptr){
					buf_next->set_prev(nullptr);}
				delete head;
				head = buf_next;
				return;}
			buf_prev = x->get_prev();
			buf_next = x->get_next();
			buf_prev->set_next(buf_next);
			if (buf_next != nullptr){
				buf_next->set_prev(buf_prev);}
			delete x;
		}
		
		void print(){
			hash_list_node<T> *curr = nullptr;
			for (curr = head; curr; curr = curr->get_next()){
				curr->print();
				printf("\n");}
		}
		
		int print_(command &y,FILE *fp){
			hash_list_node<T> *curr = nullptr;
			int res = 0;
			for (curr = head; curr; curr = curr->get_next())
				res +=curr->print_(y,fp);
		return res;
		}
		
		
		int sortprint_(list2 *LIST2){
			hash_list_node<T> *curr = nullptr;
			int res = 0;
			for (curr = head; curr; curr = curr->get_next())
				res +=curr->sortprint_(LIST2);
		return res;
		}
		
		int SearchAndOutputRecord(command &y,FILE *fp){
			hash_list_node<T> *curr;
			int res = 0;
			for (curr = head; curr; curr = curr->get_next())
				res += curr->SearchAndOutputRecord(y,fp);
			return res;
		}
	   
		int SearchSortAndOutputRecord(list2 *LIST2,command &y){
			hash_list_node<T> *curr;
			int res = 0;
			for (curr = head; curr; curr = curr->get_next())
				res += curr->SearchSortAndOutputRecord(LIST2,y);
			return res;
		}
};

#endif //HASH_LIST_H