////////////////////////////////////////////////////////////////
// unittest1.c
// By: Ryan Vollmer
//
// unit test for dominion card council room
////////////////////////////////////////////////////////////////
#include "tests.h"

void test_effect_council_room(struct gameState *actual, struct gameState *expected, int handPos, int player) {
  int ret, i;
  ret = effect_council_room(handPos, actual);
  for (i = 0; i < 4; i++) {
    drawCard(player, expected);
  }
  expected->numBuys++;
  drawCard(1 - player, expected);
  discardCard(handPos, player, expected, 0);
  test_result(!ret, "the correct return value");
  test_result(actual->handCount[player] == expected->handCount[player], "added 4 cards to the current player");
  test_result(actual->numBuys == expected->numBuys, "added a buy to the current player");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");
}

int main() {
  int player, handPos, handCount, numBuys;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  SelectStream(2);
  PutSeed(3);
  test_header("effect_council_room");
  for (player = 0; player < 2; player++) {
    for (handPos=0; handPos < 3; handPos++) {
      for (handCount=1; handCount < 3; handCount++) {
        for (numBuys=0; numBuys < 3; numBuys++) {
          memset(&actual, 23, sizeof(struct gameState));
          initializeGame(2, k, 1, &actual);
          // init game state based off player
          actual.numPlayers = 2;
          actual.numBuys = numBuys;
          actual.handCount[player] = handCount;
          actual.whoseTurn = player;
          memcpy(&expected, &actual, sizeof(struct gameState));
          // compare results
          test_effect_council_room(&actual, &expected, handPos, player);
        }
      }
    }
  }
  test_header("effect_council_room Completed.");
  return 0;
}
