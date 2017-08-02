/*
 * unittest4.c
 *
 * Testing gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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

#define TESTFUNCTION "gainCard"

int main() {
    
    //general game variables
    
    int seed = 2;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // initialize a game state and player cards.
    
    initializeGame(numPlayers, k, seed, &G);
    
    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // ----------- TEST 1:  --------------
    printf("\nTEST 1: Gain to hand, discard, or deck when supply is empty or card is unused, check return value -1\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.supplyCount[adventurer] = 0;
    testG.supplyCount[mine] = -1;
    
    for(int i = 0; i <= 2; i++){
    int result = gainCard(adventurer, &testG, 0, thisPlayer);
    	printf("result for gain to location %d = %d, expected = %d\n", i, result, -1);
    	MYASSERT(result == -1, "Result is -1 after trying to gain card from empty supply");
        MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count unchanged after trying to gain card from empty supply");
        MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count unchanged after trying to gain card from empty supply");
        MYASSERT(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], "Discard count is unchanged after trying to gain card from empty supply");
    
    	result = gainCard(mine, &testG, 0, thisPlayer);
    	printf("result for gain to location %d = %d, expected = %d\n", i, result, -1);
        MYASSERT(result == -1, "Result is -1 after trying to gain card that is not used this game");
        MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count unchanged after trying to gain card from empty supply");
        MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count unchanged after trying to gain card from empty supply");
        MYASSERT(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], "Discard count is unchanged after trying to gain card from empty supply");
    }
    
    // ----------- TEST 2:  --------------
    printf("\nTEST 2: Gain to discard, deck, hand when card available (check each card type and gain destination)\n");
    
    for(int i = 0; i <= 2; i++){
            for(int j = 0; j < 10; j++){
                
            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));
            
        	int result = gainCard(k[j], &testG, i, thisPlayer);
        	printf("result for gain of card %d to location %d = %d, expected = %d\n", k[j], i, result, 0);
        	MYASSERT(result == 0, "Result is 0 after successful gain");
            if(i == 0){
                MYASSERT(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1, "Discard count is increased after gain to discard");
                MYASSERT(testG.discard[thisPlayer][testG.discardCount[thisPlayer] -1] == k[j], "Correct card gained to discard pile");
                MYASSERT(testG.supplyCount[k[j]] == G.supplyCount[k[j]] - 1, "Supply for correct card decreased by 1");
                for(int m = 0; m < 10; m++){
                    if(m != j)
		                MYASSERT(testG.supplyCount[k[m]] == G.supplyCount[k[m]], "Supply for other cards unchanged");}
                MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count unchanged");
                MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count unchanged");
            }
            else if(i == 1){
                MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + 1, "Deck count is increased after gain to deck");
                MYASSERT(testG.deck[thisPlayer][testG.deckCount[thisPlayer] - 1 ] == k[j], "Correct card gained to deck");
                MYASSERT(testG.supplyCount[k[j]] == G.supplyCount[k[j]] - 1, "Supply for correct card decreased by 1");
                for(int m = 0; m < 10; m++){
                    if(m != j)
                        MYASSERT(testG.supplyCount[k[m]] == G.supplyCount[k[m]], "Supply for other cards unchanged");}
                MYASSERT(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], "Discard count is unchanged ");
                MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Hand count unchanged");
            }
            else if(i == 2){
                MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1, "Hand count is increased after gain to hand");
                MYASSERT(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1 ] == k[j], "Correct card gained to hand");
                MYASSERT(testG.supplyCount[k[j]] == G.supplyCount[k[j]] - 1, "Supply for correct card decreased by 1");
                for(int m = 0; m < 10; m++){
                    if(m != j)
                		MYASSERT(testG.supplyCount[k[m]] == G.supplyCount[k[m]], "Supply for other cards unchanged");}
                MYASSERT(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], "Discard count is unchanged ");
                MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count unchanged");
            }
        }
    }
    
    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);

    return 0;
}


