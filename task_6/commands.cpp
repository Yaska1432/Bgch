#include <cstring>
#include "commands.h"

static const int LEN = 1234;

bool print_condition(condition x, FILE *out = stdout);
void print_order(const ordering order[], const int max_order, FILE *out = stdout);
command_type parse_type(char **&words, int &n_words);

static condition get_condition (const char * str)
{
	condition c = condition::none;
	if (!strcmp (str, "="))
		c = condition::eq;
	else if (!strcmp (str, "<>")) 
		c = condition::ne;
	else if (!strcmp (str, "<"))
		c = condition::lt;
	else if (!strcmp (str, ">"))
		c = condition::gt;
	else if (!strcmp (str, "<="))
		c = condition::le;
	else if (!strcmp (str, ">="))
		c = condition::ge;
	else if (!strcmp (str, "like"))
		c = condition::like;
	else if (!strcmp (str, "not like"))
		c = condition::nlike;
	return c;
}

bool command::read_command (const char *& str)
{
	const char commands[][50] = {"select", "insert", "delete", "quit", ""};
	command_type field_name_ [] = {command_type::select, command_type::insert, command_type::del, command_type::quit, command_type::none,};

	str += strspn (str, " ,\t\n");
	for (int i = 0; commands[i]; i++)
	{
		if (str == strstr (str, commands[i]))
		{
			type = field_name_[i];
			str += strlen (commands[i]);
			return true;
		}
	}
	type = command_type::none;
	return false;
}

bool command::parse(char *str)
{
	const char * str_pos = str;
	reset();
if (!read_command (str_pos))
		return false;
	switch (type)
	{
		case command_type::none:
			return false;
		case command_type::select:
			if (!read_ordering (str_pos))
				return false;
			{	
				const char * where_pos = strstr (str_pos, "where");
				const char * prev_pos;
				if (where_pos != nullptr)
					str_pos = where_pos + strlen ("where");
				prev_pos = str_pos;
				if (!read_condition (str_pos))
					str_pos = prev_pos;
			}
			{	
				const char * order_by_pos = strstr (str_pos, "order by");
				const char * prev_pos;
				prev_pos = str_pos;
				str_pos = order_by_pos != nullptr? order_by_pos + strlen ("order by"): str_pos;
				if (!read_sort_ordering (str_pos))
				{
					for (int i = 0; i < 3; i++)
						order_by[i] = ordering::none;
					str_pos = prev_pos;
				}
			}
			return true;
		case command_type::insert:
			str = strstr (str, "(");
			if (str == nullptr)
				return false;
			str += strlen ("(");
			{
				int length, phone, group;
				const int LEN = 1234;
				char buf[LEN] = {'\0'}, buf2[LEN] = {'\0'};
				str += strspn (str, " ,\t\n");
				length = strcspn (str, " ,\t\n");
				strncpy (buf, str, length);
				buf[length] = '\0';
				str += length;
				str += strspn (str, " ,\t\n");
				
				length = strcspn (str, " ,\t\n");
				strncpy (buf2, str, length);
				buf2[length] = '\0';
				if (sscanf (buf2, "%d", &phone) != 1)
					return false;
				str += length;
				str += strspn (str, " ,\t\n");
				length = strcspn (str, " ,\t\n");
				strncpy (buf2, str, length);
				buf2[length] = '\0';
				if (sscanf (buf2, "%d", &group) != 1)
					return false;
				str = strstr (str, ")");
				if (str == nullptr)
					return false;
				
				init (buf, phone, group);
				return true;
			}
		case command_type::del:
			{	
				const char * where_pos = strstr (str_pos, "where");
				const char * prev_pos;
				if (where_pos != nullptr)
					str_pos = where_pos + strlen ("where");
				prev_pos = str_pos;
				if (!read_condition (str_pos))
					str_pos = prev_pos;
			}
			return true;
		case command_type::quit:
			return true;
	}
	return true;
}
bool command::read_sort_ordering (const char *& str)
{
	const char field_name[][1234] = {"phone", "name", "group"};
	ordering field_name_[] = {ordering::phone, ordering::name, ordering::group};
	str += strspn (str, " \t\n");
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (str == strstr (str, field_name[k]))
			{
				order_by[i] = field_name_[k];
				str += strlen (field_name[k]);
				str += strspn (str, ", \t\n");
				break;
			}
			else order_by[i] = ordering::none;
		}
	}
	return true;
}

static int high (const char * str, char * field_name, char * op_name, char * ex_name)
{
	const int LEN_ = 50;
	int count = 0, i, len;
	const char sp_words[][LEN_] = {"not like", "like", "<>", ">=", "<=", ">", "<", "=", "" };
	str += strspn (str, " \t\n");
	len = strcspn (str, " \t\n=<>");
	strncpy (field_name, str, len);
	field_name[len] = '\0';
	count++;
	str += len;
	str += strspn (str, " \t\n");
	for (i = 0; sp_words[i][0]; i++)
	{
		if (str == strstr (str, sp_words[i]))
		{
			strcpy (op_name, sp_words[i]);
			count++;
			break;
		}
	}
	if (!sp_words[i][0]) return count;
	str += strlen (op_name);
	str += strspn (str, " \t\n");
	len = strcspn (str, " \t\n");
	strncpy (ex_name, str, len);
	ex_name[len] = '\0';
	count++;
	return count;
}

