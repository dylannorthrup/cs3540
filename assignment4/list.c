#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Create node and init values to NULL
node* create_node (void* item) {
  node* n = malloc (sizeof(node));
  if (n != NULL) {
    n -> item = item;
    n -> next = NULL;
    n -> prev = NULL;
  }
  return n;
}

// Create node that's empty (front and rear point to NULL and size is 0)
list* create_list() {
  list* l = malloc (sizeof (list));
  if (l != NULL) {
    l -> front = NULL;
    l -> rear = NULL;
    l -> size = 0;
  }
  return l;
}

// Tell us if the list is empty or not
int is_empty (const list* l) {
  assert (l != NULL);
  return l -> size == 0;
}

// Tell us what the size of the list is
int size (const list* l) {
  assert (l != NULL);
  return l -> size;
}

// Add an item to the end of the list
void append (list* l, void* item) {
  assert (l != NULL);
  insert(l, item, size(l));
}

// Add an item to the beginning of the list
void prepend (list* l, void* item) {
  assert (l != NULL);
  insert(l, item, size(l));
}

// Add an item to the list at a specified location
int insert (list* l, void* item, int index) {
  assert (l != NULL);
  int valid = index >= 0 && index <= size(l);
  if (valid) {
    // Go ahead and create the node
    node* temp = create_node (item);
    node* n = l -> front;
    // If this is the first item to be inserted, the logic is simple
    if (size(l) == 0) {
      temp -> next = temp;
      temp -> prev = temp;
      l -> front = temp;
      l -> rear = temp;
    } else if (size(l) == 1) {  // If there's only one other item, logic is still simple
      n -> prev = temp;   // Point n.prev to temp
      n -> next = temp;   // Point n.next to temp
      temp -> prev = n;   // Point temp.prev to n
      temp -> next = n;   // Point temp.prev to n
      if (index) { // This will trigger if we're appending
        l -> front = temp;
        l -> rear = n;
      } else { // And this will trigger when we're prepending
        l -> front = n;
        l -> rear = temp;
      }
    } else {  // Now for the general case
      // Traverse to the index we're wanting to get to
      int i = 0;
      for (i = 0; i < index - 1; i++) {
        n = n -> next;
      }
      // n points to the node prior to the location we want to insert.
      node* a = n -> next;          // Make pointer to temp.next
      temp -> next = n -> next;     // Point temp.next at what n.next is pointing to
      temp -> prev = n;             // Point temp.prev at n
      n -> next = temp;             // Point n.next at temp
      a -> prev = temp;             // Point a -> prev to temp
      // If we want to prepend or append, we'll need to take care of one of the l pointers
      if(index == size(l)) {  // We're appending
        l -> front = temp;
      } else if(index == 0) {  // We're prepending
        l -> rear = temp;
      }
    }
    // Lastly, bump the size of l
    l -> size++;
  }
  return valid;
}

// Remove an item from the list at a specified location
int remove_from_list (list* l, int index) {
  assert (l != NULL);
  int valid = index >= 0 && index < size(l);
  if (valid) {
    node* r;  // Node to be removed
    node* b;  // Node before r
    node* a;  // Node after r
    // If the size of the list is 1, the logic is simple
    if (size(l) == 1) {
      // Set this so we can free it later
      r = l -> front;
      // Then set the l pointers to NULL
      l -> front = NULL;
      l -> rear = NULL;
    } else {
      if (index == 0) {
        r = l -> front; // Set r to the front node
        b = r -> prev;  // Set b to the node before r
        a = r -> next;  // Set a to the node after r
        b -> next = a;  // Set b's next node to a
        a -> prev = b;  // Set a's previous node to b
        l -> front = a; // Point l's beginning to a (which is now the new front)
      } else {
        b = l -> front; // Set b to the front node
        // Iterate through until we get to the right place in the list
        int i = 0;
        for (i = 0; i < index - 1; i++) {
          b = b -> next;
        }
        r = b -> next;  // Set r to the node after b
        a = r -> next;  // Set a to the node after r
        b -> next = a;  // Set b's next node to a
        a -> prev = b;  // Set a's previous node to b
        if (index == size(l) - 1) {
          l -> rear = b;
        }
      }
    }
    free (r);
    l -> size--;
  }
  return valid;
}

// Get the value of an item from the list at a specified location
void* get (const list* l, int index) {
  assert (l != NULL);
  void* result = NULL;
  if (0 <= index && index < size(l)) {
    node* n = l -> front;;
    int i = 0;
    for (i = 0; i < index; i++) {
      n = n -> next;
    }
    result = n -> item;
  }
  return result;
}

// Set the value of an item from the list at a specified location
int set (list* l, void* item, int index) {
  assert (l != NULL);
  int result = 0 <= index && index < size(l);
  if (result) {
    node* n = l -> front;
    int i;
    for (i = 0; i < index; i++) {
      n = n -> next;
    }
    n -> item = item;
  }
  return result;
}

// Get rid of the list (and all elements it contains)
void delete_list (list* l) {
  assert (l != NULL);
  node* current = l -> front;
  node* prev  = NULL;
  int i = 0;
  for (i = 0; i < size(l); i++) {
    prev = current;
    current = current -> next;
    free (prev);
  }
  free (l);
}
