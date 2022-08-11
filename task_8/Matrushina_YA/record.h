# ifndef record_H
# define record_H
# include <memory>
# include <stdio.h>
# include "condition.h"
# include "ordering.h"

enum class read_status
{
  success = 0,
  eof = -1,
  format = -2,
  memory = -3,
  open = -4,
  read = -5,
};


class record
{
 private:
   std::unique_ptr<char []> name = nullptr;
   int phone = 0;
   int group = 0;
public:
   record () = default;
   ~record () = default;
   char * get_name () const { return name.get (); }
   int get_phone () const { return phone; }
   int get_group () const { return group; }
   read_status init (const char *, int p, int g);
   read_status init_name(const char *n);
   read_status init_phone (int p);
   read_status init_group (int g);
// Allow as return value for functions
   record (record &&x) = default; // move constructor
// Assignement move operator
   record& operator= (record&& x)
   {
     if (this == &x)
	  return *this;
    name = std::move(x.name);
	phone = x.phone;
	group = x.group;
	return *this;
   };
   int com(record& y);
// Prohoibit pass by value
// (it is default when move constructor is declared)
   record (const record &x) = delete;
// Prohoibit assignement operator
// (it is default when move constructor is declared)
   record& operator= (const record&) = delete;
// Check condition ’x’ for field ’name’ for ’this’ and ’y’
   bool compare_name (condition x,record& y);
// Check condition ’x’ for field ’phone’ for ’this’ and ’y’
   bool compare_phone (condition x,record& y);
// Check condition ’x’ for field ’group’ for ’this’ and ’y’ 
   bool compare_group (condition x,record& y);
   bool compare(record& y);
   int compare_(record &y);
   int _compare(record& y);
   void print (const ordering order[] = nullptr,FILE * fp = stdout);
   void Print ();
   read_status read (FILE *fp = stdin);
   int hash_value(int k);
};
int strcmp_spec_sym (char* str_2,char* str_1, int* i, int* j);
int strcmp_name(char* str_1, char* str_2);
# endif