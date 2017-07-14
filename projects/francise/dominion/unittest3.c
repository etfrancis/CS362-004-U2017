/*
 * unittest3.c
 *
 * Testing updateCoins(int player, struct gameState *state, int bonus)
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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

#define TESTFUNCTION "updateCoins"

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
    
    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // ----------- TEST 1:  --------------
    printf("TEST 1: All copper hand\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(int i = 0; i <testG.handCount[thisPlayer]; i++ ){
        testG.hand[thisPlayer][i] = copper;
    }
    
    int result = updateCoins(thisPlayer, &testG, 0); //no bonus
    
    
    printf("result = %d, expected = %d\n", testG.coins, testG.handCount[thisPlayer] * 1);
    MYASSERT(testG.coins == testG.handCount[thisPlayer] * 1, "Add one to coin count per copper");
    MYASSERT(result == 0, "Result is 0");
    
    
    // ----------- TEST 2:  --------------
    printf("TEST 2: All silver hand\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(int i = 0; i <testG.handCount[thisPlayer]; i++ ){
        testG.hand[thisPlayer][i] = silver;
    }
    
    result = updateCoins(thisPlayer, &testG, 0); //no bonus
    
    
    printf("result = %d, expected = %d\n", testG.coins, testG.handCount[thisPlayer] * 2);
    MYASSERT(testG.coins == testG.handCount[thisPlayer] * 2, "Add two to coin count per copper");
    MYASSERT(result == 0, "Result is 0");
    
    
    // ----------- TEST 3:  --------------
    printf("TEST 3: All gold hand\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(int i = 0; i <testG.handCount[thisPlayer]; i++ ){
        testG.hand[thisPlayer][i] = gold;
    }
    
    result = updateCoins(thisPlayer, &testG, 0); //no bonus
    
    
    printf("result = %d, expected = %d\n", testG.coins, testG.handCount[thisPlayer] * 3);
    MYASSERT(testG.coins == testG.handCount[thisPlayer] * 3, "Add three to coin count per copper");
    MYASSERT(result == 0, "Result is 0");
    
    
    // ----------- TEST 4:  --------------
    printf("TEST 4: Hand does not contain treasure\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(int i = 0; i <testG.handCount[thisPlayer] ; i++ ){
        testG.hand[thisPlayer][i] = province;
    }
    
    result = updateCoins(thisPlayer, &testG, 0); //no bonus
    
    
    printf("result = %d, expected = %d\n", testG.coins, testG.handCount[thisPlayer] * 0);
    MYASSERT(testG.coins == testG.handCount[thisPlayer] * 0, "Coin count is zero");
    MYASSERT(result == 0, "Result is 0");
    
    
    
    // ----------- TEST 5:  --------------
    printf("TEST 5: Hand does not contain treasure, but there is a bonus\n");
    
    // copy the game state to a test case
    
    
    for(int j = 1; j <= 3; j++){
        memcpy(&testG, &G, sizeof(struct gameState));
        
        for(int i = 0; i <testG.handCount[thisPlayer] ; i++ ){
            testG.hand[thisPlayer][i] = province;
        }
        
    result = updateCoins(thisPlayer, &testG, j); //with bonus, 1-3
    
    printf("result = %d, expected = %d\n", testG.coins, testG.handCount[thisPlayer] * 0 + j);
    MYASSERT(testG.coins == testG.handCount[thisPlayer] * 0 + j, "Coin count is increased correctly reflecting bonus");
    MYASSERT(result == 0, "Result is 0");
        
    }
    
    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);

    return 0;
}


