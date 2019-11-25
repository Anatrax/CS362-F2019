//gcc -g randomtestcard1.c dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include "dominion.h"

int assertEquals(char *fail_str, int value, int expected_value)
{
  if (value != expected_value)
  {
    printf("ERROR: %s\n", fail_str);
    return 0;
  }
  return 1;
}

void printGameState(struct gameState *G)
{
  printf("{\n");
  printf("\tnumPlayers: %d,\n", G->numPlayers);
  printf("\tsupplyCount: {");
  int i;
  for (i = 0; i < treasure_map + 1; i++)
  {
    printf("%d,", G->supplyCount[i]);
  }
  printf("}\n");
  printf("\tembargoTokens: {");
  for (i = 0; i < treasure_map + 1; i++)
  {
    printf("%d,", G->embargoTokens[i]);
  }
  printf("}\n");
  printf("\toutpostPlayed: %d,\n", G->outpostPlayed);
  printf("\toutpostTurn: %d,\n", G->outpostTurn);
  printf("\twhoseTurn: %d,\n", G->whoseTurn);
  printf("\tphase: %d,\n", G->phase);
  printf("\tnumActions: %d,\n", G->numActions);
  printf("\tcoins: %d,\n", G->coins);
  printf("\tnumBuys: %d,\n", G->numBuys);
  printf("\thand: {\n");
  for (i = 0; i < G->numPlayers; i++)
  {
    printf("\t\t{");
    int j;
    for (j = 0; j < G->handCount[i]; j++)
    {
      printf("%d,", G->hand[i][j]);
    }
    printf("},\n");
  }
  printf("\t}\n");
  printf("\thandCount: {");
  for (i = 0; i < G->numPlayers; i++)
  {
    printf("%d,", G->handCount[i]);
  }
  printf("}\n");
  printf("\tdeck: {\n");
  for (i = 0; i < G->numPlayers; i++)
  {
    printf("\t\t{");
    int j;
    for (j = 0; j < G->deckCount[i]; j++)
    {
      printf("%d,", G->deck[i][j]);
    }
    printf("},\n");
  }
  printf("\t}\n");
  printf("\tdeckCount: {");
  for (i = 0; i < G->numPlayers; i++)
  {
    printf("%d,", G->deckCount[i]);
  }
  printf("}\n");
  printf("\tdiscard: {\n");
  for (i = 0; i < G->numPlayers; i++)
  {
    printf("\t\t{");
    int j;
    for (j = 0; j < G->discardCount[i]; j++)
    {
      printf("%d,", G->discard[i][j]);
    }
    printf("},\n");
  }
  printf("\t}\n");
  printf("\tdiscardCount: {");
  for (i = 0; i < G->numPlayers; i++)
  {
    printf("%d,", G->discardCount[i]);
  }
  printf("}\n");
  printf("\tplayedCards: {");
  for (i = 0; i < G->playedCardCount; i++)
  {
    printf("%d,", G->playedCards[i]);
  }
  printf("}\n");
  printf("\tplayedCardCount: %d,\n", G->playedCardCount);
  printf("}\n");
}

void copyGameState(struct gameState *A, struct gameState *B)
{
  A->numPlayers = B->numPlayers; //number of players
  int i;
  for (i = 0; i < treasure_map + 1; i++)
  {
    A->supplyCount[i] = B->supplyCount[i];
  }
  for (i = 0; i < treasure_map + 1; i++)
  {
    A->embargoTokens[i] = B->embargoTokens[i];
  }
  A->outpostPlayed = B->outpostPlayed;
  A->outpostTurn = B->outpostTurn;
  A->whoseTurn = B->whoseTurn;
  A->phase = B->phase;
  A->numActions = B->numActions;
  A->coins = B->coins;
  A->numBuys = B->numBuys;
  for (i = 0; i < B->numPlayers; i++)
  {
    A->handCount[i] = B->handCount[i];
  }
  for (i = 0; i < B->numPlayers; i++)
  {
    int j;
    for (j = 0; j < B->handCount[i]; j++)
    {
      A->hand[i][j] = B->hand[i][j];
    }
  }
  for (i = 0; i < B->numPlayers; i++)
  {
    A->deckCount[i] = B->deckCount[i];
  }
  for (i = 0; i < B->numPlayers; i++)
  {
    int j;
    for (j = 0; j < B->deckCount[i]; j++)
    {
      A->deck[i][j] = B->deck[i][j];
    }
  }
  for (i = 0; i < B->numPlayers; i++)
  {
    A->discardCount[i] = B->discardCount[i];
  }
  for (i = 0; i < B->numPlayers; i++)
  {
    int j;
    for (j = 0; j < B->discardCount[i]; j++)
    {
      A->discard[i][j] = B->discard[i][j];
    }
  }
  A->playedCardCount = B->playedCardCount;
  for (i = 0; i < B->playedCardCount; i++)
  {
    A->playedCards[i] = B->playedCards[i];
  }
}

