#ifndef RECORD_H
#define RECORD_H

#include <memory>
#include <cstdio>
#include <cstring>
#include "conditions.h"

class record
{
protected:
	std::unique_ptr<char[]> name = nullptr;
	int phone = 0;
	int group = 0;
public:
	record() = default;
	~record() = default;
	void set_phone (int p) {phone = p;}
	void set_group (int g) {group = g;}
	int set_name (const char * n)
	{
		if (n)
		{
			name = std::make_unique<char []> (strlen (n) + 1);
			if (!name) return -1;
			strcpy (name.get(), n);
		}
		else name = nullptr;
		return 0;
	}
	char *get_name() const { return name.get(); }
	int get_phone() const { return phone; }
	int get_group() const { return group; }

	bool init(const char *const new_name, const int new_p, const int new_group);
	// Allow as return value for functions
	record(record &&x) = default;// move constructor
	// Assignment move operator
	record &operator=(record &&x) = default;
	// Prohibit pass by value
	// (it is default when move constructor is declared)
	record &operator=(const record &x) = delete;

	bool operator==(const record &x) const
	{ return !strcmp(name.get(), x.name.get()) && phone==x.phone && group==x.group; }
	// Compare fields of 'x' and 'y' by order
	static long long int compare(const record &x, const record &y,
		const ordering order[], const int max_order);
	// Check condition 'x' for field 'name' of 'this' and 'y'
	bool compare_name(const condition c, const record &y) const;
	// Check condition 'c' for 'x' and 'y'
	static bool compare_int(const condition c, const int x, const int y);
	// Check condition 'c' for field 'phone' of 'this' and 'y'
	bool compare_phone(const condition c, const record &y) const
	{ return record::compare_int(c, phone, y.phone); }
	// Check condition 'c' for field 'group' of 'this' and 'y'
	bool compare_group(const condition c, const record &y) const
	{ return record::compare_int(c, group, y.group); }

	void print(const ordering order[] = nullptr, const int max_order = 3, FILE *const out = stdout) const;

	read_status read(FILE *const in = stdin);
};

#endif// RECORD_H
