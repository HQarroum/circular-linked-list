#include "linked-list.h"

list_t*	list_create()
{
  list_t*	list;
    
  list = malloc(sizeof(*list));
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return (list);
}

list_t list_create_static()
{
  return ((list_t) {
      .size = 0,
      .head = NULL,
      .tail = NULL
  });
}

void	list_iterate_over_nodes(list_t* list, list_predicate_t iterator)
{
  node_t* node = list->head;
  
  for (size_t i = 0; i < list->size; ++i) {
    if (iterator(i, node, NULL) < 0) {
      break;
    }
    node = node->next;
  }
}

node_t*	list_find_node_if(list_t* list, list_predicate_t iterator, void* data)
{
  node_t* node = list->head;
  
  for (size_t i = 0; i < list->size; ++i) {
    if (iterator(i, node, data)) {
      return (node);
    }
    node = node->next;
  }
  return (NULL);
}

size_t	list_get_size(list_t* list)
{
  return (list->size);
}

int	list_is_empty(list_t* list)
{
  return (list_get_size(list) == 0);
}

void	list_destroy(list_t* list)
{
  node_t* node = list->head;
  
  for (size_t i = 0; i < list->size; ++i) {
    node_t* current = node;
    node = node->next;
    free(current);
  }
  free(list);
}

node_t* node_new(void* element)
{
  node_t* node;
  
  node = malloc(sizeof(*node));
  node->element = element;
  node->next = NULL;
  node->prev = NULL;
  return (node);
}

node_t*	list_push_front(list_t* list, void* element)
{
  node_t* node = node_new(element);
  node_t* head = list->head;
  
  if (head) {
    // Binding the node to the list elements.
    node->next = head;
    node->prev = head->prev;
    // Binding the list elements to the node.
    head->prev->next = node;
    head->prev = node;
  } else {
    node->next = node;
    node->prev = node;
    list->tail = node;
  }
  list->head = node;
  list->size++;
  return (node);
}

node_t*	list_push_back(list_t* list, void* element)
{
  node_t* node = node_new(element);
  node_t* tail = list->tail;

  if (tail) {
    // Binding the node to the list elements.
    node->next = tail->next;
    node->prev = tail;
    // Binding the list elements to the node.
    tail->next->prev = node;
    tail->next = node;
  } else {
    node->next = node;
    node->prev = node;
    list->head = node;
  }
  list->tail = node;
  list->size++;
  return (node);
}

void* list_pop_node(list_t* list, node_t* node)
{
  void* element;
  
  if (!node) {
    return (NULL);
  }
  element = node->element;
  list_remove_node(list, node);
  return (element);
}

void* list_pop_back(list_t* list)
{
  return (list_pop_node(list, list->tail));
}

void* list_pop_front(list_t* list)
{
  return (list_pop_node(list, list->head));
}

list_iterator_t list_make_iterator(list_t* list, node_t* node)
{
  return ((list_iterator_t) {
      .current = (node != NULL ? node : list->head->prev),
      .list = list
  });
}

int list_iterator_has_next(list_iterator_t* it)
{
  return (it->current != NULL && it->current->next != NULL);
}

int list_iterator_has_prev(list_iterator_t* it)
{
  return (it->current != NULL && it->current->prev != NULL);
}

node_t* list_iterator_next(list_iterator_t* it)
{
  if (!list_iterator_has_next(it)) {
    return (NULL);
  }
  return (it->current = it->current->next);
}

node_t* list_iterator_prev(list_iterator_t* it)
{
  if (!list_iterator_has_prev(it)) {
    return (NULL);
  }
  return (it->current = it->current->prev);
}

node_t*	list_find_node(list_t* list, node_t* element)
{
  node_t* node = list->head;
  
  for (size_t i = 0; i < list->size; ++i) {
    if (node == element) {
      return (node);
    }
    node = node->next;
  }
  return (NULL);
}

/**
 * @brief Removes the given `node` from the `list`
 * and frees the memory allocated by the `node`.
 * @return a positive value if the given `node` has
 * been successfully removed from the `list`, a negative
 * value otherwise.
 */
int	list_remove_node(list_t* list, node_t* node)
{
  node_t* found = list_find_node(list, node);
  
  if (found != NULL) {
    found->prev->next = found->next;
    found->next->prev = found->prev;
    if (list->head == found) {
      list->head = found->next;
    }
    if (list->tail == found) {
      list->tail = found->prev;
    }
    list->size--;
    if (list->size == 0) {
      list->tail = NULL;
      list->head = NULL;
    }
    free(found);
    return (1);
  }
  return (0);
}

int	list_remove_node_if(list_t* list, list_predicate_t iterator, void* data)
{
  node_t* node = list->head;
  int removed  = 0;
  
  for (size_t i = 0; i < list->size; ++i) {
    node_t* next = node->next;
    
    if (iterator(i, node, data)) {
      list_remove_node(list, node);
      removed++;
      i -= 1;
    }
    node = next;
  }
  return (removed);
}
