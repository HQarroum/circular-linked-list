#include "../linked-list.h"
#include <gtest/gtest.h>

static int removal_predicate(size_t index, node_t* node, void* data)
{
  index = index;
  node = node;
  data = data;
  // Remove everything.
  return (1);
}

TEST(REMOVAL, USING_A_NODE_POINTER) {
  list_t* list = list_create();

  node_t* foo = list_push_front(list, (void*) "foo");
  node_t* bar = list_push_front(list, (void*) "bar");
  
  EXPECT_EQ(list_remove_node(list, foo), 1);
  EXPECT_EQ(list_remove_node(list, bar), 1);
  EXPECT_TRUE(list_is_empty(list));
  list_destroy(list);
}

TEST(REMOVAL, USING_A_PREDICATE) {
  list_t* list = list_create();
  size_t  size;
  
  list_push_back(list, (void*) "foo");
  list_push_back(list, (void*) "bar");
  size = list_get_size(list);
  
  EXPECT_EQ(list_remove_node_if(list, removal_predicate, NULL), size);
  EXPECT_TRUE(list_is_empty(list));
  list_destroy(list);
}

TEST(REMOVAL, OF_EVERY_NODE) {
  // Using a dynamically created list.
  list_t* list = list_create();
  
  list_push_back(list, (void*) "foo");
  list_push_back(list, (void*) "bar");
  list_clear(list);
  EXPECT_TRUE(list_is_empty(list));
  list_destroy(list);
  
  // Using a statically created list.
  list_t static_list = list_create_static();
  
  list_push_back(&static_list, (void*) "foo");
  list_push_back(&static_list, (void*) "bar");
  list_clear(&static_list);
  EXPECT_TRUE(list_is_empty(&static_list));
}
