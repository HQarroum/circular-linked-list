#include "../linked-list.h"
#include <gtest/gtest.h>

TEST(POP, IN_HEAD_AND_TAIL) {
  list_t* list = list_create();

  list_push_back(list, (void*) "foo");
  list_push_back(list, (void*) "bar");
  list_push_back(list, (void*) "baz");

  EXPECT_STREQ((const char*) list_pop_front(list), "foo");
  EXPECT_STREQ((const char*) list_pop_back(list), "baz");
  EXPECT_STREQ((const char*) list_pop_front(list), "bar");
  EXPECT_EQ(list_get_size(list), 0);
  list_destroy(list);
}
