#ifndef DATABASE_H
#define DATABASE_H

#include <cstdio>
#include "record.h"
#include "conditions.h"
#include "list2.h"
#include "hash.h"
#include "container.h"

class database
{
private:
	list2<record> main_list;
	hash_table<int> ht_phone;
	hash_table<char *> ht_name;

	bool add(record &x)
	{
		if( ht_name.find(x.get_name(), x) ) return true;
		char *name = x.get_name();
		int phone = x.get_phone();
		if( !main_list.add_head(x) ) return false;
		if( !ht_name.add(name, main_list.head) )
		{
			main_list.del_head();
			return false;
		}
		if( !ht_phone.add(phone, main_list.head) )
		{
			ht_name.del(x.get_name(), main_list.head);
			main_list.del_head();
			return false;
		}
		//if( ht_phone.find(x.get_phone(), x) ) return true;
		//if( !main_list.add_head(x) ) return false;
		return true;
	}
	void del()
	{
		main_list.del();
		ht_phone.del();
		ht_name.del();
	}
	void del_list_table(const command &comm);
	template <class T_expr>
	void del_table_list(const hash_table<T_expr> *ht, const T_expr expr, const command &comm);
	template <class T_expr>
	void del_table_links_list(const hash_table<T_expr> *ht, const T_expr expr, const command &comm);
public:
	container* CONTAINERS = nullptr;
 public:
   int m_hash = 0,k_hash = 0,m_tree = 0;
   database()=default;
   ~database()
   {
		if (CONTAINERS){
			delete[]CONTAINERS;
			CONTAINERS = nullptr;
			}
   }
	bool read_config(FILE *const in);
	read_status read(FILE *const in);
	apply_status apply(command &comm, int &n_printed, FILE *const out = stdout);
};

#endif// DATABASE_H
