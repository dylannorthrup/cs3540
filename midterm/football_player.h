#ifndef _FOOTBALL_PLAYER_H
#define _FOOTBALL_PLAYER_H

typedef struct
{
  char* name;
  char* parole_officer;
  int num_jerseys_signed;
} football_player;

/*******************************************************
precondition:: n is not NULL & has length at least 1
precondition:: po is not NULL & has length at least 1
precondition: num >= 0
return NULL if any precondition is not valid
return pointer to newly created football_player if all
preconditions are valid
*/
football_player* create_football_player (char* n, char* po, int num);

/*********************************************************
precondition: player is not NULL - checked with assertion
postcondition: all dynamic memory allocated to player
has been deallocated
*/
void delete_player (football_player* player);

/********************************************************
precondition: player is not NULL - checked with assertion
precondition: num_jerseys >= 0 - checked with assertion
postcondition: number of jerseys signed by player has
been increased by num_jerseys
*/
void additional_jerseys_signed (football_player* player, int num_jerseys);

/******************************************************
precondition: player is not NULL - checked with assertion
postcondition: player information has been displayed on
standard output
*/
void display_player (football_player* player);

#endif
