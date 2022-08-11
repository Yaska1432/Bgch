#ifndef COMMAND_H
#define COMMAND_H

#include <cstdio>
#include "record.h"
#include "conditions.h"

template <class T> class list2;
template <class T> class list2_node;
template <class T> class list;
template <class T> class list_node;

class command: public record
{
	private:
		static constexpr char separ[3] = {'\t', '\n', ' '};
		static const int n_separ = 3;
		static const int max_order = 3;
		command_type type = command_type::none;
		condition c_name = condition::none;
		condition c_phone = condition::none;
		condition c_group = condition::none;
		operation op = operation::none;
		ordering order[max_order] = {ordering::none, ordering::none, ordering::none};
		ordering order_by[max_order] = {ordering::none, ordering::none, ordering::none};
		ordering default_order[3] = { ordering::name, ordering::phone, ordering::group };

		void reset()
		{
			name = nullptr;
			phone = group = 0;
			type = command_type::none;
			c_name = c_phone = c_group = condition::none;
			op = operation::none;
			for( int i = 0; i<max_order; i++ )
				order[i] = order_by[i] = ordering::none;
		}
		friend class list2<record>;
		friend class list2<list2_node<record> *>;
		friend class list<record>;
		friend class list<list2_node<record> *>;
		friend class database;
public:
	command_type get_type () { return type; }
	bool read_ordering (const char *& str);
	bool read_condition (const char *& str);
	bool read_sort_ordering (const char *& str);
	bool read_command (const char *& str);
	bool parse(char *str);
	command() = default;
	~command() = default;
	void print(FILE *out = stdout) const;
	bool apply(const record &x) const;
};

#endif// COMMAND_H
