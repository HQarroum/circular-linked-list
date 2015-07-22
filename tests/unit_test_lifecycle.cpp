#include "../linked-list.h"
#include <gtest/gtest.h>

TEST(LINKED_LIST, CREATION) {
  list_t* list = list_create();
  
  EXPECT_TRUE(list != NULL);
  EXPECT_TRUE(list->size == 0);
  EXPECT_TRUE(list->head == NULL);
  EXPECT_TRUE(list->tail == NULL);
  list_destroy(list);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
