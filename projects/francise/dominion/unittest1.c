/*
 * unittest1.c
 *
 * Testing isGameOver(struct gameState *state)
 */
/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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

#define TESTFUNCTION "isGameOver"

int main() {
    
    //general game variables
    
    int seed = 2;
    int numPlayers = 2;
    //int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // initialize a game state and player cards.
    
    initializeGame(numPlayers, k, seed, &G);
    
    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // ----------- TEST 1:  --------------
    printf("\nTEST 1: Province supply count set to 0\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.supplyCount[province] = 0;
    
    int result = isGameOver(&testG);
    
    printf("result = %d, expected = %d\n", result, 1);
    
    MYASSERT(result == 1, "Function returns 1 when province supply count is 0");
    
    
    // ----------- TEST 2:  --------------
    printf("\nTEST 2: Province supply count > 0, three supply piles set to 0 \n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.supplyCount[adventurer] = 0;
    testG.supplyCount[embargo] = 0;
    testG.supplyCount[village] = 0;
    
    result = isGameOver(&testG);
    
    printf("result = %d, expected = %d\n", result, 1);
    
    MYASSERT(result == 1, "Function returns 1 when three supply counts are 0");
    
    
    // ----------- TEST 3:  --------------
    printf("\nTEST 3: Province supply count == 0, three supply piles set to 0 \n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.supplyCount[province] = 0;
    testG.supplyCount[adventurer] = 0;
    testG.supplyCount[embargo] = 0;
    testG.supplyCount[village] = 0;
    
    result = isGameOver(&testG);
    
    printf("result = %d, expected = %d\n", result, 1);
    
    MYASSERT(result == 1, "Function returns 1 when province and three supply counts are 0");
    

    // ----------- TEST 4:  --------------
    printf("\nTEST 4: Province supply count > 0, all supply piles > 0 \n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    result = isGameOver(&testG);
    
    printf("result = %d, expected = %d\n", result, 0);
    
    MYASSERT(result == 0, "Function returns 0 when province and three supply counts are above 0");
    
    
    // ----------- TEST 5:  --------------
    printf("\nTEST 5: Province supply count > 0, all supply piles > 0 \n");
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for (int i = 1; i<= 60; i++){
        testG.supplyCount[province] = i;
    
    result = isGameOver(&testG);
    
    printf("result = %d, expected = %d\n", result, 0);
    
    MYASSERT(result == 0, "Function returns 0 when province and three supply counts are above 0, for province count 1-60 (max supply)");

    }
    
    // ----------- TEST 6:  --------------
    printf("\nTEST 6: Any three supply piles  == 0 \n");
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
            for (int k = 0; k< 25; k++){
                if(k != j && j != i && i != k){
                memcpy(&testG, &G, sizeof(struct gameState));
                testG.supplyCount[i] = 0;
                testG.supplyCount[j] = 0;
                testG.supplyCount[k] = 0;
                result = isGameOver(&testG);
                printf("result = %d, expected = %d, i = %d, j = %d, k = %d\n", result, 1, i, j, k);
                MYASSERT(result == 1, "Function returns 1 when any three supply counts are 0");
                }
            }
        }
    }
    
    // ----------- TEST 7:  --------------
    printf("\nTEST 7: Any three supply piles  == 0 \n");
    
    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
            for (int k = 0; k< 25; k++){
                if(k != j && j != i && i != k){
                    memcpy(&testG, &G, sizeof(struct gameState));
                    testG.supplyCount[i] = 0;
                    testG.supplyCount[j] = 0;
                    testG.supplyCount[k] = 0;
                    result = isGameOver(&testG);
                    printf("result = %d, expected = %d, i = %d, j = %d, k = %d\n", result, 1, i, j, k);
                    MYASSERT(result == 1, "Function returns 1 when any three supply counts are 0");
                }
            }
        }
    }
    
    // ----------- TEST 8:  --------------
    printf("\nTEST 8: Any two supply piles  == 0 \n");
    
    for (int i = 0; i< 25; i++){
        for (int j = 0; j< 25; j++){
                if(i != j && i != province && j != province){
                    memcpy(&testG, &G, sizeof(struct gameState));
                    testG.supplyCount[i] = 0;
                    testG.supplyCount[j] = 0;
                    result = isGameOver(&testG);
                    printf("result = %d, expected = %d, i = %d, j = %d\n", result, 0, i, j);
                    MYASSERT(result == 0, "Function returns 0 when only any two supply counts are 0");
                }
            }
        }
    
    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);

    return 0;
}


