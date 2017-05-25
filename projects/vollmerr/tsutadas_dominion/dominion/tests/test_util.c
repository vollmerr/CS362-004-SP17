////////////////////////////////////////////////////////////////
// test_util.c
// By: Ryan Vollmer
//
// utility functions for running tests
////////////////////////////////////////////////////////////////
#include "tests.h"

/**
 * Generates random cards and sets count
 * @param  numPlayers - number of players
 * @param  player     - current player
 * @param  count      - count of card pile
 * @param  cards      - cards to fill up
 * @return            - success value
 */
int cards_init(struct gameState *state, int *count, int (*cards)[MAX_DECK]) {
  int i, rnd;
  rnd = rand() % (MAX_DECK + 1);
  // set random cards for current player
  for (i=0; i<rnd; i++) {
    cards[state->whoseTurn][i] = rand() % (treasure_map + 1);
  }
  // set count for current players cards
  count[state->whoseTurn] = rnd;
  return 0;
}

/**
 * Assertion function, prints message on failure
 * @param  result - result to assert
 * @param  msg    - description of what it failed to do
 * @return        - success ? 0 : 1
 */
int test_result(int result, char *msg) {
  if (!result) {
    printf("\nFAILED test...\n It should have %s\n\n", msg);
    return 1;
  }
  printf("#");
  return 0;
}

/**
 * Prints header for what is being tested
 * @param name - name to display
 */
void test_header(char *name) {
  printf("\n\n############ Testing %s ############\n\n", name);
}

/**
 * Prints array for testing purposes
 * @param arr - array to display
 * @param n   - size of array
 * @param msg - header to display
 */
void print_(int *arr, int n, char *msg) {
  printf("\n\n---- %s ---\n", msg);
  int i;
  for (i=0; i<n; i++) {
    printf("%d : %d\n", i, arr[i]);
  }
  printf("\n++++++++++++++++++\n\n");
}
