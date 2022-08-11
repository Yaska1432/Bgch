#ifndef DATABASE_H
#define DATABASE_H
#include "record.h"
# include "command.h"
# include "ordering.h"
# include "list.h"
# include "list_node.h"
# include "hash_list_.h"
# include "list2.h"
# include "list_node2.h"
# include "hash.h"
# include "container.h"

class database: public record
{
 private:
   list LIST;
   b_tree<b_tree_list> TREE;
   hash<list_node> HASH;
   container* CONTAINERS = nullptr;
 public:
   int m_hash = 0,k_hash = 0,m_tree = 0;
   database()=default;
   ~database()
   {
		if (CONTAINERS){
			delete[]CONTAINERS;
			CONTAINERS = nullptr;
			}
   }
   
   bool Insert_LIST_TREE(record &y);
   bool readConfig (char *fileway);
   char *LookingForFileConfig (char *fileway);
   char* cutOutWord(char *string, int *i, char *b, int *fl);
   bool parseConfig (char *buf, int *k);
   int getNumberByString(char* buf);
   read_status read(const char *filename);
   bool Insert_LIST_TREE(list_node *rec);
   int APLY (command &y,FILE *fp = stdout);
   int Insert(command &y, FILE *fp);
   int Select(command &y, FILE *fp );
   int Delete(command &y, FILE *fp);
   void deleteListTreeNode(command &y);
   int SearchAndOutputRecord(command &y,FILE *fp);
   int SearchSortAndOutputRecord(list2 *LIST2, command &y);

};
#endif