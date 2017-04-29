CFLAGS = -Wall -fpic -coverage -lm -fprofile-arcs -ftest-coverage -g
O_FILES = dominion.o rngs.o effects.o
TEST_PATH = ./tests/
TEST_FILES = $(TEST_PATH)tests.h $(TEST_PATH)test_util.o

#######################################################################
#####################			BASE .o FILES				#########################
#######################################################################
rngs.o: rngs.c rngs.h
	gcc $(CFLAGS) -c -o $@ $<
effects.o: effects.c dominion.h
	gcc $(CFLAGS) -c -o $@ $<
dominion.o: dominion.c dominion.h rngs.o effects.o
	gcc $(CFLAGS) -c -o $@ $<
interface.o: interface.c interface.h
	gcc $(CFLAGS) -c -o $@ $<

#######################################################################
####################				GAMEPLAY					#########################
#######################################################################
playdom: playdom.c $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
player: player.c interface.o $(O_FILES)
	gcc $(CFLAGS) -o $@ $^

#######################################################################
#####################					TESTS						#########################
#######################################################################
##	Utility
test_util.o: $(TEST_PATH)test_util.c $(TEST_PATH)tests.h
	gcc $(CFLAGS) -c -o $(TEST_PATH)$@ $<
# clean
_tests = rm -f $(TEST_PATH)*.o $(TEST_PATH)*.gcov $(TEST_PATH)*.gcda $(TEST_PATH)*.gcno $(TEST_PATH)*.so && $(_unittests)

##	Game functions
# updateCoins
unittest1: $(TEST_PATH)unittest1.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest1: unittest1
	$(TEST_PATH)$< &> $@result.out
	gcov dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# discardCard
unittest2: $(TEST_PATH)unittest2.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest2: unittest2
	$(TEST_PATH)$< &> $@result.out
	gcov dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# playCard
unittest3: $(TEST_PATH)unittest3.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest3: unittest3
	$(TEST_PATH)$< &> $@result.out
	gcov -c dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# handCard
unittest4: $(TEST_PATH)unittest4.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest4: unittest4
	$(TEST_PATH)$< &> $@result.out
	gcov dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# build
unittests: unittest1 unittest2 unittest3 unittest4
# clean
_unittests = rm -f $(TEST_PATH)unittest1 $(TEST_PATH)unittest2 $(TEST_PATH)unittest3 $(TEST_PATH)unittest4

##	Cards
# TODO!

##	Old...
testDrawCard: testDrawCard.c $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
badTestDrawCard: badTestDrawCard.c $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
testBuyCard: testDrawCard.c $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
testAll: testSuite.c $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

#######################################################################
#####################					UTILITY					#########################
#######################################################################
all: playdom player testDrawCard testBuyCard badTestDrawCard unittests

clean:
	$(_tests)
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
