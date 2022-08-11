#ifndef LIST2_H
#define LIST2_H
#define LEN 256
//#include "list.h"
#include "ordering.h"
#include "command.h"
#include "list_node2.h"
class list2
{
  private:
      list_node2 *head = nullptr;
	  list_node2 *curr = nullptr;
  public:
      list2()=default;
	  list_node2* get_head()
	     {return head;}
	  void set_head(list_node2 *x)
	     {head = x;}
	  ~list2();
	  void delete_list2();
	  int get_length();
	  bool init (list_node* a);
	  bool CompareList_node2(list_node2& node1, list_node2& node2, ordering order[], int max);
	  void merger_sort (list_node2 *& A, list_node2 *& B, list_node2 *& C, list_node2 **prev_C,int n, int m, int max, ordering order[]);
	  void mergeSort(command &y);
	  void print(ordering order[], FILE* fp = stdout);
};

#endif //LIST_H