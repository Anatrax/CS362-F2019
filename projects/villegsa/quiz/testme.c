#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    char randomChar = (rand() % (128 - 32)) + 32;
    return randomChar;
}

/*
 * Code sections with percentage comments are for
 * making certain random values more probable
 * and therefore more likely to be tested
 * and will be tested more often they would normally
 * be tested if the choosing was completely random.
 */
char *inputString(char *randomString)
{
    // 0.0001% of the time, return the string "reset"
    // (on average once every 1,000,000 iterations)
    if(!(rand() % 1000000))
    {
	    randomString = calloc(6,sizeof(char));
	    strcpy(randomString,"reset");
	    return randomString;
    }

    // Get a random length string up to 20 characters long
    int randomStringLength = rand() % 20;
 
    // 90% of the time, set the string length to 5
    if(rand() % 10)
	    randomStringLength = 5;

    // Allocate space for the characters
    randomString = calloc(randomStringLength, sizeof(char));

    // Loop through the string
    int i = 0;
    for(;i<randomStringLength;i++) {
	    // Pick a random printable ascii character
	    randomString[i] = (rand() % (128 - 32)) + 32;

	    // 50% of the time, replace character with a capital letter
	    if(rand() % 2)
		    randomString[i] = (rand() % (('Z' - 1) - 'A')) + 'A';
	    // 80% of the time, replace character with a lowercase letter
	    if(rand() % 5)
		    randomString[i] = (rand() % (('z' - 1) - 'a')) + 'a';
    }
    randomString[i] = '\0';
    return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString(s);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
    free(s);
    s = NULL;
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
