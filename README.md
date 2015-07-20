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
list_add_element_in_head(list, "foo");
list_add_element_in_head(list, "bar");

// Pushing elements in tail.
list_add_element_in_tail(list, "baz");
list_add_element_in_tail(list, "qux");
```

Both functions create an instance of a `node_t` which wraps the given element to insert in the list. As such, the two insertion functions return a pointer to the created node.

## Iterating over the nodes

It is possible to iterate over each nodes associated with a given list as follow :

```C
int iterator(size_t index, node_t* node)
{
  printf("Node (%d) element : %s\n", index, (char*) node->element);
  return (0);
}

list_iterate_over_nodes(list, &iterator);
```

## Destroying an instance of a list

Similarly to creating a new instance of a list, to delete an instance of a list, you must call `list_destroy` :

```C
list_destroy(list);
```
