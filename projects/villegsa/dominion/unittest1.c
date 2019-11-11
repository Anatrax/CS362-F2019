/*
 * @brief Baron card effect function tests
 * @author Samuel D. Villegas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include "dominion.h"

int assert_num = 0;
void assertEqual(int a, int b)
{
  if (!(a == b))
    printf("Assertion %d failed: %d == %d\n", assert_num, a, b);
  else
    //printf("Assertion %d passed!\n", assert_num);
    assert_num++;
}
void assertNotEqual(int a, int b)
{
  if (!(a != b))
    printf("Assertion %d failed: %d != %d\n", assert_num, a, b);
  else
    //printf("Assertion %d passed!\n", assert_num);
    assert_num++;
}

void testIncreasesBuysBy1()
{
  //printf("Testing if number of buys are increased by 1...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               feast,
               gardens,
               mine,
               remodel,
               smithy,
               village,
               baron,
               great_hall};
  struct gameState G;
  int handCount = 5;
  int numPlayers = 2;
  int seed = 1000;
  int currentPlayer = 0;

  // Reset game state & initialize new game
  memset(&G, -1, sizeof(struct gameState));
  int result = initializeGame(numPlayers, k, seed, &G);

  // Create arrays of all coppers, silvers, and golds
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  int i;
  for (i = 0; i < MAX_HAND; i++)
  {
    coppers[i] = copper;
    silvers[i] = silver;
    golds[i] = gold;
  }
  // Initialize currentPlayer's hand with all coppers
  memcpy(G.hand[currentPlayer], (void *)coppers, sizeof(int) * handCount);

  // Set up test variables
  int buys = G.numBuys;

  playBaron(&G, -1, currentPlayer); // Call function
  assertEqual(G.numBuys, buys + 1); // Assert that number of buys increases
}

void testDiscardingEstateIncreasesPlayersCoinsBy4()
{
  //printf("Testing if discarding an estate gains the player 4 coin...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               feast,
               gardens,
               mine,
               remodel,
               smithy,
               village,
               baron,
               great_hall};
  struct gameState G;
  int handCount = 5;
  int numPlayers = 2;
  int seed = 1000;
  int currentPlayer = 0;

  // Reset game state & initialize new game
  memset(&G, -1, sizeof(struct gameState));
  int result = initializeGame(numPlayers, k, seed, &G);

  // Create arrays of all coppers, silvers, and golds
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  int i;
  for (i = 0; i < MAX_HAND; i++)
  {
    coppers[i] = copper;
    silvers[i] = silver;
    golds[i] = gold;
  }
  // Initialize currentPlayer's hand with all coppers
  memcpy(G.hand[currentPlayer], (void *)coppers, sizeof(int) * handCount);

  // Set up test variables
  int discardEstate = 1;
  int coins = G.coins;
  G.hand[currentPlayer][0] = estate;

  // Call function with option to discard an estate
  playBaron(&G, discardEstate, currentPlayer);

  // Assert that coins increases by 4
  assertEqual(G.coins, coins + 4);
}

void testGainCard()
{
  //printf("Testing if player gains a card when not discarding an estate...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               feast,
               gardens,
               mine,
               remodel,
               smithy,
               village,
               baron,
               great_hall};
  struct gameState G;
  int numPlayers = 2;
  int seed = 1000;
  int handCount = 5;
  int currentPlayer = 0;

  // Reset game state & initialize new game
  memset(&G, -1, sizeof(struct gameState));
  int result = initializeGame(numPlayers, k, seed, &G);

  // arrays of all coppers, silvers, and golds
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  int i;
  for (i = 0; i < MAX_HAND; i++)
  {
    coppers[i] = copper;
    silvers[i] = silver;
    golds[i] = gold;
  }
  // Initialize currentPlayer's hand with all coppers
  memcpy(G.hand[currentPlayer], (void *)coppers, sizeof(int) * handCount);

  // Set up test variables
  int discardEstate = 1;
  int gainEstate = !discardEstate;
  int coins = G.coins;

  // Call function with option to gain an estate
  playBaron(&G, gainEstate, currentPlayer);

  // Assert that player gained a card
  assertEqual(G.handCount[currentPlayer], handCount + 1);

  // Assert that gained card is an estate
  assertEqual(G.hand[currentPlayer][G.handCount[currentPlayer] - 1], estate);
}

void testGainEstate()
{
  //printf("Testing if the card the player gains when not discarding an estate is an estate...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               feast,
               gardens,
               mine,
               remodel,
               smithy,
               village,
               baron,
               great_hall};
  struct gameState G;
  int numPlayers = 2;
  int seed = 1000;
  int handCount = 5;
  int currentPlayer = 0;

  // Reset game state & initialize new game
  memset(&G, -1, sizeof(struct gameState));
  int result = initializeGame(numPlayers, k, seed, &G);

  // arrays of all coppers, silvers, and golds
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  int i;
  for (i = 0; i < MAX_HAND; i++)
  {
    coppers[i] = copper;
    silvers[i] = silver;
    golds[i] = gold;
  }
  // Initialize currentPlayer's hand with all coppers
  memcpy(G.hand[currentPlayer], (void *)coppers, sizeof(int) * handCount);

  // Set up test variables
  int discardEstate = 1;
  int gainEstate = !discardEstate;
  int coins = G.coins;

  // Call function with option to gain an estate
  playBaron(&G, gainEstate, currentPlayer);

  // Assert that gained card is an estate
  assertEqual(G.hand[currentPlayer][G.handCount[currentPlayer] - 1], estate);
}

void test4()
{
  printf("Testing if discarded estate is no longer in player's hand...\n");

  int seed = 1000;
  int handCount = 5;
  int k[10] = {adventurer,
               council_room,
               feast,
               gardens,
               mine,
               remodel,
               smithy,
               village,
               baron,
               great_hall};
  struct gameState G;
  int numPlayers = 2;
  int discardEstate = 1;
  int currentPlayer = 0;
  G.handCount[currentPlayer] = handCount;
  G.hand[currentPlayer][0] = estate;

  // Reset game state & initialize new game
  // initialized to zero to differentiate between
  // an originally empty value
  // and a value explicitly marked as empty
  memset(&G, 0, sizeof(struct gameState));
  int result = initializeGame(numPlayers, k, seed, &G);

  // arrays of all coppers, silvers, and golds
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  int i;
  for (i = 0; i < MAX_HAND; i++)
  {
    coppers[i] = copper;
    silvers[i] = silver;
    golds[i] = gold;
  }
  // Initialize currentPlayer's hand with all coppers
  memcpy(G.hand[currentPlayer], (void *)coppers, sizeof(int) * handCount);

  // Set up test variables
  int estateIndex = G.handCount[currentPlayer] - 1;
  G.hand[currentPlayer][estateIndex] = estate;

  // Call function
  result = playBaron(&G, discardEstate, currentPlayer);

  // Assert that the removed index is set to -1
  assertEqual(G.hand[currentPlayer][estateIndex], -1);
}

int main()
{
  printf("Testing playBaron():\n");

  testIncreasesBuysBy1();
  testDiscardingEstateIncreasesPlayersCoinsBy4();
  testGainEstate();
  test4();

  printf("Tests for playBaron() completed!\n\n");
  return 0;
}