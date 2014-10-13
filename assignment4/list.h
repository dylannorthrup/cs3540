#ifndef _LIST_H
#define _LIST_H

typedef struct list_node {
  void* item;
  struct list_node* next;
  struct list_node* prev;
} node;

typedef struct {
  node* front;
  node* rear;
  int size;
} list;

/**************************************************
return pointer to an empty list - NULL if list cannot be created
*/
list* create_list();

/*************************************************
precondition: l is not NULL - checked with assertion
return whether list pointed to by l is empty
*/
int is_empty (const list* l);

/*************************************************
precondition: l is not NULL - checked with assertion
return number of elements in the list
*/

int size (const list* l);

/**************************************************
precondition: l is not NULL - checked with assertion
postcondition: item is at the end of *l
**************************************************/
void append (list* l, void* item);

/**************************************************
precondition: l is not NULL - checked with assertion
postcondition: item is at the beginning of *l
**************************************************/
void prepend (list* l, void* item);

/****************************************************
precondition: l is not NULL - checked with assertion
precondition: 0 <= index <= size of list
returns false if location is not valid - true ow
postcondition: item is at location in *l
*/
int insert (list* l, void* item, int index);

/******************************************************
precondition: l is not NULL - checked with assertion
precondition: 0 <= index < size of list
returns false if index is not valid - true ow
postcondition: item at index in *l has been removed
*/
int remove_from_list (list* l, int index);

/*****************************************************
precondition: l is not NULL - checked with assertion
precondition:  0 <= index < size of list
return element at index position of list - NULL if index
is not valid
****************************************************/
void* get (const list* l, int index);

/*****************************************************
precondition: l is not NULL - checked with assertion
precondition:  0 <= index < size of list
return true if index is valid - false otherwise
postcondition: item is at index location in list
***************************************************/
int set (list* l, void* item, int index);

/*************************************************
precondition: l is NULL - checked with assertion
postcondition: all components to the list have been
deallocated
*/
void delete_list (list* l);

#endif
