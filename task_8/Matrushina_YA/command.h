# ifndef command_H
# define command_H
# include <stdio.h>
# include "record.h"
# include "condition.h"
# include "list_node.h"
# include "ordering.h"
# include "operation.h"
# include "command_type.h"

class command : public record
{
	private:
		static const int max_items = 3;
		command_type type = command_type::none;
		condition c_name = condition::none;
		condition c_phone = condition::none;
		condition c_group = condition::none;
		field f_field = field::none;
		operation op = operation::none;
	public:
		ordering order[max_items] = {ordering::none, ordering::none, ordering::none};
		ordering order_by[max_items] = {ordering::none, ordering::none, ordering::none};
		command () = default;
		~command () = default;
		command_type get_type()
		{ return type;}
		condition get_c_name()
		{return c_name;}
		condition get_c_phone()
		{return c_phone;}
		condition get_c_group()
		{return c_group;}
		operation get_op()
		{return op;}
		bool parseInsert(char *string);
		bool PARSE (char *string);
		bool parseSelect(char *string);
		bool parseDelete(char *string);
		bool parseConditionOutputFields(char *string);
		bool parseSearch(char *string, int *i);
		bool parseConditionSorting(char *string);
		// Print parsed structure
		void print (FILE *fp = stdout);
		// Apply command, return comparision result for record ’x’
		//int APLY (list_node<T>* head, FILE *fp = stdout);
		bool apply (record& x);
};

field strncmp_field(char* buf);
condition strcmp_condition(char* s, field f_field, int *i);
int getNumberByString(char* buf);
char* cutOutWord(char *string, int *i, char *b);
char* cutOutWordInsert(char *string, int *i, char *b);
# endif