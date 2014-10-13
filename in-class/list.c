#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*
 * Function to create a new node
 */
node* create_node(void* datum) {
  node* n = malloc(sizeof(node));
  n -> item = datum;
  n -> next = NULL;
  return n;
}

list* create_list() {
  list* l = malloc(sizeof(list));
  l -> front = NULL;
  l -> rear = NULL;
  l -> size = 0;
  return l;
}


int is_empty (list* l) {
  assert (l != NULL);
  return l -> size == 0;
}

int size (list* l) {
  assert (l != NULL);
  return l -> size;
}

void prepend (list* l, void* datum) {
  assert (l != NULL);
  node* n = create_node(datum);
  if(is_empty(l)) {
    l -> front = n;
    l -> rear = n;
  } else {
    n -> next = l -> front; /* point n->next at previous first node */
    l -> front = n;         /* now, point the front of the list at n */
  }
  l -> size++;
}

void append (list* l, void* datum) {
    assert (l != NULL);
  node* n = create_node(datum);
  if(is_empty(l)) {
    l -> front = n;
    l -> rear = n;
  } else {
    l -> rear -> next = n;  /* Access next field of last node and point it to n */
    l -> rear = n;          /* then update list to make n the last node */
  }
  l -> size++;
}

int insert (list* l, void* datum, int location) {
  assert (l != NULL);
  int result = 0;

  /* Check location validity */
  if (location < 0 || location > l -> size {
    result = 1;
  } else {
    if(location == 0) {
      prepend (l, datum);
    } else if (location == l -> size) {
      append (l, datum);
    } else {
      node* n = create_node (datum);
      node* temp = l -> front;
      int i = 0;
      for (; i < location - l; i++) {
        temp = temp -> next;
      }
      n -> next = temp -> next;
      temp -> next = n;
      l -> size++;
    }
  }
  return result;
}

int remove (list* l, int location) {
  assert (l != NULL);
  int result = 0;
  // Check for an invalid location
  if (location < 0 || location >= size(1)){
    result = 1;
  } else {  // If the location is valid, go ahead and remove things
    if (location == 0) {  // Remove front item
      node* temp = l -> front;  // Store the value for the front pointer
      l -> front = l -> front -> next;  // Move the actual front value up
      if(l -> front == NULL) { // Handles degenerate case where list has no elements
        l -> rear = NULL;
      }
      free (temp);  // Make sure to free up the memory
    } else if (location == size(l){ // 
      node* n = l -> front;
      // Increment through list to get to the node immediately before what we're going to remove
      int i = 0;
      for(; i< location - 1; i++) { 
        n = n -> next;
      }
      node* temp = n -> next;
      if (temp -> next == NULL) { // We're removing the last element
        l -> rear = n;
      } else {  // Have the previous node point to the next node
        n -> next = temp -> rear;
      }
      // Free the memory of the node we're removing
      free (temp);
    }
  }
  return result;
}

void* get (list* l, int location) {
  assert (l != NULL);

}

int set (list* l, int location, void* datum) {
  assert (l != NULL);

  return 0;
}

void delete_list (list* l) {
  assert (l != NULL);

}

