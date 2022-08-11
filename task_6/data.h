#ifndef DATABASE_H
#define DATABASE_H

#include <cstdio>
#include "record.h"
#include "conditions.h"
#include "list2.h"
#include "hash.h"

class database
{
private:
	list2<record> main_list;
	hash_table<char *> ht_name;

	bool add(record &x)
	{
		if( ht_name.find(x.get_name(), x) ) return true;
		char *name = x.get_name();

		if( !main_list.add_head(x) ) return false;
		if( !ht_name.add(name, main_list.head) )
		{
			main_list.del_head();
			return false;
		}
		return true;
	}
	void del()
	{
		main_list.del();
		ht_name.del();
	}
	void del_list_table(const command &comm);
	template <class T_expr>
	void del_table_list(const hash_table<T_expr> *ht, const T_expr expr, const command &comm);

public:
	database() = default;
	~database() = default;
	bool read_config(FILE *const in);
	read_status read(FILE *const in);
	apply_status apply(command &comm, int &n_printed, FILE *const out = stdout);
};

#endif// DATABASE_H
