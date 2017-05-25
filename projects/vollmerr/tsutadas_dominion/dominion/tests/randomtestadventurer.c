////////////////////////////////////////////////////////////////
// randomtestadventurer.c
// By: Ryan Vollmer
//
// random tests for Adventurer card
// Adventurer depends upon the following state:
//      - numPlayers => [1..MAX_PLAYERS] (must be > whoseTurn)
//      - whoseTurn => [0..MAX_PLAYERS-1]
//      - deckCards[MAX_DECK] => (cards in range [curse..treasure_map])
//      - deckCount[whoseTurn] => [0..MAX_DECK]
//      - deck[whoseTurn][deckCount] => (use deckCards)
//      - handCards[MAX_HAND] => (cards in range [curse..treasure_map])
//      - handCount[whoseTurn] => [0..MAX_HAND]
//      - hand[whoseTurn][handCount] => (use handCards)
//      - discardCards[MAX_HAND] => (cards in range [curse..treasure_map])
//      - discardCount[whoseTurn] => [0..MAX_DECK]
//      - discard[whoseTurn][discardCount] => (use discardCards)
////////////////////////////////////////////////////////////////
#include "tests.h"

/**
 * Initalizes game state with random values withiin bounds
 * @param  actual   - actual outcome of state
 * @param  expected - expected outcome of state
 * @return          - success value
 */
int test_init(struct gameState *actual, struct gameState *expected) {
  int seed = rand();
  int numPlayers = (rand() % MAX_PLAYERS) + 1;
  int whoseTurn = rand() % numPlayers;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

  memset(actual, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, actual);
  actual->whoseTurn = whoseTurn;
  actual->numPlayers = numPlayers;
  cards_init(actual, actual->deckCount, actual->deck);
  cards_init(actual, actual->handCount, actual->hand);
  cards_init(actual, actual->discardCount, actual->discard);
  memcpy(expected, actual, sizeof(struct gameState));

  return 0;
}

/**
 * Runs a single test run for adventurer card
 * @param  actual   - actual state to test
 * @param  expected - expected outcome of state
 * @return          - success value
 */
int test_run(struct gameState *actual, struct gameState *expected) {
  int ret;
  int whoseTurn = actual->whoseTurn;
  int drawntreasure=0;
  int cardDrawn=0;
  int temphand[MAX_HAND];
  int z = 0; // counter for the temp hand
  ret = adventurer_effet(drawntreasure, actual, whoseTurn, cardDrawn, temphand, z);
  test_result(!ret, "the correct return value");

  while(drawntreasure < 2) {
    if (expected->deckCount[whoseTurn] <1) { //if the deck is empty we need to shuffle discard and add to deck
      ret = shuffle(whoseTurn, expected);
      test_result(!ret, "the correct return value from shuffle");
    }
    ret = drawCard(whoseTurn, expected);
    test_result(!ret, "the correct return value from drawCard");
    cardDrawn = expected->hand[whoseTurn][expected->handCount[whoseTurn]-1]; //top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      expected->handCount[whoseTurn]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1 >= 0) {
    expected->discard[whoseTurn][expected->discardCount[whoseTurn]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z = z-1;
  }
  test_result(!memcmp(expected->hand[whoseTurn], actual->hand[whoseTurn], MAX_HAND), "only drawn the 2 treasure cards");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");

  return 0;
}

int main() {
  struct gameState actual, expected;
  int numTests = 1000;
  srand(time(NULL));
  test_header("effect_adventurer");
  for (; numTests; numTests--) {
    test_init(&actual, &expected);
    test_run(&actual, &expected);
  }
  test_header("effect_adventurer Completed.");
  return 0;
}
