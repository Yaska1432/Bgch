#include "data.h"
#include "inline.h"

#define MAX_LEN_CONF_STR 1234
#define NAME_CONF_HT_PHONE "CONFIG_HASH_TABLE_PHONE=\0"
#define NAME_CONF_HT_NAME "CONFIG_HASH_TABLE_NAME=\0"

void database::del_list_table(const command &comm)
{
	list2_node<record> *tmp;
	while( main_list.head && comm.apply(main_list.head->data) )
	{
		if( (tmp = main_list.head->next) ) tmp->prev = nullptr;
		ht_name.del(main_list.head->data.get_name(), main_list.head);
		delete main_list.head;
		main_list.head = tmp;
	}
	if( !main_list.head ) return;

	list2_node<record> *curr = main_list.head->next;
	while( curr )
	{
		if( comm.apply(curr->data) )
		{
			if( curr->prev ) curr->prev->next = curr->next;
			if( curr->next ) curr->next->prev = curr->prev;
			tmp = curr->next;
			ht_name.del(curr->data.get_name(), curr);
			delete curr;
			curr = tmp;
			continue;
		}
		curr = curr->next;
	}
}

template <class T_expr>
void database::del_table_list(const hash_table<T_expr> *ht, const T_expr expr, const command &comm)
{
	list<list2_node<record> *> *hash_list = ht->entries + ht->hash(expr);

	list_node<list2_node<record> *> *tmp;
	while( hash_list->head && apply_command(comm, hash_list->head->data) )
	{
		if( hash_list->head->data==main_list.head )
			main_list.head = main_list.head->next;
		if( hash_list->head->data->prev )
			hash_list->head->data->prev->next = hash_list->head->data->next;
		if( hash_list->head->data->next )
			hash_list->head->data->next->prev = hash_list->head->data->prev;
		delete hash_list->head->data;
		tmp = hash_list->head->next;
		delete hash_list->head;
		hash_list->head = tmp;
	}
	if( !hash_list->head ) return;
	list_node<list2_node<record> *> *curr = hash_list->head;
	while( curr->next )
	{
		if( apply_command(comm, curr->next->data) )
		{
			if( curr->next->data==main_list.head )
				main_list.head = main_list.head->next;
			if( curr->next->data->prev )
				curr->next->data->prev->next = curr->next->data->next;
			if( curr->next->data->next )
				curr->next->data->next->prev = curr->next->data->prev;
			delete curr->next->data;
			tmp = curr->next->next;
			delete curr->next;
			curr->next = tmp;
			continue;
		}
		curr = curr->next;
	}
}


bool database::read_config(FILE *const in)
{
	char buf[MAX_LEN_CONF_STR];
	int k;
	const char * pos = nullptr;
	while( fgets(buf, MAX_LEN_CONF_STR, in) )
	{
		if (*buf == '#') continue;
		pos = buf + strspn (buf, " \t\n");
		if (sscanf (pos, "%d", &k) != 1 || !ht_name.set_param(k))
			{ return false; }
		break;
	}
	return true;
}

read_status database::read(FILE *const in)
{
	del();
	if(!ht_name.alloc() ) return read_status::memory;
	if( !(main_list.head = new list2_node<record>) ) return read_status::memory;
	read_status res;
	if( (res = main_list.head->data.read(in))!=read_status::success )
	{
		del();
		if( res==read_status::eof ) return read_status::success;
		return res;
	}
	if( !ht_name.add(main_list.head->data.get_name(), main_list.head) )
	{
		del();
		return read_status::memory;
	}

	list2_node<record> *curr = main_list.head, *tmp;
	if( !(tmp = new list2_node<record>) )
	{
		del();
		return read_status::memory;
	}
	while( (res = tmp->data.read(in))==read_status::success )
	{
		if(!ht_name.add(tmp->data.get_name(), tmp) )
		{
			del();
			return read_status::memory;
		}
		tmp->prev = curr;
		curr->next = tmp;
		curr = tmp;

		if( !(tmp = new list2_node<record>) )
		{
			del();
			return read_status::memory;
		}
	}
	delete tmp;
	if( res!=read_status::eof )
	{
		del();
		return res;
	}
	return read_status::success;
}


apply_status database::apply(command &comm, int &n_printed, FILE *const out)
{
	n_printed = 0;
	switch( comm.type )
	{
	case command_type::none:
		return apply_status::incorrect_command;
	case command_type::quit:
		return apply_status::quit;
	case command_type::insert:
		if( !add(comm) ) return apply_status::memory;
		return apply_status::done;
	case command_type::select:
		if( comm.op!=operation::lor )
		{
			if( comm.c_name==condition::eq )
			{
				if( !ht_name.select(comm.name.get(), comm, n_printed, out) )
				       return apply_status::memory;
				return apply_status::done;
			}
		}
		if( !main_list.select(comm, n_printed, out) )
			return apply_status::memory;
		return apply_status::done;
	case command_type::del:
		if( comm.op!=operation::lor )
		{
			if( comm.c_name==condition::eq )
			{
				del_table_list<char *>(&ht_name, comm.name.get(), comm);
				return apply_status::done;
			}
		}
		del_list_table(comm);
		return apply_status::done;
	}
	return apply_status::done;
}
