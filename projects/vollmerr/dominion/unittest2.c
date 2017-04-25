////////////////////////////////////////////////////////////////
// unittest2.c
// By: Ryan Vollmer
//
// unit test for dominion function discardCard
////////////////////////////////////////////////////////////////
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int test_discardCard(struct gameState *actual, struct gameState *expected, int ret, int player) {
  int r = 0;
  // print_(expected->hand[player], 5, "expected");
  // print_(actual->hand[player], 5, "actual");
  test_result(!ret, "the correct return value");
  test_result(expected->playedCardCount == actual->playedCardCount, "updated played card count if trash flag set");
  test_result(!memcmp(expected->playedCards, actual->playedCards, MAX_DECK), "updated played cards if trash flag set");
  test_result(expected->handCount[player] == actual->handCount[player], "updated the players hand count");
  test_result(!memcmp(expected->hand[player], actual->hand[player], MAX_HAND), "updated the players hand");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "not effected other values of the game state");
  return r;
}

int main() {
  int debug = 0;
  int player, handPos, handCount, playedCardCount, trashFlag, ret, i;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  SelectStream(2);
  PutSeed(3);
  test_header("discardCard");
  for (player = 0; player < 2; player++) {
    for (handPos=0; handPos < 3; handPos++) {
      for (handCount=1; handCount < 3; handCount++) {
        for (playedCardCount=0; playedCardCount<3; playedCardCount++) {
          for (trashFlag=0; trashFlag < 2; trashFlag++) {
            memset(&actual, 23, sizeof(struct gameState));
            initializeGame(2, k, 1, &actual);
            // init game state based off player
            actual.handCount[player] = handCount;
            actual.discardCount[player] = 5;
            actual.deckCount[player] = 5;
            // init players cards to be not -1
            for (i = 0; i < handCount; i++) {
              actual.hand[player][i] = 4;
            }
            // init players played cards
            actual.playedCardCount = playedCardCount;
            for (i = 0; i < playedCardCount; i++) {
              actual.playedCards[i] = 4;
            }
            memcpy(&expected, &actual, sizeof(struct gameState));
            ret = discardCard(handPos, player, &actual, trashFlag);
            // if no trash flag, should add card to played pile
            if (trashFlag < 1) {
              expected.playedCards[playedCardCount] = expected.hand[player][handPos];
              expected.playedCardCount = playedCardCount + 1;
            }
            expected.hand[player][handPos] = -1;
            // if not last or first card in hand, replace with last card
            if (expected.handCount[player] > 1 && handPos != (expected.handCount[player] - 1)) {
              expected.hand[player][handPos] = expected.hand[player][expected.handCount[player] - 1];
              expected.hand[player][handCount - 1] = -1;
            }
            expected.handCount[player]--;
            // compare results
            ret = test_discardCard(&actual, &expected, ret, player);
            if (ret && debug) {
              printf("with values:\n\tplayer: %d\n\thandPos: %d\n\thandCount: %d\n\tplayerCardCount: %d\n\ttrashFlag: %d\n", player, handPos, handCount, playedCardCount, trashFlag);
            }
          }
        }
      }
    }
  }
  test_header("discardCard Completed.");
  return 0;
}
