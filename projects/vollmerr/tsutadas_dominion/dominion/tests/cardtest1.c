////////////////////////////////////////////////////////////////
// unittest1.c
// By: Ryan Vollmer
//
// unit test for dominion card adventurer
////////////////////////////////////////////////////////////////
#include "tests.h"

void test_effect_adventurer(struct gameState *actual, struct gameState *expected, int player, int hand_count) {
  int ret;
  int drawntreasure=0;
  int cardDrawn=0;
  int temphand[MAX_HAND];
  int z = 0; // counter for the temp hand
  while(drawntreasure<2) {
    if (expected->deckCount[player] <1) { //if the deck is empty we need to shuffle discard and add to deck
      shuffle(player, expected);
    }
    drawCard(player, expected);
    cardDrawn = expected->hand[player][expected->handCount[player]-1]; //top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      expected->handCount[player]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1>=0) {
    expected->discard[player][expected->discardCount[player]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  ret = adventurer_effet(drawntreasure, actual, player, cardDrawn, temphand, z);

  test_result(!ret, "the correct return value");
  test_result(!memcmp(expected->hand[player], actual->hand[player], MAX_HAND), "only drawn the 2 treasure cards");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");
}

int main() {
  int player, deck_count, hand_count, discard_count, i;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  SelectStream(2);
  PutSeed(3);
  test_header("effect_adventurer");
  for (player = 0; player < 2; player++) {
    for (deck_count=0; deck_count < 3; deck_count++) {
      for (hand_count=0; hand_count < 4; hand_count++) {
        for (discard_count=0; discard_count < 3; discard_count++) {
          memset(&actual, 23, sizeof(struct gameState));
          initializeGame(2, k, 1, &actual);
          // init game state based off player
          actual.handCount[player] = hand_count;
          for (i=0; i<hand_count; i++) {
            actual.hand[player][i] = k[i];
          }
          actual.discardCount[player] = discard_count;
          for (i=0; i<discard_count; i++) {
            actual.discard[player][i] = 4;
          }
          actual.deckCount[player] = deck_count;
          actual.whoseTurn = player;
          memcpy(&expected, &actual, sizeof(struct gameState));
          // compare results
          test_effect_adventurer(&actual, &expected, player, hand_count);
        }
      }
    }
  }
  test_header("effect_adventurer Completed.");
  return 0;
}