int compareArray(int *arr1, int arr1_size, int *arr2, int arr2_size)
{
  if (arr1_size != arr2_size)
    return 1;
  int i;
  for (i = 0; i < arr1_size; i++)
  {
    if (arr1[i] != arr2[i])
      return 1;
  }
  return 0;
}

int compare2DArray(int *arr1, int arr1_depth, int *arr1_lengths, int *arr2, int arr2_depth, int *arr2_lengths)
{
  if (arr1_depth != arr2_depth)
    return 1;
  int i;
  for (i = 0; i < arr1_depth; i++)
  {
    if (compareArray(&arr1[i], arr1_lengths[i], &arr2[i], arr2_lengths[i]) != 0)
      return 1;
  }
  return 0;
}

int checkExpectedTributeState(struct gameState *prev, struct gameState *cur, int currentPlayer, int nextPlayer)
{
  if (!assertEquals("numPlayers modified", prev->numPlayers, cur->numPlayers))
    return 1;
  if (!assertEquals("outpostPlayed modified", prev->outpostPlayed, cur->outpostPlayed))
    return 1;
  if (!assertEquals("outpustTurn modified", prev->outpostTurn, cur->outpostTurn))
    return 1;
  if (!assertEquals("whoseTurn modified", prev->whoseTurn, cur->whoseTurn))
    return 1;
  if (!assertEquals("phase modified", prev->phase, cur->phase))
    return 1;
  if (!assertEquals("numActions modified", prev->numActions, cur->numActions))
    return 1;
  if (!assertEquals("coins modified", prev->coins, cur->coins))
    return 1;
  if (!assertEquals("numBuys modified", prev->numBuys, cur->numBuys))
    return 1;
  if (!assertEquals("playedCardCount modified", prev->playedCardCount, cur->playedCardCount))
    return 1;
  if (!assertEquals("supplyCount modified", compareArray(prev->supplyCount, treasure_map + 1, cur->supplyCount, treasure_map + 1), 0))
    return 1;
  if (!assertEquals("embargoTokens modified", compareArray(prev->embargoTokens, treasure_map + 1, cur->embargoTokens, treasure_map + 1), 0))
    return 1;
  if (!assertEquals("decks modified", compare2DArray(prev->deck, prev->numPlayers, prev->deckCount, cur->deck, cur->numPlayers, cur->deckCount), 0))
    return 1;
  if (!assertEquals("discard piles modified", compare2DArray(prev->discard, prev->numPlayers, prev->discardCount, cur->discard, cur->numPlayers, prev->discardCount), 0))
    return 1;

  // Apply expected changes to previous state
  prev->handCount[currentPlayer]--;
  prev->playedCards[prev->playedCardCount] = tribute;
  prev->playedCardCount++;
  //
  // Check that the previous state now matches the current state
  if (!assertEquals("hands modified", compare2DArray(prev->hand, prev->numPlayers, prev->handCount, cur->hand, cur->numPlayers, prev->handCount), 0))
    return 1;
  if (!assertEquals("playedCards modified", compareArray(prev->playedCards, prev->playedCardCount, cur->playedCards, cur->playedCardCount), 0))
    return 1;
  return 0;
}

int randRanged(int start_inclusive, int end_inclusive)
{
  if (end_inclusive < start_inclusive)
  {
    end_inclusive = start_inclusive;
  }
  int random_from_range = (rand() % (end_inclusive - start_inclusive + 1)) + start_inclusive;
  return random_from_range;
}

void randArray(int random_array[], int size)
{
  int i = 0;
  for (; i < size; i++)
  {
    random_array[i] = rand();
  }
}

void randArrayRanged(int random_array_from_range[], int size, int min_element, int max_element)
{
  if (min_element > max_element)
    return;
  int i = 0;
  for (; i < size; i++)
  {
    random_array_from_range[i] = randRanged(min_element, max_element);
  }
}

