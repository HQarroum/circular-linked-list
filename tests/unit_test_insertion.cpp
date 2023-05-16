#include "../linked-list.h"
#include <gtest/gtest.h>

namespace {

  TEST(INSERTION, IN_HEAD) {
    list_t* list = list_create();

    // Inserting elements in head.
    node_t* foo = list_push_front(list, (void*) "foo");
    node_t* bar = list_push_front(list, (void*) "bar");

    EXPECT_EQ(list_get_size(list), 2);
    EXPECT_STREQ((const char*) foo->element, "foo");
    EXPECT_STREQ((const char*) bar->element, "bar");
    EXPECT_EQ(list->head, bar);
    EXPECT_EQ(list->tail, foo);
    list_destroy(list);
  }

  TEST(INSERTION, IN_TAIL) {
    list_t* list = list_create();

    // Inserting elements in tail.
    node_t* foo = list_push_back(list, (void*) "foo");
    node_t* bar = list_push_back(list, (void*) "bar");

    EXPECT_EQ(list_get_size(list), 2);
    EXPECT_STREQ((const char*) foo->element, "foo");
    EXPECT_STREQ((const char*) bar->element, "bar");
    EXPECT_EQ(list->head, foo);
    EXPECT_EQ(list->tail, bar);
    list_destroy(list);
  }

  TEST(INSERTION, MIXING_TAIL_AND_HEAD) {
    list_t* list = list_create();
    char* baz    = strdup("baz");
    char* foo    = strdup("foo");

    // Inserting 1000 elements in head.
    for (size_t i = 0; i < 1000; ++i) {
      list_push_front(list, baz);
    }

    // Inserting 1000 elements in tail.
    for (size_t i = 0; i < 1000; ++i) {
      list_push_back(list, foo);
    }

    EXPECT_EQ(list_get_size(list), (1000 * 2));
    EXPECT_STREQ((const char*) list->head->element, baz);
    EXPECT_STREQ((const char*) list->tail->element, foo);
    free(baz);
    free(foo);
    list_destroy(list);
  }
}
