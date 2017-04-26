CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

effects.o: dominion.h effects.c
	gcc -c effects.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o effects.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c effects.o
	gcc -o playdom playdom.c -g dominion.o rngs.o effects.o $(CFLAGS)

testUnits: unittest1.c unittest2.c unittest3.c unittest4.c test_util.c dominion.o rngs.o effects.o
	gcc -c test_util.c -g $(CFLAGS)
	gcc -o unittest1 -g unittest1.c test_util.o dominion.o rngs.o effects.o $(CFLAGS)
	gcc -o unittest2 -g unittest2.c test_util.o dominion.o rngs.o effects.o $(CFLAGS)
	gcc -o unittest3 -g unittest3.c test_util.o dominion.o rngs.o effects.o $(CFLAGS)
	gcc -o unittest4 -g unittest4.c test_util.o dominion.o rngs.o effects.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o effects.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o effects.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o effects.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o effects.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o effects.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o effects.o $(CFLAGS)

testAll: dominion.o testSuite.c effects.o
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o effects.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o effects.o $(CFLAGS)

all: playdom player testUnits testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
