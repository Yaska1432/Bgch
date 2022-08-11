#ifndef LIST_H
#define LIST_H

#include <cstdio>
#include "conditions.h"
#include "record.h"

//template <class T> class list;

template <class T>
class list_node
{
	friend class list<T>;
	friend class list<list2_node<T> *>;
	friend class database;
	friend bool apply_command(const command &comm, const list2_node<record> *const x);
	friend void print_record(const list2_node<record> *const x, const ordering order[], const int max_order, FILE *const out);
	friend record *get_address_record(list_node<list2_node<record> *> *const x);
private:
	T data;
	list_node<T> *next = nullptr;

public:
	list_node() = default;
	~list_node() = default;

	static void mergesort(list_node<T> *&list, const ordering order_by[], const int max_ordering);
	static list_node<T> *merge(list_node<T> *list1, list_node<T> *end_list1, list_node<T> *list2, list_node<T> *end_list2, list_node<T> *&end, const ordering order_by[], const int max_ordering);

	void print(const ordering order[] = nullptr, const int max_order = 3, FILE *const out = stdout) const
	{
		for( const list_node<T> *tmp = this; tmp; tmp = tmp->next )
			tmp->data->print(order, max_order, out);
	}
};


template <class T>
class list
{
friend class database;
private:
	list_node<T> *head = nullptr;

public:
	list() = default;
	~list() {del();}
	bool find(const record &x) const
	{
		for( list_node<T> *curr = head; curr; curr = curr->next )
		{ if( x==curr->data->data ) return true; }
		return false;
	}
	bool add_head(T x)
	{
		list_node<T> *tmp = new list_node<T>;
		if( !tmp ) return false;
		tmp->data = static_cast<T &&>(x);
		tmp->next = head;
		head = tmp;
		return true;
	}

	void mergesort(const ordering order_by[], const int max_order)
	{ list_node<T>::mergesort(head, order_by, max_order); }

	void print(const ordering order[], const int max_order, FILE *out = stdout) const
	{ head->print(order, max_order, out); }
	bool select(const command &comm, int &n_printed, FILE *const out = stdout) const;

	void del()
	{
		list_node<T> *tmp;
		while( head )
		{
			tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	void del(const T &x);// Remove only first match
};

template <class T>
bool list<T>::select(const command &comm, int &n_printed, FILE *const out) const
{
	n_printed = 0;
	if( comm.order_by[0]==ordering::none )
	{
		for( list_node<T> *curr = head; curr; curr = curr->next )
		{
			if( apply_command(comm, curr->data) )
			{
				n_printed++;
				print_record(curr->data, comm.order, comm.max_order, out);
			}
		}
		return true;
	}

	list<record *> applied;
	for( list_node<T> *curr = head; curr; curr = curr->next )
	{
		if( apply_command(comm, curr->data) )
		{
			n_printed++;
			if( !applied.add_head( get_address_record(curr) ) )
			{
				n_printed = 0;
				return false;
			}
		}
	}
	applied.mergesort(comm.order_by, comm.max_order);
	applied.print(comm.order, comm.max_order, out);
	return true;
}

template <class T>
void list_node <T>::mergesort(list_node<T> *&list, const ordering order_by[], const int max_order)
{
	list_node<T> *list1, *list2, *tmp, *merged, *result = nullptr, 
		*merged_end, *new_end, *end_list1, *end_list2;

	for( int size = 1; true; size *= 2)// Max size of merged parts
	{
		merged_end = nullptr;
		while( true )// Merge all parts that possible
		{
			if( !(list1 = list) ) 
			{
				if( !merged_end ) return;
				break;
			}
			// Make list1 nullptr-terminated
			tmp = list1;
			for( int i = 0; i<(size - 1); i++ )
			{
				if( !(tmp = tmp->next) ) break;
			}
			if( !tmp || !(list2 = tmp->next) )
			{
				if( !merged_end ) return;
				merged_end->next = list1;
				break;
			}
			tmp->next = nullptr;
			end_list1 = tmp;

			// Make list2 nullptr-terminated
			tmp = list2;
			for( int i = 0; i<(size - 1); i++ )
			{
				if( !tmp->next ) break;
				tmp = tmp->next;
			}
			list = tmp->next;
			tmp->next = nullptr;
			end_list2 = tmp;

			merged = list_node<T>::merge(list1, end_list1, list2, end_list2,
				new_end, order_by, max_order);
			if( !merged_end )
				result = merged;
			else
				merged_end->next = merged;
			merged_end = new_end;
		}
		list = result;
	}
}

template <class T>
list_node <T> *list_node<T>::merge(list_node<T> *list1, list_node<T> *end_list1, list_node<T> *list2, list_node<T> *end_list2, list_node<T> *&end, const ordering order_by[], const int max_order)
{
	list_node<T> *merged;
	if( record::compare(*list1->data, *list2->data, order_by, max_order)<=0 )
	{
		merged = list1;
		list1 = list1->next;
	} else
	{
		merged = list2;
		list2 = list2->next;
	}

	list_node<T> *tmp;
	for( tmp = merged; list1 && list2; tmp = tmp->next )
	{
		if( record::compare(*list1->data, *list2->data, order_by, max_order)<=0 )
		{
			tmp->next = list1;
			list1 = list1->next;
		} else
		{
			tmp->next = list2;
			list2 = list2->next;
		}
	}
	if( list1 )
	{
		tmp->next = list1;
		end = end_list1;
	} else
	{
		tmp->next = list2;
		end = end_list2;
	}

	return merged;
}


template <class T>
void list<T>::del(const T &x)
{
	if( !head ) return;

	list_node<T> *tmp;
	while( x==head->data )
	{
		tmp = head->next;
		delete head;
		head = tmp;
		return;
	}

	list_node<T> *curr = head;
	while( curr->next )
	{
		if( x==curr->next->data )
		{
			tmp = curr->next->next;
			delete curr->next;
			curr->next = tmp;
			return;
		}
		curr = curr->next;
	}
}
#endif// LIST_H
