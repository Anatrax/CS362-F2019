/*
 * @brief Minion card effect function tests
 * @author Samuel D. Villegas
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int assert_num = 0;
void assertEqual(int a, int b)
{
  if (!(a == b))
    printf("Assertion %d failed: %d == %d\n", assert_num, a, b);
  else
    printf("Assertion %d passed!\n", assert_num);
  assert_num++;
}
void assertNotEqual(int a, int b)
{
  if (!(a != b))
    printf("Assertion %d failed: %d != %d\n", assert_num, a, b);
  else
    printf("Assertion %d passed!\n", assert_num);
  assert_num++;
}

void test1()
{
  printf("Running Test 1...\n");

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
  memset(&G, 0, sizeof(struct gameState));
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
  int handPos = 0;
  G.hand[currentPlayer][handPos] = minion;
  int actions = G.numActions;

  minionCard(-1, -1, &G, handPos, currentPlayer);
  assertEqual(G.numActions, actions + 1); // Assert that number of buys increases
}

void test2()
{
  printf("Running Test 2...\n");

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
  memset(&G, 0, sizeof(struct gameState));
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
  int handPos = 0;
  G.hand[currentPlayer][handPos] = minion;
  int actions = G.numActions;

  minionCard(-1, -1, &G, handPos, currentPlayer); // Call function
  assertEqual(G.numActions, actions + 1);         // Assert that number of buys increases
}

int main()
{
  printf("Testing playMinion():\n");

  test1();
  test2();

  printf("Tests for playMinion() completed!\n\n");

  return 0;
}