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
fprintf(stdout, "Assert failed: %s\n", message);\
} \
else \
{ \
fprintf(stdout, "Assert passed: %s\n", message);\
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

	// initialize a game state and player cards. Add smithy to hand.
    
	initializeGame(numPlayers, k, seed, &G);

    gainCard(smithy, &G, 2, thisPlayer);
    handpos = G.handCount[thisPlayer] -1;
    
    
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1:  --------------
	printf("\nTEST 1: Using deck with at least 3 cards in it\n");
    

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    
    int result = smithy_effect(thisPlayer, handpos, &testG);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3, "Deck count test");
	MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount -1] == smithy, "Played card last added test");
    MYASSERT(result == 0, "Return val is 0");
    
    // ----------- TEST 2:  --------------
    printf("\nTEST 2: Using deck with no cards in it\n");
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisPlayer] = 0; //set deck size to 0
    
    result = smithy_effect(thisPlayer, handpos, &testG);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] -1, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == 0, "Deck count test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount -1] == smithy, "Played card last added test");
    MYASSERT(result == 0, "Return val is 0");
           

           
    // ----------- TEST 3:  --------------
    printf("\nTEST 3: Using deck with two cards in it\n");
           
           
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisPlayer] = 2; //set deck size to 2
           
    result = smithy_effect(thisPlayer, handpos, &testG);
           
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] +1);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 0);
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
                  
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == 0, "Deck count test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount -1] == smithy, "Played card last added test");
    MYASSERT(result == 0, "Return val is 0");
           
           
    // ----------- TEST 4:  --------------
    printf("\nTEST 4: Using deck with three cards in it\n");
           
           
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisPlayer] = 3; //set deck size to 3
           
    result = smithy_effect(thisPlayer, handpos, &testG);
           
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 0);
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
                  
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == 0, "Deck count test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount -1] == smithy, "Played card last added test");
    MYASSERT(result == 0, "Return val is 0");
           

           
    // ----------- TEST 5:  --------------
    printf("\nTEST 5: Using deck with four cards in it\n");
           
           
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisPlayer] = 4; //set deck size to 4
           
    result = smithy_effect(thisPlayer, handpos, &testG);
           
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 1);
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
                  
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == 1, "Deck count test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount -1] == smithy, "Played card last added test");
    MYASSERT(result == 0, "Return val is 0");
    
    
	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


