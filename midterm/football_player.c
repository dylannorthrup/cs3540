#include "football_player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

football_player* create_football_player (char* n, char* po, int num) {
  // Set return variable to NULL
  football_player* fp = NULL;
  // Check preconditions. If they're not met, return NULLified pointer
  if (n == NULL) { return fp; }
  if (strlen(n) < 1) { return fp; }
  if (po == NULL) { return fp; }
  if (strlen(po) < 1) { return fp; }
  if (num < 0) { return fp; }
  // Preconditions satisfied
  fp = malloc(sizeof(football_player));
  fp -> name = strdup(n);
  fp -> parole_officer = strdup(po);
  fp -> num_jerseys_signed = num;
  return fp;
}

void delete_player (football_player* player) {
  assert (player != NULL);
  if (player -> name != NULL) { free (player -> name); }
  if (player -> parole_officer != NULL) { free (player -> parole_officer); }
  free(player);
}

void additional_jerseys_signed (football_player* player, int num_jerseys) {
  assert (player != NULL);
  assert (num_jerseys >= 0);
  player -> num_jerseys_signed += num_jerseys;
}

void display_player (football_player* player) {
  assert (player != NULL);
  printf ("Player Name: %s\n", player -> name);
  printf ("\tPO: %s\n", player -> parole_officer);
  printf ("\tJerseys Signed: %d\n", player -> num_jerseys_signed);
}
