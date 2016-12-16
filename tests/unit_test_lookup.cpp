#include "../linked-list.h"
#include <gtest/gtest.h>

static int node_predicate(size_t i, node_t* node, void* data)
{
  (void) i;
  return (*(int*)(node->element) == *(int*)(data));
}

TEST(LOOKUP, USING_A_NODE_POINTER) {
  list_t* list = list_create();
  int zero     = 0;
  int one      = 1;

  node_t* foo = list_push_back(list, &zero);
  node_t* bar = list_push_back(list, &one);

  EXPECT_EQ(list_find_node(list, foo), foo);
  EXPECT_EQ(list_find_node(list, bar), bar);
  list_destroy(list);
}

TEST(LOOKUP, USING_A_PREDICATE) {
  list_t* list = list_create();
  int zero     = 0;
  int one      = 1;

  node_t* foo = list_push_back(list, &zero);
  node_t* bar = list_push_back(list, &one);

  EXPECT_EQ(list_find_node_if(list, node_predicate, &zero), foo);
  EXPECT_EQ(list_find_node_if(list, node_predicate, &one), bar);
  list_destroy(list);
}
