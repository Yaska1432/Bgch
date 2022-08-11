#ifndef CONTAINER_H
#define CONTAINER_H
# include "list_node.h"
# include "hash_.h"
# include "hash_list.h"
# include "hash.h"

class container
{
 public:
   b_tree<b_tree_list> TREE;
   hash<list_node> HASH;
   container()=default;
   ~container()=default;

};
#endif