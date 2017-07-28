/*
 * randomtestcard2.c
 *
 * Testing council_room card
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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

    int seed = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards. Add smithy to hand.
    
    // randomize game state and player cards.
    
    //set up random number generator
    SelectStream(1);
    PutSeed((long)seed);
    

    
    //run test multiple times in a loop
    for(int i = 0; i < 10000; i++){
        
    int supplyCount[treasure_map+1];
    int inGameCount[treasure_map+1];
        
    //set number of players between 2-MAX (four for this game)
    int numPlayers = floor(Random() * (MAX_PLAYERS - 2)) + 2; //at least two players
	
    
    //set all supplyCount to -1 by default, to indicate card not in game
    for(int i = 0; i <= treasure_map + 1; i++){
        supplyCount[i] = -1;
        inGameCount[i] = 0;}
    
    
    //reset supply and inGame for all selected kingdom cards to a random amount, from 0 to 10
    for(int i = 0; i < 10; i++){
        int cardSupply = floor(Random() * (10 + 1));
        supplyCount[k[i]] = cardSupply;
        inGameCount[k[i]] = 10 - cardSupply;
    }
    
    //set all victory cards supply to random amount from 0 to 8 if players = 2, or from 0 to 12 if players > 2
    int victorycards = 12;
    if(numPlayers == 2)
        victorycards = 8;
    for(int i = duchy; i <= province; i++){
        supplyCount[i] = floor(Random() * (victorycards + 1));
        inGameCount[i] = victorycards - supplyCount[i];}
    supplyCount[estate] = floor(Random() * (victorycards - (3*numPlayers) + 1)); // account for cards automatically in starting hard
    inGameCount[estate] = victorycards - supplyCount[estate];
    
    //set curses supply to max 10 if 2 players, plus 2 for every additional 2 players
    int numCurses = 10 + 10 * (numPlayers - 2)/2;
    supplyCount[curse] = floor(Random() * (numCurses + 1));
    inGameCount[curse] = numCurses - supplyCount[curse];
    
    //set treasures supply to random amount up to max, reserving 7*numPlayers copper for starting hands
    int numCopper = 60 - 7 * numPlayers; // account for cards automatically in starting hard
    int numSilver = 40;
    int numGold = 30;
    supplyCount[copper] = floor(Random() * (numCopper + 1));
    inGameCount[copper] = numCopper - supplyCount[copper];
    
    supplyCount[silver] = floor(Random() * (numSilver + 1));
    inGameCount[silver] = numSilver - supplyCount[silver];
    
    supplyCount[gold] = floor(Random() * (numGold + 1));
    inGameCount[gold] = numGold - supplyCount[gold];
    
    int whoseTurn = floor(Random() * numPlayers); //randomize current player
    int phase = 0; //let phase be 0, to allow cards to be played
    int outpostPlayed = floor(Random() * 2); //randomize outpost played
    int outpostTurn =  floor(Random() * 2); //randomize outpost played
    int numActions = floor(Random() * 5); //randomize number of actions
    int coins = floor(Random() * 10); //randomize number of coins
    int numBuys = floor(Random() * 5); //randomize number of buys
    
    //set default embargo tokens, played count to 0
    int embargoTokens[treasure_map+1];
    for(int i = 0; i <= treasure_map; i++)
        embargoTokens[i] = 0;
    int embargoPlayed = 0;
    
    //if embargo in play, update embargo tokens and played count to random amount up to 10
    if(supplyCount[embargo] != -1){
        int embargoInPlay = 10 - supplyCount[embargo];
        embargoPlayed = floor(Random() * (embargoInPlay + 1));
        inGameCount[embargo] = inGameCount[embargo] - embargoPlayed;
        
        for(int i = 0; i < embargoPlayed; i++){
        	int embargoCardIndex = floor(Random() * (10));
            embargoTokens[k[embargoCardIndex]]++;
        }
    }
    
    //allocate each card in play to a random player to create each player's deck, discard, and hand pool.
    bool allCardsAllocated = false;
    int playerCards[MAX_PLAYERS][MAX_DECK];
    int playerCardCount[MAX_PLAYERS];
    
    //assignment 7 copper and 3 estates to each player
    for(int i = 0; i < numPlayers; i++){
        playerCardCount[i] = 10;
    	for(int j = 0; j < 7; j++)
        	playerCards[i][j] = copper;
        for(int k = 7; k < 10; k++)
            playerCards[i][k] = estate;}
    
    //assignment of remaining in-play cards to each player
    while(!allCardsAllocated){
        bool movedCard = false;
        for(int i = 0; i <= treasure_map; i++){
            if(inGameCount[i] > 0){
                int selectedPlayer = floor(Random() * numPlayers);
                playerCards[selectedPlayer][playerCardCount[selectedPlayer]] = i;
                playerCardCount[selectedPlayer]++;
                inGameCount[i]--;
                movedCard = true;}
            }
        if(movedCard == false)
          allCardsAllocated = true;
    }
    
    //distribute cards in each player's allocation to their hand, deck, and discard pile
    int hand[MAX_PLAYERS][MAX_HAND];
    int handCount[MAX_PLAYERS];
    int deck[MAX_PLAYERS][MAX_DECK];
    int deckCount[MAX_PLAYERS];
    int discard[MAX_PLAYERS][MAX_DECK];
    int discardCount[MAX_PLAYERS];
    for(int i = 0; i < numPlayers; i++){
        handCount[i] = deckCount[i] = discardCount[i] = 0;
        while(playerCardCount[i] > 0){
            int destination = floor(Random() * 4); //bump range to 4 to increase chance of populating deck, rather than hand or discard
            int card = floor(Random() * playerCardCount[i]);
            switch(destination){
                case 0:
                    hand[i][handCount[i]] = playerCards[i][card];
                    handCount[i]++;
                    break;
                case 1:
                    deck[i][deckCount[i]] = playerCards[i][card];
                    deckCount[i]++;
                    break;
                case 2:
                    deck[i][deckCount[i]] = playerCards[i][card];
                    deckCount[i]++;
                    break;
                case 3:
                    discard[i][discardCount[i]] = playerCards[i][card];
                    discardCount[i]++;
                    break;
            }
            for (int j = card; j < playerCardCount[i]-1; j++) {
                playerCards[i][j] = playerCards[i][j+1];}
            playerCardCount[i]--;
        }
    }

    //transfer data to game state
    G.numPlayers = numPlayers;
    for(int i = 0; i <= treasure_map; i++){
        G.supplyCount[i] = supplyCount[i];
        G.embargoTokens[i] = embargoTokens[i];}
    G.outpostPlayed = outpostPlayed;
    G.outpostTurn = outpostTurn;
    G.whoseTurn = whoseTurn;
    G.phase = phase;
    G.numActions = numActions;
    G.coins = coins;
    G.numBuys = numBuys;
    for(int i = 0; i < MAX_PLAYERS; i++){
        G.handCount[i] = handCount[i];
        G.discardCount[i] = discardCount[i];
        G.deckCount[i] = deckCount[i];
        for(int j = 0; j < MAX_DECK; j++)
        {
            G.hand[i][j] = hand[i][j];
            G.deck[i][j] = deck[i][j];
            G.discard[i][j] = discard[i][j];
        }
    }
    
    //set played cards to zero for now
    for(int i = 0; i < MAX_DECK; i++)
        G.playedCards[i] = 0;
    G.playedCardCount = 0;
    

    //select starting player
    int thisPlayer = G.whoseTurn;
        
    //for council_room, adjust random starting conditions to ensure that deckcount is below 4 with some frequency
        if(floor(Random() * (100)) > 90){ //10% chance
            while((G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) > 4){
                G.deckCount[thisPlayer] /= 2;
                G.discardCount[thisPlayer] /= 2;
            }}
        else if(floor(Random() * (100)) > 90){ //10% chance
                while((G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) > 3){
                    G.deckCount[thisPlayer] /= 2;
                    G.discardCount[thisPlayer] /= 2;
                }}
        else if(floor(Random() * (100)) > 90){ //10% chance
                while((G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) > 2){
                    G.deckCount[thisPlayer] /= 2;
                    G.discardCount[thisPlayer] /= 2;
                }}
        else if(floor(Random() * (100)) > 90){ //10% chance
                while((G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) > 1){
                    G.deckCount[thisPlayer] /= 2;
                    G.discardCount[thisPlayer] /= 2;
                }}
            
        
    //start game with council_room in hand
	G.supplyCount[council_room]++;
    gainCard(council_room, &G, 2, thisPlayer);
    int handpos = G.handCount[thisPlayer] -1;
    
    
	printf("\n----------------- Testing Card: %s, Trial %d ----------------\n", TESTCARD, i);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    
    int result = council_room_effect(thisPlayer, &testG, handpos);

    if(G.deckCount[thisPlayer] + G.discardCount[thisPlayer] >= 4){
        
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
        for(int i = 1; i < numPlayers; i++)
            printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
        printf("deck and discard count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 4);
        for(int i = 1; i < numPlayers; i++)
            printf("deck and discard count for other player %d = %d, expected = %d\n", i, testG.deckCount[i] + testG.discardCount[i], G.discardCount[i] + G.deckCount[i] - 1);
        printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
        printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
        printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
        
        MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 3, "Hand count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.handCount[i] == G.handCount[i] + 1, "Other player handcount increased test");
        MYASSERT(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] == G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 4, "Deck count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.deckCount[i] + testG.discardCount[i] == G.deckCount[i] + G.discardCount[i] - 1, "Other player deckcount decreased test");
        
        MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
        MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
        MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");
        MYASSERT(result == 0, "Return val is 0");

    }
    else if(G.deckCount[thisPlayer] + G.discardCount[thisPlayer] == 3){
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
        for(int i = 1; i < numPlayers; i++)
            printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
        printf("deck and discard count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 3);
        for(int i = 1; i < numPlayers; i++)
            printf("deck and discard count for other player %d = %d, expected = %d\n", i, testG.deckCount[i] + testG.discardCount[i], G.discardCount[i] + G.deckCount[i] - 1);
        printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
        printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
        printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
        
        MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "Hand count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.handCount[i] == G.handCount[i] + 1, "Other player handcount increased test");
        MYASSERT(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] == G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 3, "Deck count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.deckCount[i] + testG.discardCount[i] == G.deckCount[i] + G.discardCount[i] - 1, "Other player deckcount decreased test");
        MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
        MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
        MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");
        MYASSERT(result == 0, "Return val is 0");
	}
    else if(G.deckCount[thisPlayer] + G.discardCount[thisPlayer] == 2){
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
        for(int i = 1; i < numPlayers; i++)
            printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
        printf("deck and discard count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 2);
        for(int i = 1; i < numPlayers; i++)
            printf("deck and discard count for other player %d = %d, expected = %d\n", i, testG.deckCount[i] + testG.discardCount[i], G.discardCount[i] + G.deckCount[i] - 1);
        printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
        printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
        printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
        
        MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1, "Hand count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.handCount[i] == G.handCount[i] + 1, "Other player handcount increased test");
        MYASSERT(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] == G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 2, "Deck count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.deckCount[i] + testG.discardCount[i] == G.deckCount[i] + G.discardCount[i] - 1, "Other player deckcount decreased test");
        MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
        MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
        MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");
        MYASSERT(result == 0, "Return val is 0");
        
    }
    else if(G.deckCount[thisPlayer] + G.discardCount[thisPlayer] == 1){
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 0);
        for(int i = 1; i < numPlayers; i++)
            printf("hand count for other player %d = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
        printf("deck and discard count for current player = %d, expected = %d\n",  testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 1);
        for(int i = 1; i < numPlayers; i++)
            printf("deck and discard count for other player %d = %d, expected = %d\n", i, testG.deckCount[i] + testG.discardCount[i], G.discardCount[i] + G.deckCount[i] - 1);
        printf("ending played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);
        printf("ending played card is council_room = %d, expected = %d\n", testG.playedCards[testG.playedCardCount -1], council_room);
        printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
        
        MYASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 0, "Hand count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.handCount[i] == G.handCount[i] + 1, "Other player handcount increased test");
        MYASSERT(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] == G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 1, "Deck count test");
        for(int i = 1; i < numPlayers; i++)
            MYASSERT(testG.deckCount[i] + testG.discardCount[i] == G.deckCount[i] + G.discardCount[i] - 1, "Other player deckcount decreased test");
        MYASSERT(testG.playedCardCount == G.playedCardCount + 1, "Played card count test");
        MYASSERT(testG.playedCards[testG.playedCardCount - 1] == council_room, "Played card last added test");
        MYASSERT(testG.numBuys == G.numBuys + 1, "Num Buys increased test");
        MYASSERT(result == 0, "Return val is 0");
    }
    
	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    }
	return 0;
}


