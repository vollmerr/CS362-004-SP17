////////////////////////////////////////////////////////////////
// randomtestcard2.c
// By: Ryan Vollmer
//
// random tests for Council Room card
// Council Room depends upon the following state:
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
//      - playedCards[playedCardCount] => (cards in range [curse..treasure_map])
//      - playedCardCount => (int)
//      - numBuys => (0..int)
////////////////////////////////////////////////////////////////
#include "tests.h"

/**
 * Initalizes game state with random values withiin bounds
 * @param  actual   - actual outcome of state
 * @param  expected - expected outcome of state
 * @return          - success value
 */
int test_init(struct gameState *actual, struct gameState *expected) {
  int i;
  int seed = rand();
  int numPlayers = (rand() % MAX_PLAYERS) + 1;
  int whoseTurn = rand() % numPlayers;
  int playedCardCount = rand() % MAX_HAND;
  int numBuys = rand() % 20;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

  memset(actual, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, actual);
  actual->whoseTurn = whoseTurn;
  actual->numPlayers = numPlayers;
  actual->playedCardCount = playedCardCount;
  actual->numBuys = numBuys;
  cards_init(actual, actual->deckCount, actual->deck);
  cards_init(actual, actual->handCount, actual->hand);
  cards_init(actual, actual->discardCount, actual->discard);
  for (i=0; i<playedCardCount; i++) {
    actual->playedCards[i] = rand() % (treasure_map + 1);
  }
  memcpy(expected, actual, sizeof(struct gameState));

  return 0;
}

/**
 * Runs a single test run for council room card
 * @param  actual   - actual state to test
 * @param  expected - expected outcome of state
 * @return          - success value
 */
int test_run(struct gameState *actual, struct gameState *expected) {
  int ret, i;
  int whoseTurn = actual->whoseTurn;
  int numPlayers = actual->numPlayers;
  int handPos = rand() % (actual->handCount[whoseTurn] + 1);
  int expectedHandCount = actual->handCount[whoseTurn] + 3; // +4, -1 for played
  // run actual function
  ret = effect_council_room(handPos, actual);
  test_result(!ret, "the correct return value");
  // draw 4 cards
  for (i=0; i<4; i++) {
    ret = drawCard(whoseTurn, expected);
    test_result(!ret, "the correct return value from drawCard");
  }
  // add a buy
  expected->numBuys++;
  test_result(actual->numBuys == expected->numBuys, "added a buy to the current player");
  // draw a card for all other players
  for (i=0; i<numPlayers; i++) {
    if (i != whoseTurn) {
      ret = drawCard(i, expected);
      test_result(!ret, "the correct return value from drawCard");
    }
  }
  // discard played card
  ret = discardCard(handPos, whoseTurn, expected, 0);
  test_result(!ret, "the correct return value from discardCard");
  test_result(actual->handCount[whoseTurn] == expectedHandCount, "added 4 cards to the current player");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "effected only values of the game state it needed to");

  return 0;
}

int main() {
  struct gameState actual, expected;
  int numTests = 1000;
  srand(time(NULL));
  test_header("effect_council_room");
  for (; numTests; numTests--) {
    test_init(&actual, &expected);
    test_run(&actual, &expected);
  }
  test_header("effect_council_room Completed.");
  return 0;
}
