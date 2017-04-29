////////////////////////////////////////////////////////////////
// unittest3.c
// By: Ryan Vollmer
//
// unit test for dominion function playCard
////////////////////////////////////////////////////////////////
#include "tests.h"

int test_playCard(struct gameState *actual, struct gameState *expected, int handPos, int choice1, int choice2, int choice3) {
  int card;
  int ret, r;
  r = playCard(handPos, choice1, choice2, choice3, actual);
  if (expected->phase != 0) {
    test_result(r == -1, "return error code when its not the correct phase");
  }
  else {
    if (expected->numActions < 1) {
      test_result(r == -1, "return error code when player does not have enough actions");
    }
    else {
      card = handCard(handPos, expected);
      if (card < adventurer) {
        test_result(r == -1, "return error code when card is not an action (lower bound)");
      }
      else if (card > treasure_map) {
        test_result(r == -1, "return error code when card is not an action (upper bound)");
      }
      else {
        ret = cardEffect(card, choice1, choice2, choice3, expected, handPos, 0);
        if (ret < 0) {
          test_result(r == -1, "return error code when bad card effect input");
        }
        else {
          expected->numActions--;
          test_result(expected->numActions == actual->numActions, "reduced number of actions");
          updateCoins(expected->whoseTurn, expected, 0);
          test_result(!ret, "the correct return value");
        }
      }
    }
  }
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");
  return r;
}

int main() {
  int player, handPos, numActions, phase, choice1, choice2, choice3, i;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  SelectStream(2);
  PutSeed(3);
  test_header("playCard");
  for (player = 0; player < 2; player++) {
    for (handPos=0; handPos < 10; handPos++) {
      for (numActions=0; numActions < 2; numActions++) {
        for (phase=0; phase<2; phase++) {
          for (choice1=0; choice1 < 2; choice1++) {
            for (choice2=0; choice2 < 2; choice2++) {
              for (choice3=0; choice3 < 2; choice3++) {
                memset(&actual, 23, sizeof(struct gameState));
                initializeGame(2, k, 1, &actual);
                // init game state
                actual.handCount[player] = 10;
                actual.phase = phase;
                actual.numActions = numActions;
                actual.whoseTurn = player;
                // init players cards to default cards
                for (i = 0; i < 10; i++) {
                  actual.hand[player][i] = k[i];
                }
                memcpy(&expected, &actual, sizeof(struct gameState));
                // compare results
                test_playCard(&actual, &expected, handPos, choice1, choice2, choice3);
              }
            }
          }
        }
      }
    }
  }
  test_header("playCard Completed.");
  return 0;
}
