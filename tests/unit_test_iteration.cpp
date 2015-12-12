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

  list_iterate_over_nodes(list, node_iterator, NULL);
  list_destroy(list);
}

TEST(ITERATION, USING_AN_ITERATOR) {
  list_t* list     = list_create();
  size_t iteration = 0;
  int zero         = 0;
  int one          = 1;
  int two          = 2;

  list_push_back(list, &zero);
  list_push_back(list, &one);
  list_push_back(list, &two);

  list_iterator_t it = list_make_iterator(list, NULL);

  for (size_t s = list_get_size(list); iteration < s
         && list_iterator_has_next(&it); ++iteration) {
    node_t* node = list_iterator_next(&it);
    EXPECT_EQ(iteration, *(int*)(node->element));
  }
  EXPECT_EQ(iteration, 3);
  list_destroy(list);
}

TEST(ITERATION, USING_AN_ITERATOR_ON_AN_EMPTY_LIST) {
  list_t list        = list_create_static();
  list_iterator_t it = list_make_iterator(&list, NULL);
    
  while (list_iterator_has_next(&it)) {
    ASSERT_TRUE(0);
  }
}

TEST(ITERATION, WHILE_REMOVING_NODES) {
  list_t list        = list_create_static();
  size_t iteration   = 0;
  int zero           = 0;
  int one            = 1;
  int two            = 2;

  list_push_back(&list, &zero);
  list_push_back(&list, &one);
  list_push_back(&list, &two);

  list_iterator_t it = list_make_iterator(&list, NULL);

  for (size_t s = list_get_size(&list); iteration < s
	 && list_iterator_has_next(&it); ++iteration) {
    list_iterator_next(&it);
    EXPECT_EQ(list_iterator_remove(&it), 1);
  }
  EXPECT_EQ(iteration, 3);
  EXPECT_EQ(list_get_size(&list), 0);
}
