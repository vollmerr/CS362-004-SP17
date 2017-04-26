////////////////////////////////////////////////////////////////
// unittest4.c
// By: Ryan Vollmer
//
// unit test for dominion function handCard
////////////////////////////////////////////////////////////////
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int test_handCard(struct gameState *actual, struct gameState *expected, int player, int handPos) {
  int r, card;
  r = handCard(handPos, actual);
  card = expected->hand[player][handPos];

  test_result(r == card, "the correct card returned");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");
  return r;
}

int main() {
  int numPlayer, player, handPos;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  // int debug=1, r;
  SelectStream(2);
  PutSeed(3);
  test_header("handCard");
  for (numPlayer = 2; numPlayer < MAX_PLAYERS; numPlayer++) {
    for (player = 0; player < numPlayer; player++) {
      for (handPos = 0; handPos < 10; handPos++) {
        memset(&actual, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, 1, &actual);
        actual.handCount[player] = 10;
        memcpy(actual.hand[player], k, sizeof(int) * 10);
        actual.whoseTurn = player;
        memcpy(&expected, &actual, sizeof(struct gameState));
        // compare results
        test_handCard(&actual, &expected, player, handPos);
      }
    }
  }
  test_header("handCard Completed.");
  return 0;
}
