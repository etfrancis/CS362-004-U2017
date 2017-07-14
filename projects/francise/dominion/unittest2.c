/*
 * unittest2.c
 *
 * Testing shuffle(int player, struct gameState *state)
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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

#define TESTFUNCTION "shuffle"

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
    printf("TEST 1: Full deck from starting conditions\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    int result = shuffle(thisPlayer, &testG);
    
    if(testG.deckCount[thisPlayer] > 0){
    	printf("result = %d, expected = %d\n", result, 0);
    	MYASSERT(result == 0, "Function returns 0 when shuffling deck with more than 0 cards");
    }
    
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    MYASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck count test");
    
    
    int startingCards[25];
    int postCards[25];
    
    for(int i = 0; i < 25; i++){
        startingCards[i] = 0;
        postCards[i] = 0;
    }
    
    for(int i = 0; i < G.deckCount[thisPlayer]; i++)
        startingCards[G.deck[thisPlayer][i]]++;
    
    for(int i = 0; i < testG.deckCount[thisPlayer]; i++)
        postCards[testG.deck[thisPlayer][i]]++;
    
    for(int i = 0; i < 25; i++)
    {
        MYASSERT(startingCards[i] == postCards[i], "Deck contents identical test");
    }
    
    // ----------- TEST 2:  --------------
    printf("TEST 2: Empty deck \n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisPlayer] = 0;
    
    result = shuffle(thisPlayer, &testG);
    printf("result = %d, expected = %d\n", result, -1);
    MYASSERT(result == -1, "Function returns -1 when shuffling empty deck");
    
    // ----------- TEST 3:  --------------
    printf("TEST 3: Full deck from starting conditions -- show that other decks are unaffected\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    result = shuffle(thisPlayer, &testG);
    
    for(int i = 0; i < numPlayers; i++){
        if(i != thisPlayer){
            printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
            MYASSERT(testG.deckCount[i] == G.deckCount[i], "Deck count test for other players");
            if(testG.deckCount[i] == G.deckCount[i]){
                for(int j = 0; j<testG.deckCount[i]; j++)
                    MYASSERT(testG.deck[i][j] == G.deck[i][j], "Deck contents identical and same order");
            }
    	}
    }

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);

    return 0;
}


