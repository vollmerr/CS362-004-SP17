////////////////////////////////////////////////////////////////
// unittest1.c
// By: Ryan Vollmer
//
// unit test for dominion card minion
////////////////////////////////////////////////////////////////
#include "tests.h"

int test_effect_minion(struct gameState *actual, struct gameState *expected, int handPos, int choice1, int choice2) {
  int r, i, j;
  int player = whoseTurn(expected);
  r = effect_minion(handPos, actual, choice1, choice2);
  expected->numActions++;
  test_result(actual->numActions == expected->numActions, "added 1 action for current player");
  discardCard(handPos, player, expected, 0);
  if (choice1) {
    expected->coins += 2;
    test_result(actual->coins == expected->coins, "return error code when its not the correct phase");
  }
  else if (choice2) {
    //discard hand
    while(numHandCards(expected) > 0) {
      discardCard(handPos, player, expected, 0);
    }
    //draw 4
    for (i = 0; i < 4; i++) {
      drawCard(player, expected);
    }
    //other players discard hand and redraw if hand size > 4
    for (i = 0; i < expected->numPlayers; i++) {
      if (i != player) {
        if ( expected->handCount[i] > 4 ) {
          //discard hand
          while( expected->handCount[i] > 0 ) {
            discardCard(handPos, i, expected, 0);
          }
          //draw 4
          for (j = 0; j < 4; j++) {
            drawCard(i, expected);
          }
          test_result(expected->handCount[i] == actual->handCount[i], "replace other players hand with 4 cards");
        }
      }
    }
  }
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");
  return r;
}

int main() {
  int player, handPos, numActions, choice1, choice2, i;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  SelectStream(2);
  PutSeed(3);
  test_header("effect_minion");
  for (player = 0; player < 2; player++) {
    for (handPos=0; handPos < 10; handPos++) {
      for (numActions=0; numActions < 2; numActions++) {
        for (choice1=0; choice1 < 2; choice1++) {
          for (choice2=0; choice2 < 2; choice2++) {
            memset(&actual, 23, sizeof(struct gameState));
            initializeGame(2, k, 1, &actual);
            // init game state
            actual.handCount[player] = 10;
            actual.numActions = numActions;
            actual.whoseTurn = player;
            // init players cards to default cards
            for (i = 0; i < 10; i++) {
              actual.hand[player][i] = k[i];
            }
            memcpy(&expected, &actual, sizeof(struct gameState));
            // compare results
            test_effect_minion(&actual, &expected, handPos, choice1, choice2);
          }
        }
      }
    }
  }
  test_header("effect_minion Completed.");
  return 0;
}
