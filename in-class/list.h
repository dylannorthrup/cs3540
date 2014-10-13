#ifndef _LIST_H
#define _LIST_H

typedef struct list_node {
  void* item;
  struct list_node* next;
} node;

typedef struct list {
  node* front;
  node* rear;
  int size;
} list;

/*
 * returns a pointer to an empty list
 */
list* create_list ();

/*
 * Precondition: l is not NULL - checked with assertion
 * Returns 1 if list pointed to by l is empty
 */
int is_list_empty (list* l);

/*
 * Precondition: l is not NULL - checked with assertion
 * returns number of elements in list pointed to by l
 */
int size (list* l);

/*
 * Precondition: l is not NULL  - checked with assertion
 * postcondition: datum has been prepended to the list pointed to by l
 */
void prepend(list* l, void* datum);

/*
 * Precondition: l is not NULL  - checked with assertion
 * postcondition: datum has been appended to the list pointed to by l
 */
void append(list* l, void* datum);

/*
 * Preconditions: 
 *  l is not NULL - checked with assertion
 *  0 <= location <= list size    - return non-zero if this is not the case
 * Returns:
 *  0 if datum is inserted
 *  1 otherwise
 * Postcondition: datum has been inserted at specified location in list pointed to by l
 */
int insert (list* l, void* datum, int location);

/*
 * Preconditions:
 *  l is not NULL - checked with assertion
 *  0 <= location < list size    - return non-zero if this is not the case
 * Returns:
 *  0 if datum is removed
 *  1 if datum is not removed
 * Postcondition: datum at location has been removed from list pointed to by l
 */
int remove (list* l, int location);

/*
 * Preconditions:
 *  l is not NULL - checked with assertion
 *  0 <= location < size of list
 * returns NULL if location is not valid
 * returns item stored at location
 */

void* get (list* l, int location);

/*
 * Preconditions:
 *  l is not NULL - checked with assertion
 *  0 <= location < size of list
 * returns 0 if location is valid; returns 1 otherwise
 * postcondition: element at index location is datum
 */

int set (list* l, int location, void* datum);

/*
 * precondition: l is not NULL - checked with assertion
 * postcondition: all memory allocated for list l has been deallocated
 */

void delete_list (list* l);

#endif