bool command::read_condition (const char *& str)
{
	const char * pos = str;
	char * name = nullptr;
	int phone = -1, group = -1, fl = 1;
	char field_name[LEN], operator_name[LEN], ex_name[LEN], op_name[LEN];
	if (high (pos, field_name, operator_name, ex_name) != 3) return false;
	pos += strspn (str, " \t\n");
	pos += strlen (field_name);
	pos += strspn (pos, " \t\n");
	pos += strlen (operator_name);
	pos += strspn (pos, " \t\n");
	pos += strlen (ex_name);
	pos += strspn (pos, " \t\n");
	if (sscanf (pos, "%s", op_name) == 1)
	{
		if (!strcmp (op_name, "and")) this->op = operation::land;
		else if (!strcmp (op_name, "or")) this->op = operation::lor;
		else fl = 0;
		if (fl)
		{
			pos += strlen (op_name);
			pos += strspn (pos, " \t\n");
			if (!read_condition (pos)) return false;
		}
	}
	if (!strcmp (field_name, "phone"))
	{
		this->c_phone = get_condition (operator_name);
		if (sscanf (ex_name, "%d", &phone) != 1) return false;
		set_phone (phone);
	} 
	else if (!strcmp (field_name, "group"))
	{
		this->c_group = get_condition (operator_name);
		if (sscanf (ex_name, "%d", &group) != 1) return false;
		set_group (group);
	}
	else if (!strcmp (field_name, "name"))
	{
		this->c_name = get_condition (operator_name);
		name = ex_name;
		set_name (name);
	}
	return true;
}

bool command::read_ordering (const char *& str)
{
	const char field_name[][LEN] = {"phone", "name", "group"};
	ordering field_name_ [] = {ordering::phone,ordering::name,ordering::group};
	str += strspn (str, " \t\n");
	if (*str == '*')
	{
		for (int i = 0; i < 3; i++) order[i] = default_order[i];
		return true;
	}
	else
	{
		for (int i = 0; i < 3; i++) order[i] = ordering::none;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (str == strstr (str, field_name[k]))
			{
				order[i] = field_name_ [k];
				str += strlen (field_name[k]);
				str += strspn (str, ", \t\n");
				break;
			}
		}
	}
	return true;
}


void command::print(FILE *out) const
{
	fprintf(out, "type\t");
	switch( type )
	{
		case command_type::none:
			fprintf(out, "not specified\n");
			break;
		case command_type::quit:
			fprintf(out, "quit\n");
			break;
		case command_type::insert:
			fprintf(out, "insert\n");
			break;
		case command_type::select:
			fprintf(out, "select\n");
			break;
		case command_type::del:
			fprintf(out, "delete\n");
	}

	fprintf(out, "name\t");
	if( print_condition(c_name, out) )
		fprintf(out, " %s", name.get());
	fprintf(out, "\n");

	fprintf(out, "phone\t");
	if( print_condition(c_phone, out) )
		fprintf(out, " %d", phone);
	fprintf(out, "\n");

	fprintf(out, "group\t");
	if( print_condition(c_group, out) )
		fprintf(out, " %d", group);
	fprintf(out, "\n");

	fprintf(out, "operation\t");
	switch( op )
	{
	case operation::none:
		fprintf(out, "not specified\n");
		break;
	case operation::land:
		fprintf(out, "and\n");
		break;
	case operation::lor:
		fprintf(out, "or\n");
	}

	fprintf(out, "order ");
	print_order(order, max_order, out);
	fprintf(out, "order by ");
	print_order(order_by, max_order, out);
}

bool print_condition(condition x, FILE *out)
{
	switch( x )
	{
	case condition::none:
		fprintf(out, "not specified");
		return false;
	case condition::eq:
		fprintf(out, "=");
		return true;
	case condition::ne:
		fprintf(out, "<>");
		return true;
	case condition::lt:
		fprintf(out, "<");
		return true;
	case condition::gt:
		fprintf(out, ">");
		return true;
	case condition::le:
		fprintf(out, "<=");
		return true;
	case condition::ge:
		fprintf(out, ">=");
		return true;
	case condition::like:
		fprintf(out, "like");
		return true;
	case condition::nlike:
		fprintf(out, "not like");
		return true;
	}
	return false;
}

void print_order(const ordering order[], const int max_order, FILE *out)
{
	fprintf(out, "{");
	for( int i = 0; i<(max_order - 1); i++ )
	{
		switch( order[i] )
		{
		case ordering::none:
			fprintf(out, "not specified, ");
			break;
		case ordering::name:
			fprintf(out, "name, ");
			break;
		case ordering::phone:
			fprintf(out, "phone, ");
			break;
		case ordering::group:
			fprintf(out, "group, ");
		}
	}
	switch( order[max_order - 1] )
	{
	case ordering::none:
		fprintf(out, "not specified");
		break;
	case ordering::name:
		fprintf(out, "name");
		break;
	case ordering::phone:
		fprintf(out, "phone");
		break;
	case ordering::group:
		fprintf(out, "group");
	}
	fprintf(out, "}\n");
}

bool command::apply(const record &x) const
{
	switch( type )
	{
	case command_type::none:
		return true;
	case command_type::quit:
		return true;
	case command_type::insert:
		return true;
	case command_type::select:
		[[fallthrough]];
	case command_type::del:
		break;
	}

	switch( op )
	{
		case operation::none:
			[[fallthrough]];
		case operation::land:
			if( c_name!=condition::none && !x.compare_name(c_name, *this) )
				return false;
			if( c_phone!=condition::none && !x.compare_phone(c_phone, *this) )
				return false;
			if( c_group!=condition::none && !x.compare_group(c_group, *this) )
				return false;
			return true;
		case operation::lor:
			if( c_name!=condition::none && x.compare_name(c_name, *this) )
				return true;
			if( c_phone!=condition::none && x.compare_phone(c_phone, *this) )
				return true;
			if( c_group!=condition::none && x.compare_group(c_group, *this) )
				return true;
			return false;
	}
	return false;
}
