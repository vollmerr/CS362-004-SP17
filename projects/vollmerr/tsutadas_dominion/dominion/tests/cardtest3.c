////////////////////////////////////////////////////////////////
// unittest1.c
// By: Ryan Vollmer
//
// unit test for dominion card council room
////////////////////////////////////////////////////////////////
#include "tests.h"

void test_effect_smithy(struct gameState *actual, struct gameState *expected, int player) {
  int ret, i; 
  ret = smithy_effect(player, actual, 0);
  for (i = 0; i < 3; i++) {
    drawCard(player, expected);
  }
  discardCard(0, player, expected, 0);
  test_result(!ret, "the correct return value");
  test_result(actual->handCount[player] == expected->handCount[player], "drawn the correct number of cards");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");
}

int main() {
  int player, deck_count, hand_count, discard_count;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  SelectStream(2);
  PutSeed(3);
  test_header("effect_smithy");
  for (player = 0; player < 2; player++) {
    for (deck_count=0; deck_count < 3; deck_count++) {
      for (hand_count=0; hand_count < 3; hand_count++) {
        for (discard_count=0; discard_count < 3; discard_count++) {
          memset(&actual, 23, sizeof(struct gameState));
          initializeGame(2, k, 1, &actual);
          // init game state based off player
          actual.handCount[player] = hand_count;
          actual.discardCount[player] = discard_count;
          actual.deckCount[player] = deck_count;
          memcpy(&expected, &actual, sizeof(struct gameState));
          // compare results
          test_effect_smithy(&actual, &expected, player);
        }
      }
    }
  }
  test_header("effect_smithy Completed.");
  return 0;
}
