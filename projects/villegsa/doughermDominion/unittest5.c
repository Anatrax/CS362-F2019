/*
 * @brief Mine card effect function tests
 * @author Samuel D. Villegas
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int assert_num = 0;
void assert(int a, int b)
{
  if (a == b)
    printf("Assertion %d failed: %d != %d", assert_num, a, b);
  else
    printf("Assertion %d passed!", assert_num);
  assert_num++;
}

// Initialize variables
struct gameState G;

// Call refactored functions
playMine(&G, int choice1, int choice2, int currentPlayer, int handPos);

// Assert the results