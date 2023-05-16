#include "../linked-list.h"
#include <gtest/gtest.h>

namespace {

  TEST(CREATION, DYNAMIC) {
    list_t* list = list_create();
    
    ASSERT_TRUE(list != NULL);
    EXPECT_TRUE(list->size == 0);
    EXPECT_TRUE(list->head == NULL);
    EXPECT_TRUE(list->tail == NULL);
    list_destroy(list);
  }

  TEST(CREATION, STATIC) {
    list_t list = list_create_static();
    
    EXPECT_TRUE(list.size == 0);
    EXPECT_TRUE(list.head == NULL);
    EXPECT_TRUE(list.tail == NULL);
  }
}
