# ifndef condition_H
# define condition_H
enum class condition
{
	none, // not specified
	eq,
	// equal
	ne,
	// not equal
	lt,
	// less than
	gt,
	// great than
	le,
	// less equal
	ge,
	// great equal
	like, // strings only: match pattern
	// strings only: not match pattern	
	nlike,
};

enum class field
{
none, // not specified
name,
phone,
group,
};
# endif
