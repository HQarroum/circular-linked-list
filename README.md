<br/>
<p align="center">
  <img src="./assets/icon.png" />
</p>
<br/>

# circular-linked-list
[![CI](https://github.com/HQarroum/circular-linked-list/actions/workflows/main.yml/badge.svg)](https://github.com/HQarroum/circular-linked-list/actions/workflows/main.yml)

> An implementation of a tiny circular doubly-linked list in C.

Current version: **1.0.1**

## Building and testing

This implementation builds as a dynamic and a static library by default. In order to trigger the build, simply call the Makefile at the root of the project using `make`.

This project is tested using the `Google Test` framework, the tests are located in the `tests/` directory and have their own Makefile which produce an executable. To launch the tests simply call the produced `launch_tests` executable.

## Creating an instance of a list

An instance of a list is of type `list_t`.

A list holds its current size which is represented as the sum of its nodes that are of type `node_t`. It also contains a pointer to the head of the list, and a pointer to the tail of the list.

### Creating a list dynamically

In order to create a new instance of a list on the heap, you must call `list_create`.

```C
list_t* list = list_create();
```

### Creating a list statically

If you feel you do not need a pointer to be returned and you'd like the list to be created statically, you can call `list_create_static` :

```C
list_t list = list_create_static();
```

> 💁 Do not forget to clear the list when you are finished using a static instance, typically using `list_clear` in order for all the nodes to be properly deleted.

## Inserting elements

Elements you can push into an instance of a `list_t` are of type `void*`.

There are two ways to insert an element into an instance of a list :

```C
// Pushing elements to head.
list_push_front(list, "foo");
list_push_front(list, "bar");

// Pushing elements to tail.
list_push_back(list, "baz");
list_push_back(list, "qux");
```

Both functions create an instance of a `node_t` which wraps the given element to insert in the list. Both functions return a pointer to the created node.

> ℹ️ The complexity of a node insertion is constant `O(1)`.

## Popping elements

You can *pop* an element located at the head or at the tail of the list. Popping an element will remove the inserted `node` and return a pointer to the value that was associated with that node.

```C
// Will return the constant string `qux`.
const char* qux = list_pop_back(list);
// Will return the constant string `bar`.
const char* bar = list_pop_front(list).
```

> ℹ️ The complexity of a node pop is constant `O(1)`.

## Iterating over the nodes

### Using a callback

It is possible to iterate over each nodes associated with a list by having a function called back on each node :

```C
int iterator(size_t index, node_t* node, void* data) {
  printf("Node (%zu) element : %s\n", index,
    (const char*) node->element);
  return (0);
}

list_iterate_over_nodes(list, iterator, NULL);
```

This method will allow you to iterate from the first element (the head of the list) to the last element (the tail of the list).

> ℹ️ If a negative value is returned from the iterator, the iteration will stop.

### Using an iterator

Another way of iterating over the list is by using the iterator APIs. The main difference with using a callback is that you are in full control of the iteration, you can stop it, but also go forward or backward.

To do so, first create a `list_iterator_t` and use it to traverse the list.

```C
list_iterator_t it = list_make_iterator(list, NULL);

for (size_t i = 0; i < list_get_size(list)
         && list_iterator_has_next(&it); ++i) {
  node_t* node = list_iterator_next(&it);
  // Do something with `node`.
}
```

> ℹ️ The second parameter of `list_make_iterator` is optional, it specifies a node pointer you'd like the iterator to start at. If NULL is specified, the iterator will start at the head of the list.

The iterator created by `list_make_iterator` will indefinitely iterate over the list (unless it is empty), since the list is circular. This is why we used a counter in the above example to stop the iteration at the end of the list.

Note that you are encouraged to write your own iterator functions that will implement the appropriate logic of how to iterate over an instance of a list given your application requirements.

> ℹ️ The complexity of an iteration over each node in the list is linear `O(n)`.

## Finding an element

### Basic node lookup

It is possible to search through the list for a particular node. You can use the `list_find_node` function to do so.

```C
node_t* node = list_push_front(list, "foo");

if (list_find_node(list, node)) {
  // `node` was found
}
```

### Conditional lookup

To customize the way to find an element in the list you can provide a predicate function to the `list_find_node_if` function :

```C
/**
 * Returns a positive value when the element
 * contained by the given node is `data`.
 */
int predicate(size_t index, node_t* node, void* data) {
  return (!strcmp(node->element, data));
}

if (list_find_node_if(list, predicate, "foo")) {
  // `foo` was found
}
```

> ℹ️ The complexity of both basic and customized lookups is linear `O(n)`.

## Removing a node

### Basic removal

To remove a given node from the list, you can pass a pointer to the node you'd like to be removed to the `list_remove_node` function :

```C
list_t* list = list_create();
node_t* node = list_push_front(list, "foo");

// Remove the node from the list.
list_remove_node(list, node);
```

### Conditional removal

It is possible to remove a node using a more functional way, by using a predicate passed to `list_remove_node_if`, here is an example of how you can use it :

```C
int predicate(size_t index, node_t* node, void* data) {
  return (!strcmp(node->element, "bar")
          || !strcmp(node->element, "foo"));
}

// This will remove from the list each node holding
// the constant strings 'foo' or 'bar'.
list_remove_node_if(list, predicate, NULL);
```

It is also possible to pass a third parameter to `list_remove_node_if`, for it to be passed to your predicate function.

```C
int predicate(size_t index, node_t* node, void* data) {
  return (!strcmp(node->element, data));
}

// This will remove from the list each node holding
// the constant string 'foo'.
list_remove_node_if(list, predicate, "foo");
```

> ℹ️ The complexity of a node removal is linear `O(n)`.

## Retrieving the size of a list instance

Retrieving the size of the list is a constant time operation `O(1)`, since the size is maintained across each insertions and removals. You can retrieve it as follow :

```C
size_t size = list_get_size(list);
```

Similarly, it is also possible to call `list_is_empty` if you'd like to know whether the given list is empty :

```C
int empty = list_is_empty(list)
```

## Clearing a list

To remove all the nodes contained in the list, you can call `list_clear` as follow :

```C
list_clear(list);
```

## Destroying an instance of a list

Similarly to creating a new instance of a list dynamically, to delete a dynamic instance of a list, you must call `list_destroy`. This will cause every node left in the list to be deleted, and the list itself to be destroyed.

```C
list_destroy(list);
```
