#ifndef PRINT_RECORD_H
#define PRINT_RECORD_H

#include <cstdio>
#include "record.h"
#include "conditions.h"
#include "list2_node.h"

inline void print_record(const record &x, const ordering order[] = nullptr, const int max_order = 3, FILE *const out = stdout)
	{ x.print(order, max_order, out); }
inline void print_record(const list2_node<record> *const x, const ordering order[] = nullptr, const int max_order = 3, FILE *const out = stdout)
	{ x->data.print(order, max_order, out); }

inline record *get_address_record (list2_node<record> *const x)
	{ return &x->data; }
inline record *get_address_record (list_node<list2_node<record> *> *const x)
	{ return &x->data->data; }
	
inline bool apply_command(const command &comm, const record &x)
	{ return comm.apply(x); }
inline bool apply_command(const command &comm, const list2_node<record> *const x)
	{ return comm.apply(x->data); }

#endif
