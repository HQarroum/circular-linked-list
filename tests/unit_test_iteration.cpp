#include "../linked-list.h"
#include <gtest/gtest.h>

static int node_iterator(size_t index, node_t* node, void* data)
{
  EXPECT_TRUE(node != NULL && data == NULL);
  EXPECT_EQ(index, *(int*)(node->element));
  return (0);
}

TEST(ITERATION, OVER_NODES) {
  list_t* list = list_create();
  int zero     = 0;
  int one      = 1;
  int two      = 2;

  list_push_back(list, &zero);
  list_push_back(list, &one);
  list_push_back(list, &two);

  list_iterate_over_nodes(list, node_iterator);
  list_destroy(list);
}

TEST(ITERATION, USING_AN_ITERATOR) {
  list_t* list = list_create();
  int zero     = 0;
  int one      = 1;
  int two      = 2;

  list_push_back(list, &zero);
  list_push_back(list, &one);
  list_push_back(list, &two);

  list_iterator_t it = list_make_iterator(list, NULL);

  for (size_t i = 0; i < list_get_size(list)
         && list_iterator_has_next(&it); ++i) {
    node_t* node = list_iterator_next(&it);

    EXPECT_EQ(i, *(int*)(node->element));
  }
  list_destroy(list);
}

TEST(ITERATION, USING_AN_ITERATOR_ON_AN_EMPTY_LIST) {
  list_t list        = list_create_static();
  list_iterator_t it = list_make_iterator(&list, NULL);
    
  while (list_iterator_has_next(&it)) {
    ASSERT_TRUE(0);
  }
}
