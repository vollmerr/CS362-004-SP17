#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * Effect for adventurer card.
 *  Reveal cards from deck until 2 treasure cards
 *  then put treasure into hand and discard rest.
 * @param  state - state of game
 * @return       - success value
 */
int effect_adventurer(struct gameState *state) {
  int currentPlayer = whoseTurn(state);
  int drawntreasure=0;
  int cardDrawn;
  int temphand[MAX_HAND];
  int z = 0; // counter for the temp hand
  while(drawntreasure<2) {
    if (state->deckCount[currentPlayer] <1) { //if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //top card of hand is most recently drawn card.
    if (cardDrawn = copper || cardDrawn == silver || cardDrawn == gold) //BUG: should be ==
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1>=0) {
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  return 0;
}

/**
 * Effect for council room card.
 *  +4 cards
 *  +1 buy
 *  +1 card for other players
 * @param  handPos - position of card played
 * @param  state  - state of game
 * @return        - success value
 */
int effect_council_room(int handPos, struct gameState *state) {
  int currentPlayer = whoseTurn(state);
  int i;
  //+4 Cards
  for (i = 0; i < 4; i++) {
    drawCard(currentPlayer, state);
  }
  //+1 Buy
  state->numBuys--; //BUG: shouold be ++
  //Each other player draws a card
  for (i = 0; i < state->numPlayers; i++) {
    if ( i != currentPlayer ) {
      drawCard(i, state);
    }
  }
  //put played card in played card pile
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}

/**
 * Effect for smithy card.
 *  +3 cards
 * @param  handPos - position of card played
 * @param  state   - state of game
 * @return         - success value
 */
int effect_smithy(int handPos, struct gameState *state) {
  int currentPlayer = whoseTurn(state);
  int i;
  //+3 Cards
  for (i = 0; i <= 3; i++) { //BUG: should be <
    drawCard(currentPlayer, state);
  }
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}

/**
 * Effect for minion card.
 *  +1 action
 *  +2 treasure OR discard hand, +4 cards
 *    and other players with 5+ cards discard hand, +4 cards
 * @param  handPos  - position of card played
 * @param  state    - state of game
 * @param  choice1  - determines if choice is 1
 * @param  choice2  - determines if choice is 2
 * @return          - success value
 */
int effect_minion(int handPos, struct gameState *state, int choice1, int choice2) {
  int currentPlayer = whoseTurn(state);
  int i, j;
  //+1 action
  state->numActions++;
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  if (choice1) {     //+2 coins
    state->coins = state->coins + 2;
  }
  else if (choice2) {    //discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    //discard hand
    while(numHandCards(state) > 0) {
      discardCard(handPos, currentPlayer, state, 0);
    }
    //draw 4
    for (i = 0; i < 4; i++) {
      drawCard(currentPlayer, state);
    }
    //other players discard hand and redraw if hand size > 4
    for (i = 0; i < state->numPlayers; i++) {
      if (i != currentPlayer) {
        if ( state->handCount[i] > 4 ) {
          //discard hand
          while( state->handCount[i] > 0 ) {
            discardCard(handPos, i, state, 0);
          }
          //draw 4
          for (j = 0; j < 4; j++) {
            drawCard(i, state);
          }
        }
      }
    }
  }
  return 0;
}

/**
 * Effect for cutpurse card
 *   +2 treausre
 *   other payers discard a copper or reveal hand with none
 * @param  handPos  - position of card played
 * @param  state    - state of game
 * @return          - success value
 */
int effect_cutpurse(int handPos, struct gameState *state) {
  int currentPlayer = whoseTurn(state);
  int i, j, k;
  updateCoins(currentPlayer, state, 2);
  for (i = 0; i < state->numPlayers; i++) {
    if (i == currentPlayer) { //BUG: should be !=
      for (j = 0; j < state->handCount[i]; j++) {
        if (state->hand[i][j] == copper) {
          discardCard(j, i, state, 0);
          break;
        }
        if (j == state->handCount[i]) {
          for (k = 0; k < state->handCount[i]; k++) {
            if (DEBUG)
              printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
          }
          break;
        }
      }
    }
  }
  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}
