/*
 * cardtest2.c
 *
 * Testing council_room card
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "council_room"

int main() {
    
    //general game variables

    int handpos = -1;
    int seed = 2;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards. Draw council_room to hand
    
	initializeGame(numPlayers, k, seed, &G);

    gainCard(council_room, &G, 2, thisPlayer);
    handpos = G.handCount[thisPlayer] -1;
    
    
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1:  --------------
	printf("\nTEST 1: normal start with five cards in hand and deck \n");
    

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    
    council_room_effect(thisPlayer, &testG, handpos);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
    
    for(int i = 1; i < numPlayers; i++)
        printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
    
    for(int i = 1; i < numPlayers; i++)
	printf("deck count for other player %d = %d, expected = %d\n", i, testG.deckCount[i], G.deckCount[i] - 1);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
    
    printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 3, "Hand count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.handCount[i] == G.handCount[i] + 1, "Other player handcount increased test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 4, "Deck count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.deckCount[i] == G.deckCount[i] - 1, "Other player deckcount decreased test");
    
    
	MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
    MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");
    
    
    // ----------- TEST 2:  --------------
    printf("\nTEST 2: only three cards in deck \n");
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisPlayer] = 3;
    
    council_room_effect(thisPlayer, &testG, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
    
    for(int i = 1; i < numPlayers; i++)
        printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 0);
    
    for(int i = 1; i < numPlayers; i++)
        printf("deck count for other player %d = %d, expected = %d\n", i, testG.deckCount[i], G.deckCount[i] - 1);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
    
    printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "Hand count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.handCount[i] == G.handCount[i] + 1, "Other player handcount increased test");
    
    MYASSERT(testG.deckCount[thisPlayer] == 0, "Deck count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.deckCount[i] == G.deckCount[i] - 1, "Other player deckcount decreased test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
    MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");
    
    
    // ----------- TEST 3:  --------------
    printf("\nTEST 3: four cards in deck \n");
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisPlayer] = 4;
    
    council_room_effect(thisPlayer, &testG, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
    
    for(int i = 1; i < numPlayers; i++)
        printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 0);
    
    for(int i = 1; i < numPlayers; i++)
        printf("deck count for other player %d = %d, expected = %d\n", i, testG.deckCount[i], G.deckCount[i] - 1);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
    
    printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 3, "Hand count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.handCount[i] == G.handCount[i] + 1, "Other player handcount increased test");
    
    MYASSERT(testG.deckCount[thisPlayer] == 0, "Deck count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.deckCount[i] == G.deckCount[i] - 1, "Other player deckcount decreased test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
    MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");
    
    
    
    // ----------- TEST 4:  --------------
    printf("\nTEST 4: normal deck for current player, other players have empty decks \n");
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for(int i = 0; i < numPlayers; i++){
        if( i != thisPlayer){
            testG.deckCount[i] = 0;
        }
    }
    
    council_room_effect(thisPlayer, &testG, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
    
    for(int i = 1; i < numPlayers; i++)
        printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i]);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
    
    for(int i = 1; i < numPlayers; i++)
        printf("deck count for other player %d = %d, expected = %d\n", i, testG.deckCount[i], 0);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
    
    printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 3, "Hand count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.handCount[i] == G.handCount[i], "Other player handcount increased test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] -4, "Deck count test");
    
    for(int i = 1; i < numPlayers; i++)
        MYASSERT(testG.deckCount[i] == 0, "Other player deckcount decreased test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
    MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");

    
    
	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


