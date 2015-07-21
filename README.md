![Logo](http://dory.fr/images/jouets/train2.png)

# Circular linked list

This is an implementation of a tiny circular linked list in C.

Current version: **0.1.0**

Lead Maintainer: [Halim Qarroum](mailto:hqm.post@gmail.com)

## Creating an instance of a list

An instance of a list is of type `list_t`.

A list holds its current size which is represented by the sum of its nodes that are of type `node_t`. It also contains a pointer to the head of the list, and a pointer to the tail of the list.

In order to create a new instance of a list, you must call `list_create`.

```C
list_t* list = list_create();
```

## Inserting elements

Elements you can push into an instance of a `list_t` are of type `void*`.

There are two main ways to insert an element into an instance of a list :

```C
// Pushing elements in head.
list_push_front(list, "foo");
list_push_front(list, "bar");

// Pushing elements in tail.
list_push_back(list, "baz");
list_push_back(list, "qux");
```

Both functions create an instance of a `node_t` which wraps the given element to insert in the list. As such, the two insertion functions return a pointer to the created node.

The complexity of a node insertion is constant `O(1)`.

## Iterating over the nodes

It is possible to iterate over each nodes associated with a given list as follow :

```C
int iterator(size_t index, node_t* node, void* data)
{
  printf("Node (%zu) element : %s\n",
    index,
    (const char*) node->element);
  return (0);
}

// Iterates over each node in the list.
list_iterate_over_nodes(list, iterator);
```
> Note : If a negative value is returned from the iterator, the iteration will be stopped.

The complexity of an iteration over each node in the list is linear `O(n)`.

## Finding an element

### Basic node lookup

It is possible to search through the list for a particular node. You can use the `list_find_node` function to do so :

```C
node_t* node = list_push_front(list, "foo");

if (list_find_node(list, node)) {
  puts("Node found !");
}
```

### Conditional lookup

To customize the way to find an element in the list you can provide a predicate function to the `list_find_element_by_predicate` function :

```C
/**
 * Returns a positive value when the element
 * contained by the given node is 'foo'.
 */
int predicate(size_t index, node_t* node)
{
  return (!strcmp(node->element, "foo"));
}

// Triggering a lookup by predicate.
if (list_find_element_by_predicate(list, &predicate)) {
  puts("I found foo !");
}
```

The complexity of both basic and customized lookups is linear `O(n)`.

## Removing a node

### Basic removal

To remove a given node from the list, you can pass a pointer to the node you'd like to be removed to the `list_remove_node` function :

```C
list_t* list = list_create();
node_t* node = list_push_front(list, "foo");

// After this call, the list will be empty.
list_remove_node(list, node);
```

### Conditional removal

It is possible to remove a node using a more functional way, by using a predicate passed to `list_remove_node_if`, here is an example of how you can use it :

```C
int predicate(size_t index, node_t* node, void* data)
{
  return (!strcmp(node->element, "bar")
          || !strcmp(node->element, "foo"));
}

// This will remove from the list each node holding
// the constant strings 'foo' or 'bar'.
list_remove_node_if(list, predicate, NULL);
```

It is also possible to pass a third parameter to `list_remove_node_id`, for it to be passed to your predicate function. This is espacially handy when removing values you do not known compile-time from the list :

```C
int predicate(size_t index, node_t* node, void* data)
{
  return (!strcmp(node->element, data));
}

// This will remove from the list each node holding
// the constant string 'foo'.
list_remove_node_if(list, predicate, "foo");
```

The complexity of a node removal is linear `O(n)`.

## Retrieving the size of a list instance

Retrieving the size of the list is a constant time operation `O(1)`, since the size is maintained across each insertions and removals. You can retrieve it as follow :

```C
size_t size = list_get_size(list);
```

Similarly, it is also possible to call `list_is_empty` if you'd like to know whether the given list is empty :

```C
int empty = list_is_empty(list)
```

## Destroying an instance of a list

Similarly to creating a new instance of a list, to delete an instance of a list, you must call `list_destroy`. This will cause every node left in the list to be deleted, and the list itself to be destroyed. You will not be able to use the pointer to the list after a call to `list_destroy`.

Example :

```C
list_destroy(list);
```
