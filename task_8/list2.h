#ifndef LIST2_H
#define LIST2_H

#include <cstdio>
#include "list2_node.h"
#include "commands.h"
#include "list.h"
#include "record.h"
#include "inline.h"

class database;

template <class T>
class list2
{
	friend class database;

private:
	list2_node<T> *head = nullptr;

public:
	list2() = default;
	~list2() { del(); }

	bool find(const record &x) const
	{
		for( list2_node<T> *curr = head; curr; curr = curr->next )
			if( x==curr->data->data ) return true;
		return false;
	}

	bool add_head(T &x)
	{
		list2_node<T> *tmp = new list2_node<T>;
		if( !tmp ) return false;
		tmp->data = static_cast<T &&>(x);
		if( head ) head->prev = tmp;
		tmp->next = head;
		head = tmp;
		return true;
	}
	void del_head()
	{
		if( !head ) return;
		list2_node<T> *tmp = head->next;
		delete head;
		head = tmp;
	}

	bool select(const command &comm, int &n_printed, FILE *const out = stdout) const;

	void del()
	{
		list2_node<T> *tmp;
		while( head )
		{
			tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	void del(const command &comm);
	void del(const T &x);

	void print(const ordering order[] = nullptr, const int max_order = 3,
		FILE *const out = stdout)
	{
		for( list2_node<T> *tmp = head; tmp; tmp = tmp->next )
			print_record(tmp->data, order, max_order, out);
	}
};


template <class T>
bool list2<T>::select(const command &comm, int &n_printed, FILE *const out) const
{
	n_printed = 0;
	if( comm.order_by[0]==ordering::none )
	{
		for( list2_node<T> *curr = head; curr; curr = curr->next )
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
	for( list2_node<T> *curr = head; curr; curr = curr->next )
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
void list2<T>::del(const command &comm)
{
	list2_node<T> *tmp;
	while( head && apply_command(comm, head->data) )
	{
		if( (tmp = head->next) ) tmp->prev = nullptr;
		delete head;
		head = tmp;
	}
	if( !head ) return;

	list2_node<T> *curr = head->next;
	while( curr )
	{
		if( apply_command(comm, curr->data) )
		{
			if( curr->prev ) curr->prev->next = curr->next;
			if( (tmp = curr->next) ) curr->next->prev = curr->prev;
			delete curr;
			curr = tmp;
			continue;
		}
		curr = curr->next;
	}
}

template <class T>
void list2<T>::del(const T &x)
{
	if( !head ) return;
	list2_node<T> *tmp;
	while( x==head->data )
	{
		if( (tmp = head->next) ) tmp->prev = nullptr;
		delete head;
		head = tmp;
		return;
	}
	list2_node<T> *curr = head->next;
	while( curr )
	{
		if( x==curr->data )
		{
			if( curr->prev ) curr->prev->next = curr->next;
			if( (tmp = curr->next) ) curr->next->prev = curr->prev;
			delete curr;
			curr = tmp;
			return;
		}
		curr = curr->next;
	}
}
#endif// LIST2_H
