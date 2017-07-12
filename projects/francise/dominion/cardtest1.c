/*
 * cardtest1.c
 *
 * Testing smithy card
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define MYASSERT(statement, message) do \
{ \
if(!(statement)) \
{ \
fprintf(stderr, "Assert failed: %s\n", message);\
} \
else \
{ \
fprintf(stderr, "Assert passed: %s\n", message);\
} \
}while(0)

#define TESTCARD "smithy"

int main() {

    //general game variables

    int handpos = -1;
    int seed = 2;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards. Discard a copper and replace with smithy card in hand.
    
	initializeGame(numPlayers, k, seed, &G);

    for(int i = 0; i < G.handCount[thisPlayer]; i++){
        if(G.hand[thisPlayer][i] == copper){
            G.hand[thisPlayer][i] = smithy;
            handpos = i;
            break;
        }
    }

    G.discard[thisPlayer][G.discardCount[thisPlayer]] = copper;
    G.discardCount[thisPlayer]++;
    
    
	printf("----------------- Testing Card: Hand, deck, played card changes for %s ----------------\n", TESTCARD);

	// ----------- TEST 1:  --------------
	printf("TEST 1: \n");
    

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    
    smithy_effect(thisPlayer, handpos, &testG);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3, "Deck count test");
	MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount -1] == smithy, "Played card last added test");
    
	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


