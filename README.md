![Logo](http://dory.fr/images/jouets/train2.png)

# Circular linked list

This is an implementation of a tiny circular linked list in C.

Current version: **0.1.0**

## Creating an instance of a list

Every list instance are of types `list_t`.

In order to create a new instance of a list, you must call `list_create`.

```C
list_t* list = list_create();
```

## Destroying an instance of a list

Similarly to delete an instance of a list, you must call `list_destroy` :

```C
list_destroy(list);
```
