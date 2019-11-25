CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

test: unittestresults randomtestresults

unittestresults: unittest1.c dominion.o rngs.o
	gcc -o unittest1.out -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2.out -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3.out -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4.out -g unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest5.out -g unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest1.out > unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	./unittest2.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	./unittest3.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	./unittest4.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	./unittest5.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out

randomtestresults: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o interface.o
	gcc -o randomtestcard1.out randomtestcard1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	./randomtestcard1.out > randomtestresults.out
	gcov -bf dominion.c >> randomtestresults.out
	gcc -o randomtestcard2.out randomtestcard2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	./randomtestcard2.out >> randomtestresults.out
	gcov -bf dominion.c >> randomtestresults.out
	gcc -o randomtestcard3.out randomtestcard3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	./randomtestcard3.out >> randomtestresults.out
	gcov -bf dominion.c >> randomtestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
