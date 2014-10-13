#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void display_list (list* l);

int main ()
{
  //printf("test_list: Creating list\n");
  list* l = create_list();
  int n1 = 4;
  //printf("test_list: Appending n1 to list\n");
  append (l, &n1);
  int n2 = 3;
  //printf("test_list: Prepending n2 to list\n");
  prepend (l, &n2);
  int n3 = 7;
  //printf("test_list: Appending n3 to list\n");
  append (l, &n3);
  int n4 = 5;
  //printf("test_list: Inserting n4 into list\n");
  int result = insert (l, &n4, 2);
  assert (result != 0);
  int n5 = 12;
  result = set (l, &n5, 1);
  assert (result != 0);
  result = remove_from_list (l, 1);
  assert (result != 0);
  result = remove_from_list (l, 2);
  assert (result != 0);
  result = remove_from_list (l, 0);
  assert (result != 0); 
  display_list (l);
  delete_list (l);
  return 0;
}

void display_list (list* l)
{
  if (l == NULL)
    printf ("list does not exist\n");
  else
  {
    int i = 0;
    for (i = 0; i < size(l); i++)
    {
      int* num = (int*)get(l, i);
      printf ("%d ", *num);
    }
    printf ("\n");
  }
}
