/*
 * cardtest3.c
 *
 * Testing mine card
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "mine"

int main() {

    //general game variables
    int handpos = -1, choice1 = 0, choice2 = 0;
    int seed = 2;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards. Discard a copper and replace with mine card in hand.
    
	initializeGame(numPlayers, k, seed, &G);


    gainCard(mine, &G, 2, thisPlayer);
    handpos = G.handCount[thisPlayer] -1;
    
    for(int i = 0; i < G.handCount[thisPlayer]; i++){
        if(G.hand[thisPlayer][i] == copper){
            choice1 = i;
            break;
        }
    }

    
    
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1:  --------------
	printf("TEST 1: valid choice1, valid choice2\n");
    

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    
    choice2 = silver;
    
    mine_effect(&testG, choice1, choice2, thisPlayer, handpos);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    int handstartingchoice2 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == choice2)
            handstartingchoice2++;
    
    int handendingchoice2 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == choice2)
            handendingchoice2++;
    printf("ending hand choice2 = %d, expected = %d\n", handendingchoice2, handstartingchoice2 + 1);
    
    int handstartingchoice1 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handstartingchoice1++;
    
    int handendingchoice1 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handendingchoice1++;
    printf("ending hand choice1 = %d, expected = %d\n", handendingchoice1, handstartingchoice1 - 1);
    
    printf("ending count2 supply count = %d, expected = %d\n", testG.supplyCount[choice2], G.supplyCount[choice2] - 1);

    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1, "Hand count test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
	MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    
    MYASSERT(handendingchoice1 == handstartingchoice1 - 1, "Choice1 in hand reduced by 1 test");
    
    MYASSERT(handendingchoice2 == handstartingchoice2 + 1, "Choice2 in hand increased by 1 test");
    
    MYASSERT(testG.supplyCount[choice2] == G.supplyCount[choice2] - 1, "Choice2 in supply decreased by 1 test");
    
    
    
    // ----------- TEST 2:  --------------
    printf("\nTEST 2: choice1 < copper, valid choice2\n");
    
    
    G.hand[thisPlayer][choice1] = province;
    choice2 = silver;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    
    int returnval = mine_effect(&testG, choice1, choice2, thisPlayer, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
    
    handstartingchoice2 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == choice2)
            handstartingchoice2++;
    
    handendingchoice2 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == choice2)
            handendingchoice2++;
    printf("ending hand choice2 = %d, expected = %d\n", handendingchoice2, handstartingchoice2);
    
    handstartingchoice1 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handstartingchoice1++;
    
    handendingchoice1 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handendingchoice1++;
    printf("ending hand choice1 = %d, expected = %d\n", handendingchoice1, handstartingchoice1);
    
    printf("ending count2 supply count = %d, expected = %d\n", testG.supplyCount[choice2], G.supplyCount[choice2]);
    
    printf("return val = %d, expected %d\n", returnval, -1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount, "Played card count test");
    
    MYASSERT(handendingchoice1 == handstartingchoice1, "Choice1 in hand unchanged test");
    
    MYASSERT(handendingchoice2 == handstartingchoice2, "Choice2 in hand unchanged test");
    
    MYASSERT(testG.supplyCount[choice2] == G.supplyCount[choice2], "Choice2 in supply not changed test");
    
    MYASSERT(returnval == -1, "Return val -1 test");
    
    
    
    // ----------- TEST 3:  --------------
    printf("\nTEST 3: choice1 > gold, valid choice2\n");
    
    G.hand[thisPlayer][choice1] = adventurer;
    choice2 = silver;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    returnval = mine_effect(&testG, choice1, choice2, thisPlayer, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
    
    handstartingchoice2 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == choice2)
            handstartingchoice2++;
    
    handendingchoice2 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == choice2)
            handendingchoice2++;
    printf("ending hand choice2 = %d, expected = %d\n", handendingchoice2, handstartingchoice2);
    
    handstartingchoice1 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handstartingchoice1++;
    
    handendingchoice1 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handendingchoice1++;
    printf("ending hand choice1 = %d, expected = %d\n", handendingchoice1, handstartingchoice1);
    
    printf("ending count2 supply count = %d, expected = %d\n", testG.supplyCount[choice2], G.supplyCount[choice2]);
    
    printf("return val = %d, expected %d\n", returnval, -1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount, "Played card count test");
    
    MYASSERT(handendingchoice1 == handstartingchoice1, "Choice1 in hand unchanged test");
    
    MYASSERT(handendingchoice2 == handstartingchoice2, "Choice2 in hand unchanged test");
    
    MYASSERT(testG.supplyCount[choice2] == G.supplyCount[choice2], "Choice2 in supply not changed test");
    
    MYASSERT(returnval == -1, "Return val -1 test");
    
    
    // ----------- TEST 4:  --------------
    printf("\nTEST 4: choice1 valid, choice2 < copper\n");
    
    G.hand[thisPlayer][choice1] = copper;
    choice2 = duchy;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    returnval = mine_effect(&testG, choice1, choice2, thisPlayer, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
    
    handstartingchoice2 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == choice2)
            handstartingchoice2++;
    
    handendingchoice2 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == choice2)
            handendingchoice2++;
    printf("ending hand choice2 = %d, expected = %d\n", handendingchoice2, handstartingchoice2);
    
    handstartingchoice1 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handstartingchoice1++;
    
    handendingchoice1 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handendingchoice1++;
    printf("ending hand choice1 = %d, expected = %d\n", handendingchoice1, handstartingchoice1);
    
    printf("ending count2 supply count = %d, expected = %d\n", testG.supplyCount[choice2], G.supplyCount[choice2]);
    
    printf("return val = %d, expected %d\n", returnval, -1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount, "Played card count test");
    
    MYASSERT(handendingchoice1 == handstartingchoice1, "Choice1 in hand unchanged test");
    
    MYASSERT(handendingchoice2 == handstartingchoice2, "Choice2 in hand unchanged test");
    
    MYASSERT(testG.supplyCount[choice2] == G.supplyCount[choice2], "Choice2 in supply not changed test");
    
    MYASSERT(returnval == -1, "Return val -1 test");
    
    
    
    
    // ----------- TEST 5:  --------------
    printf("\nTEST 5: choice1 valid, choice2 > gold\n");
    
    G.hand[thisPlayer][choice1] = gold;
    choice2 = adventurer;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    returnval = mine_effect(&testG, choice1, choice2, thisPlayer, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
    
    handstartingchoice2 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == choice2)
            handstartingchoice2++;
    
    handendingchoice2 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == choice2)
            handendingchoice2++;
    printf("ending hand choice2 = %d, expected = %d\n", handendingchoice2, handstartingchoice2);
    
    handstartingchoice1 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handstartingchoice1++;
    
    handendingchoice1 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handendingchoice1++;
    printf("ending hand choice1 = %d, expected = %d\n", handendingchoice1, handstartingchoice1);
    
    printf("ending count2 supply count = %d, expected = %d\n", testG.supplyCount[choice2], G.supplyCount[choice2]);
    
    printf("return val = %d, expected %d\n", returnval, -1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount, "Played card count test");
    
    MYASSERT(handendingchoice1 == handstartingchoice1, "Choice1 in hand unchanged test");
    
    MYASSERT(handendingchoice2 == handstartingchoice2, "Choice2 in hand unchanged test");
    
    MYASSERT(testG.supplyCount[choice2] == G.supplyCount[choice2], "Choice2 in supply not changed test");
    
    MYASSERT(returnval == -1, "Return val -1 test");
    
    
    
    
    // ----------- TEST 6:  --------------
    printf("\nTEST 6: choice1 valid, choice2 valid but too expensive\n");
    
    G.hand[thisPlayer][choice1] = copper;
    choice2 = gold;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    returnval = mine_effect(&testG, choice1, choice2, thisPlayer, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
    
    handstartingchoice2 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == choice2)
            handstartingchoice2++;
    
    handendingchoice2 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == choice2)
            handendingchoice2++;
    printf("ending hand choice2 = %d, expected = %d\n", handendingchoice2, handstartingchoice2);
    
    handstartingchoice1 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handstartingchoice1++;
    
    handendingchoice1 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handendingchoice1++;
    printf("ending hand choice1 = %d, expected = %d\n", handendingchoice1, handstartingchoice1);
    
    printf("ending count2 supply count = %d, expected = %d\n", testG.supplyCount[choice2], G.supplyCount[choice2]);
    
    printf("return val = %d, expected %d\n", returnval, -1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount, "Played card count test");
    
    MYASSERT(handendingchoice1 == handstartingchoice1, "Choice1 in hand unchanged test");
    
    MYASSERT(handendingchoice2 == handstartingchoice2, "Choice2 in hand unchanged test");
    
    MYASSERT(testG.supplyCount[choice2] == G.supplyCount[choice2], "Choice2 in supply not changed test");
    
    MYASSERT(returnval == -1, "Return val -1 test");
    
    
    
    // ----------- TEST 7:  --------------
    printf("\nTEST 7: choice1 valid and more expensive than choice2\n");
    
    G.hand[thisPlayer][choice1] = gold;
    choice2 = copper;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    mine_effect(&testG, choice1, choice2, thisPlayer, handpos);
    
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
    
    printf("deck count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
    
    handstartingchoice2 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == choice2)
            handstartingchoice2++;
    
    handendingchoice2 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == choice2)
            handendingchoice2++;
    printf("ending hand choice2 = %d, expected = %d\n", handendingchoice2, handstartingchoice2 + 1);
    
    handstartingchoice1 = 0;
    for(int i = 0; i < G.handCount[thisPlayer]; i++)
        if ( G.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handstartingchoice1++;
    
    handendingchoice1 = 0;
    for(int i = 0; i < testG.handCount[thisPlayer]; i++)
        if ( testG.hand[thisPlayer][i] == G.hand[thisPlayer][choice1])
            handendingchoice1++;
    printf("ending hand choice1 = %d, expected = %d\n", handendingchoice1, handstartingchoice1 - 1);
    
    printf("ending count2 supply count = %d, expected = %d\n", testG.supplyCount[choice2], G.supplyCount[choice2] - 1);
    
    
    MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1, "Hand count test");
    
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
    MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
    
    MYASSERT(handendingchoice1 == handstartingchoice1 - 1, "Choice1 in hand reduced by 1 test");
    
    MYASSERT(handendingchoice2 == handstartingchoice2 + 1, "Choice2 in hand increased by 1 test");
    
    MYASSERT(testG.supplyCount[choice2] == G.supplyCount[choice2] - 1, "Choice2 in supply decreased by 1 test");


    
	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


