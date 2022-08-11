# ifndef command_type_H
# define command_type_H
enum class command_type
{
	none,
	quit,
	insert, // add record
	select, // find by conditions specified
	del,
};
# endif