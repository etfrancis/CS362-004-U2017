/*
 * cardtest4.c
 *
 * Testing adventurer card
 
 */
/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "adventurer"

int main() {

    //adventurer variables
    int temphand[MAX_HAND];
    int drawntreasure=0;
    int cardDrawn = 0;
    int z = 0;
    
    //general game variables
    
    int handpos = -1;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards. Gain adventurer card to hand
    initializeGame(numPlayers, k, seed, &G);
    
    gainCard(adventurer, &G, 2, thisPlayer);
    handpos = G.handCount[thisPlayer] -1;

	printf("\n----------------- Testing Card:  %s ----------------\n", TESTCARD);

	// ----------- TEST 1:  --------------
	printf("\nTEST 1: normal deck with sufficient copper (starting conditions)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	int result = playAdventurer(thisPlayer, &testG, handpos);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    int handstartingTreasure = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == copper || G.hand[thisPlayer][i] == silver || G.hand[thisPlayer][i] == gold)
            handstartingTreasure++;
    
    int handendingTreasure = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
            handendingTreasure++;
    printf("ending hand treasure = %d, expected = %d\n", handendingTreasure, handstartingTreasure + 2);
    
    int deckstartingTreasure = 0;
    for(int i = 0; i < G.deckCount[thisPlayer]; i++)
        if ( G.deck[thisPlayer][i] == copper || G.deck[thisPlayer][i] == silver || G.deck[thisPlayer][i] == gold)
            deckstartingTreasure++;
    
    int deckendingTreasure = 0;
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        if ( testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold)
            deckendingTreasure++;
    printf("ending deck treasure = %d, expected = %d\n", deckendingTreasure, deckstartingTreasure - 2);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);

    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, "Deck count test");
	MYASSERT(handendingTreasure == handstartingTreasure + 2, "Hand treasure test");
    MYASSERT(deckendingTreasure == deckstartingTreasure - 2, "Deck treasure test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(result == 0, "Return val is 0");
    
    // ----------- TEST 2:  --------------
    printf("\nTEST 2: empty deck, cards moved to discard pile\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++){
        testG.discard[thisPlayer][testG.discardCount[thisPlayer]++] = testG.deck[thisPlayer][i];
            }
    testG.deckCount[thisPlayer] = 0;
	result = playAdventurer(thisPlayer, &testG, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    handstartingTreasure = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == copper || G.hand[thisPlayer][i] == silver || G.hand[thisPlayer][i] == gold)
            handstartingTreasure++;
    
    handendingTreasure = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
            handendingTreasure++;
    printf("ending hand treasure = %d, expected = %d\n", handendingTreasure, handstartingTreasure + 2);
    
    deckstartingTreasure = 0;
    for(int i = 0; i < G.deckCount[thisPlayer]; i++)
        if ( G.deck[thisPlayer][i] == copper || G.deck[thisPlayer][i] == silver || G.deck[thisPlayer][i] == gold)
            deckstartingTreasure++;
    
    deckendingTreasure = 0;
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        if ( testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold)
            deckendingTreasure++;
    printf("ending deck treasure = %d, expected = %d\n", deckendingTreasure, deckstartingTreasure - 2);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, "Deck count test");
    MYASSERT(handendingTreasure == handstartingTreasure + 2, "Hand treasure test");
    MYASSERT(deckendingTreasure == deckstartingTreasure - 2, "Deck treasure test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(result == 0, "Return val is 0");
    
    
    // ----------- TEST 3:  --------------
    printf("\nTEST 3: deck without any treasure\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    //replace all treasure with provinces
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++){
        if(testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold)
        {
            testG.deck[thisPlayer][i] = province;
        }
    }
    
    for(int i = 0; i < testG.handCount[thisPlayer]; i++){
        if(testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
        {
            testG.hand[thisPlayer][i] = province;
        }
    }
    
    for(int i = 0; i < testG.discardCount[thisPlayer]; i++){
        if(testG.discard[thisPlayer][i] == copper || testG.discard[thisPlayer][i] == silver || testG.discard[thisPlayer][i] == gold)
        {
            testG.discard[thisPlayer][i] = province;
        }
    }
    
    handstartingTreasure = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
            handstartingTreasure++;
    
    deckstartingTreasure = 0;
    for(int i = 0; i < G.deckCount[thisPlayer]; i++)
        if ( testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold)
            deckstartingTreasure++;
    
	result = playAdventurer(thisPlayer, &testG, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 0);
    
    handendingTreasure = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
            handendingTreasure++;
    printf("ending hand treasure = %d, expected = %d\n", handendingTreasure, handstartingTreasure);

    
    deckendingTreasure = 0;
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        if ( testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold)
            deckendingTreasure++;
    printf("ending deck treasure = %d, expected = %d\n", deckendingTreasure, deckstartingTreasure);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == 0, "Deck count test");
    MYASSERT(handendingTreasure == handstartingTreasure, "Hand treasure test");
    MYASSERT(deckendingTreasure == deckstartingTreasure, "Deck treasure test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    
    
    // ----------- TEST 4:  --------------
    printf("\nTEST 4: normal deck with all copper replaced with gold\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        if(testG.deck[thisPlayer][i] == copper)
            testG.deck[thisPlayer][i] = gold;
    
	result = playAdventurer(thisPlayer, &testG, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    handstartingTreasure = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == copper || G.hand[thisPlayer][i] == silver || G.hand[thisPlayer][i] == gold)
            handstartingTreasure++;
    
    handendingTreasure = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
            handendingTreasure++;
    printf("ending hand treasure = %d, expected = %d\n", handendingTreasure, handstartingTreasure + 2);
    
    deckstartingTreasure = 0;
    for(int i = 0; i < G.deckCount[thisPlayer]; i++)
        if ( G.deck[thisPlayer][i] == copper || G.deck[thisPlayer][i] == silver || G.deck[thisPlayer][i] == gold)
            deckstartingTreasure++;
    
    deckendingTreasure = 0;
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        if ( testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold)
            deckendingTreasure++;
    printf("ending deck treasure = %d, expected = %d\n", deckendingTreasure, deckstartingTreasure - 2);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, "Deck count test");
    MYASSERT(handendingTreasure == handstartingTreasure + 2, "Hand treasure test");
    MYASSERT(deckendingTreasure == deckstartingTreasure - 2, "Deck treasure test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(result == 0, "Return val is 0");
    
    
    // ----------- TEST 5:  --------------
    printf("\nTEST 5: normal deck with all copper replaced with silver\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        if(testG.deck[thisPlayer][i] == copper)
            testG.deck[thisPlayer][i] = silver;
    
	result = playAdventurer(thisPlayer, &testG, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    handstartingTreasure = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == copper || G.hand[thisPlayer][i] == silver || G.hand[thisPlayer][i] == gold)
            handstartingTreasure++;
    
    handendingTreasure = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
            handendingTreasure++;
    printf("ending hand treasure = %d, expected = %d\n", handendingTreasure, handstartingTreasure + 2);
    
    deckstartingTreasure = 0;
    for(int i = 0; i < G.deckCount[thisPlayer]; i++)
        if ( G.deck[thisPlayer][i] == copper || G.deck[thisPlayer][i] == silver || G.deck[thisPlayer][i] == gold)
            deckstartingTreasure++;
    
    deckendingTreasure = 0;
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        if ( testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold)
            deckendingTreasure++;
    printf("ending deck treasure = %d, expected = %d\n", deckendingTreasure, deckstartingTreasure - 2);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1, "Hand count test");
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, "Deck count test");
    MYASSERT(handendingTreasure == handstartingTreasure + 2, "Hand treasure test");
    MYASSERT(deckendingTreasure == deckstartingTreasure - 2, "Deck treasure test");
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    MYASSERT(result == 0, "Return val is 0");




	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


