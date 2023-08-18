
# Doubly Linked Lists

Author: Clever Ncube

This repository contains solutions for various tasks related to doubly linked lists in C.

## Task 0: Print List

Write a function `print_dlistint` that prints all the elements of a `dlistint_t` list.

### Prototype

```c
size_t print_dlistint(const dlistint_t *h);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 0);
add_dnodeint_end(&head, 1);
add_dnodeint_end(&head, 2);
print_dlistint(head); // Output: 0\n1\n2
```

## Task 1: List Length

Write a function `dlistint_len` that returns the number of elements in a linked `dlistint_t` list.

### Prototype

```c
size_t dlistint_len(const dlistint_t *h);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 0);
add_dnodeint_end(&head, 1);
add_dnodeint_end(&head, 2);
size_t length = dlistint_len(head); // Returns 3
```

## Task 2: Add Node at Beginning

Write a function `add_dnodeint` that adds a new node at the beginning of a `dlistint_t` list.

### Prototype

```c
dlistint_t *add_dnodeint(dlistint_t **head, const int n);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint(&head, 42);
add_dnodeint(&head, 23);
add_dnodeint(&head, 17);
// Resulting list: 17 <-> 23 <-> 42
```

## Task 3: Add Node at End

Write a function `add_dnodeint_end` that adds a new node at the end of a `dlistint_t` list.

### Prototype

```c
dlistint_t *add_dnodeint_end(dlistint_t **head, const int n);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 5);
add_dnodeint_end(&head, 10);
add_dnodeint_end(&head, 15);
// Resulting list: 5 <-> 10 <-> 15
```

## Task 4: Free List

Write a function `free_dlistint` that frees a linked `dlistint_t` list.

### Prototype

```c
void free_dlistint(dlistint_t *head);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 5);
add_dnodeint_end(&head, 10);
add_dnodeint_end(&head, 15);
free_dlistint(head); // Frees the entire list
```

## Task 5: Get Node at Index

Write a function `get_dnodeint_at_index` that returns the nth node of a `dlistint_t` linked list.

### Prototype

```c
dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 5);
add_dnodeint_end(&head, 10);
add_dnodeint_end(&head, 15);
dlistint_t *node = get_dnodeint_at_index(head, 1); // Returns the second node (10)
```

## Task 6: Sum List

Write a function `sum_dlistint` that returns the sum of all the data (n) of a `dlistint_t` linked list.

### Prototype

```c
int sum_dlistint(dlistint_t *head);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 5);
add_dnodeint_end(&head, 10);
add_dnodeint_end(&head, 15);
int total_sum = sum_dlistint(head); // Returns 30
```

## Task 7: Insert at Index

Write a function `insert_dnodeint_at_index` that inserts a new node at a given position in a `dlistint_t` list.

### Prototype

```c
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 5);
add_dnodeint_end(&head, 10);
add_dnodeint_end(&head, 15);
insert_dnodeint_at_index(&head, 1, 7);
// Resulting list: 5 <-> 7 <-> 10 <-> 15
```

## Task 8: Delete at Index

Write a function `delete_dnodeint_at_index` that deletes the node at a given index in a `dlistint_t` linked list.

### Prototype

```c
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index);
```

### Usage

```c
dlistint_t *head = NULL;
add_dnodeint_end(&head, 5);
add_dnodeint_end(&head, 10);
add_dnodeint_end

(&head, 15);
delete_dnodeint_at_index(&head, 1);
// Resulting list: 5 <-> 15
```

## Task 9: Crackme4

Find the password for `crackme4` and save it in the file `100-password`.

## Task 10: Palindromes

Find the largest palindrome made from the product of two 3-digit numbers and save it in the file `102-result`.

## Task 11: Crackme5 Keygen

Write a keygen for `crackme5` using the provided `keygen5` program. The keygen should print a valid key for the given username.

---
 🚀
