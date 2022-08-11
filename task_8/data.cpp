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
		ht_phone.del(main_list.head->data.get_phone(), main_list.head);
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
			ht_phone.del(curr->data.get_phone(), curr);
			ht_name.del(curr->data.get_name(), curr);
			delete curr;
			curr = tmp;
			continue;
		}
		curr = curr->next;
	}
}


template <class T_expr>
void database::del_table_links_list(const hash_table<T_expr> *ht, const T_expr expr, const command &comm)
{
	list<list2_node<record> *> *hash_list = ht->entries + ht->hash(expr);
	list_node<list2_node<record> *> *tmp;
	
	while( hash_list->head && apply_command(comm, hash_list->head->data) )
	{
		tmp = hash_list->head->next;
		delete hash_list->head;
		hash_list->head = tmp;
	}
	
	if( !hash_list->head ) return;
	list_node<list2_node<record> *> *curr = hash_list->head->next, *prev = hash_list->head;
	while( curr )
	{
		if( apply_command(comm, curr->data) )
		{
			prev->next = curr->next;
			tmp = curr->next;
			delete curr;
			curr = tmp;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}


template <class T_expr>
void database::del_table_list(const hash_table<T_expr> *ht, const T_expr expr, const command &comm)
{
	list<list2_node<record> *> *hash_list = ht->entries + ht->hash(expr);
	list_node<list2_node<record> *> *tmp;
	
	while( hash_list->head && apply_command(comm, hash_list->head->data) )
	{
		command to_del_object;
		char * name = ((record *) (hash_list->head->data))->get_name();
		int phone = ((record *) (hash_list->head->data))->get_phone();
		int group = ((record *) (hash_list->head->data))->get_group();
		to_del_object.init_t (name, phone, group); // Шаблон элемента который удаляется из main_list, для поиска в другой хеш-таблице.
		//printf ("*) ");main_list.print();
		//printf ("Delete record: "); hash_list->head->data->data.print();
		// Это сшивается main_list в месте удаления hash_list->head->data.
		if( hash_list->head->data==main_list.head )
			main_list.head = main_list.head->next;
		if( hash_list->head->data->prev )
			hash_list->head->data->prev->next = hash_list->head->data->next;
		if( hash_list->head->data->next )
			hash_list->head->data->next->prev = hash_list->head->data->prev;
		
		// Удаление из ДРУГОЙ хеш-таблицы.
		tmp = hash_list->head->next;
		if( std::is_same<T_expr, char *>::value )
			del_table_links_list<int>(&ht_phone, phone, to_del_object);
		else if ( std::is_same<T_expr, int>::value )
			del_table_links_list<char *>(&ht_name, name, to_del_object);
		delete hash_list->head->data; hash_list->head->data = nullptr;
		delete hash_list->head;
		hash_list->head = tmp;
	}
	
	
	if( !hash_list->head ) return;
	list_node<list2_node<record> *> *curr = hash_list->head->next, *prev = hash_list->head;
	while( curr )
	{
		if( apply_command(comm, curr->data) )
		{
			command to_del_object;
			char * name = ((record *) (curr->data))->get_name();
			int phone = ((record *) (curr->data))->get_phone();
			int group = ((record *) (curr->data))->get_group();
			to_del_object.init_t (name, phone, group); // Шаблон элемента который удаляется из main_list, для поиска в другой хеш-таблице.
			
			// Сшивается main_list в месте удаления curr->data.
			if( curr->data==main_list.head )
				main_list.head = main_list.head->next;
			if( curr->data->prev )
				curr->data->prev->next = curr->data->next;
			if( curr->data->next )
				curr->data->next->prev = curr->data->prev;
			
			// Сшивание текущего списка, который лежит в хеш-таблице.
			prev->next = curr->next;
				
			// Удаление из ДРУГОЙ хеш-таблицы.
			tmp = curr->next;
			if( std::is_same<T_expr, char *>::value )
				del_table_links_list<int>(&ht_phone, phone, to_del_object);
			else if ( std::is_same<T_expr, int>::value )
				del_table_links_list<char *>(&ht_name, name, to_del_object);
			delete curr->data; curr->data = nullptr;
			delete curr;
			curr = tmp;			
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}


bool database::read_config(FILE *const in)
{
	char buf[MAX_LEN_CONF_STR];
	int k, is_k_read = 0;
	const char * pos = nullptr;
	while( fgets(buf, MAX_LEN_CONF_STR, in) )
	{
		if (*buf == '#') continue;
		pos = buf + strspn (buf, " \t\n");
		if (!is_k_read)
		{
			if( sscanf (pos, "%d", &k) != 1 || !ht_name.set_param(k))
				return false;
			else
				is_k_read = 1;
		}
		else
		{
			if (sscanf (pos, "%d", &k) != 1 || !ht_phone.set_param(k))
				return false;
			break;
		}
	}
	return true;
}

read_status database::read(FILE *const in)
{
	del();
	if( !ht_phone.alloc() || !ht_name.alloc() ) return read_status::memory;
	if( !(main_list.head = new list2_node<record>) ) return read_status::memory;
	read_status res;
	if( (res = main_list.head->data.read(in))!=read_status::success )
	{
		if( res==read_status::eof ) return read_status::empty_base;
		del();
		return res;
	}
	if( !ht_phone.add(main_list.head->data.get_phone(), main_list.head)
		|| !ht_name.add(main_list.head->data.get_name(), main_list.head) )
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
		if( !ht_phone.add(tmp->data.get_phone(), tmp)
			|| !ht_name.add(tmp->data.get_name(), tmp) )
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
		if(comm.op!=operation::lor)
		{
			if( comm.c_name==condition::eq )
			{
				if( !ht_name.select(comm.name.get(), comm, n_printed, out) )
				       return apply_status::memory;
				return apply_status::done;
			}
			if( comm.c_phone==condition::eq )
			{
				if( !ht_phone.select(comm.get_phone(), comm, n_printed, out) )
					return apply_status::memory;
				return apply_status::done;
			}
		}
		if (!main_list.select(comm, n_printed, out)) return apply_status::memory;
		return apply_status::done;
	case command_type::del:
		if( comm.op!=operation::lor )
		{
			if( comm.c_phone==condition::eq )
			{
				del_table_list<int>(&ht_phone, comm.get_phone(), comm);
				return apply_status::done;
			}
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
