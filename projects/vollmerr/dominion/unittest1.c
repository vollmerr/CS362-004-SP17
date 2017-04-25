////////////////////////////////////////////////////////////////
// unittest1.c
// By: Ryan Vollmer
//
// unit test for dominion function updateCoins
////////////////////////////////////////////////////////////////
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void test_updateCoins(struct gameState *actual, struct gameState *expected, int ret) {
  test_result(!ret, "the correct return value");
  test_result(actual->coins == expected->coins, "reset current players coins, added based off cards, then added bonus");
  test_result(!memcmp(expected, actual, sizeof(struct gameState)), "not effected other values of the game state");
}

int main() {
  int player, coins_start, coins_bonus, num_copper, num_silver, num_gold, i, ret;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState actual, expected;
  SelectStream(2);
  PutSeed(3);
  test_header("updateCoins");
  for (player = 0; player < 2; player++) {
    for (coins_start=0; coins_start < 3; coins_start++) {
      for (coins_bonus=0; coins_bonus < 3; coins_bonus++) {
        for (num_copper=0; num_copper < 3; num_copper++) {
          for (num_silver=0; num_silver < 3; num_silver++) {
            for (num_gold=0; num_gold < 3; num_gold++) {
              memset(&actual, 23, sizeof(struct gameState));
              initializeGame(2, k, 1, &actual);
              // init game state based off player
              actual.handCount[player] = num_copper + num_silver + num_gold;
              actual.discardCount[player] = 5;
              actual.deckCount[player] = 5;
              // init players cards to be treasure cards
              for (i = 0; i < num_copper; i++) {
                actual.hand[player][i] = copper;
              }
              for (i = 0; i < num_silver; i++) {
                actual.hand[player][i + num_copper] = silver;
              }
              for (i = 0; i < num_gold; i++) {
                actual.hand[player][i + num_copper + num_silver] = gold;
              }
              memcpy(&expected, &actual, sizeof(struct gameState));
              expected.coins = (num_copper * 1) + (num_silver * 2) + (num_gold * 3) + coins_bonus;
              ret = updateCoins(player, &actual, coins_bonus);
              // compare results
              test_updateCoins(&actual, &expected, ret);
            }
          }
        }
      }
    }
  }
  test_header("updateCoins Completed.");
  return 0;
}