void shuffleArray(int *array, size_t n)
{
  if (n > 1)
  {
    size_t i;
    for (i = 0; i < n - 1; i++)
    {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void randGameState(struct gameState *G)
{
  G->numPlayers = randRanged(2, 4);

  //set number of Curse cards in supply
  if (G->numPlayers == 2)
  {
    G->supplyCount[curse] = randRanged(0, 10);
  }
  else if (G->numPlayers == 3)
  {
    G->supplyCount[curse] = randRanged(0, 20);
  }
  else
  {
    G->supplyCount[curse] = randRanged(0, 30);
  }

  //set number of Victory cards in supply
  if (G->numPlayers == 2)
  {
    G->supplyCount[estate] = randRanged(0, 8);
    G->supplyCount[duchy] = randRanged(0, 8);
    G->supplyCount[province] = randRanged(0, 8);
  }
  else
  {
    G->supplyCount[estate] = randRanged(0, 12);
    G->supplyCount[duchy] = randRanged(0, 12);
    G->supplyCount[province] = randRanged(0, 12);
  }

  //set number of Treasure cards in supply
  G->supplyCount[copper] = randRanged(0, 60 - (7 * G->numPlayers));
  G->supplyCount[silver] = randRanged(0, 40);
  G->supplyCount[gold] = randRanged(0, 30);

  //set number of Kingdom cards in supply
  int card = treasure_map;
  int includeCard[treasure_map + 1] = {0};
  int i = 0;
  for (; i < 10; i++)
  {
    includeCard[i] = 1;
  }
  shuffleArray(includeCard, treasure_map + 1);

  int kingdomCardsLeftToChoose = 10;
  int kingdomCards[kingdomCardsLeftToChoose];
  for (; kingdomCardsLeftToChoose > 0; card--)
  {
    if (includeCard[card])
    {
      kingdomCards[kingdomCardsLeftToChoose - 1] = card;
      kingdomCardsLeftToChoose--;
    }
  }

  int j;
  for (i = adventurer; i <= treasure_map; i++)
  {
    for (j = 0; j < 10; j++) //loop chosen cards
    {
      if (kingdomCards[j] == i)
      {
        //check if card is a 'Victory' Kingdom card
        if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
        {
          if (G->numPlayers == 2)
          {
            G->supplyCount[i] = 8;
          }
          else
          {
            G->supplyCount[i] = 12;
          }
        }
        else
        {
          G->supplyCount[i] = 10;
        }
        break;
      }
      else //card is not in the set choosen for the game
      {
        G->supplyCount[i] = -1;
      }
    }
  }
  randArray(G->embargoTokens, treasure_map + 1);
  G->outpostPlayed = randRanged(0, G->supplyCount[outpost]);
  G->outpostTurn = randRanged(0, G->numPlayers);
  G->whoseTurn = randRanged(0, G->numPlayers);
  G->phase = rand();
  G->numActions = 1; /* Starts at 1 each turn */
  G->coins = randRanged(0, MAX_DECK);
  G->numBuys = 1; /* Starts at 1 each turn */

  randArrayRanged(G->handCount, G->numPlayers, 0, MAX_HAND);
  int currentPlayer = 0;
  for (; currentPlayer < G->numPlayers; currentPlayer++)
  {
    randArrayRanged(G->hand[currentPlayer], G->handCount[currentPlayer], curse, treasure_map);
  }

  randArrayRanged(G->deckCount, G->numPlayers, 0, MAX_HAND);
  if (rand() % 9)
    randArrayRanged(G->deckCount, G->numPlayers, 0, 0);
  currentPlayer = 0;
  for (; currentPlayer < G->numPlayers; currentPlayer++)
  {
    randArrayRanged(G->deck[currentPlayer], G->deckCount[currentPlayer], curse, treasure_map);
  }

  randArrayRanged(G->discardCount, G->numPlayers, 0, MAX_HAND);
  if (rand() % 3)
    randArrayRanged(G->discardCount, G->numPlayers, 1, 1);
  currentPlayer = 0;
  for (; currentPlayer < G->numPlayers; currentPlayer++)
  {
    randArrayRanged(G->discard[currentPlayer], G->discardCount[currentPlayer], curse, treasure_map);
  }

  G->playedCardCount = randRanged(0, MAX_DECK);
  randArrayRanged(G->playedCards, G->playedCardCount, curse, treasure_map);
}

int tributeRandomTest(struct gameState *state)
{
  randGameState(state);
  int currentPlayer = randRanged(0, 4);
  int nextPlayer = (currentPlayer + 1) % state->numPlayers;

  // Record previous state
  struct gameState previousState;
  copyGameState(&previousState, state); // needs to be deep copy

  // Call Tribute function
  int result = tributeCard(state, nextPlayer, currentPlayer);
  if (result != 0)
  {
    printf("Function Returned Non-Zero Value: %d\n", result);
    // TODO: assert if failure was expected
    return 1;
  }
  else if (checkExpectedTributeState(&previousState, state, currentPlayer, nextPlayer) != 0) // needs to be deep comparison
  {
    printf("Test Failed:\n");
    printf("\tCurrent Player: %d\n", currentPlayer);
    printf("\tNext Player: %d\n", nextPlayer);
    printf("\tPrevious State: ");
    printGameState(&previousState);
    printf("\tCurrent State: ");
    printGameState(state);
  }
  return 0;
}

int main()
{
  //set up random number generator
  srand(0);
  SelectStream(2);
  PutSeed(3);

  printf("Testing tribute card...\n");
  struct gameState G;
  int i = 0;
  for (; i < 100; i++)
    tributeRandomTest(&G);
  printf("Done.\n");
  return 0;
}