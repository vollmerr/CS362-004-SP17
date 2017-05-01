CFLAGS = -Wall -fpic -coverage -lm -fprofile-arcs -ftest-coverage -g
O_FILES = dominion.o rngs.o effects.o

TEST_PATH = ./tests/
TEST_FILES = $(TEST_PATH)tests.h $(TEST_PATH)test_util.o
TEST_TYPE = -b

T_CARD = cardtest1 cardtest2 cardtest3 cardtest4
T_UNIT = unittest1 unittest2 unittest3 unittest4
T_ALL = $(T_CARD) $(T_UNIT)

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
#############	Utility
test_util.o: $(TEST_PATH)test_util.c $(TEST_PATH)tests.h
	gcc $(CFLAGS) -c -o $(TEST_PATH)$@ $<
# run all tests

gcov_all: $(T_ALL)
	echo "" > unittestresult.out
	@for n in $(T_UNIT); do $(TEST_PATH)$$n &>> unittestresult.out; done
	gcov $(TEST_TYPE) dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	@for n in $(T_CARD); do $(TEST_PATH)$$n &>> unittestresult.out; done
	gcov $(TEST_TYPE) effects.c >> unittestresult.out
	cat effects.c.gcov >> unittestresult.out

# clean
_tests = cd $(TEST_PATH) && rm -f *.o *.gcov *.gcda *.gcno *.so && $(_unittests) && $(_cardtests) && cd ../

############# Game functions
# updateCoins
unittest1: $(TEST_PATH)unittest1.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest1: unittest1
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# discardCard
unittest2: $(TEST_PATH)unittest2.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest2: unittest2
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# playCard
unittest3: $(TEST_PATH)unittest3.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest3: unittest3
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# handCard
unittest4: $(TEST_PATH)unittest4.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest4: unittest4
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) dominion.c >> $@result.out
	cat dominion.c.gcov >> $@result.out
# build
unittests: $(T_UNIT)
# clean
_unittests = rm -f $(T_UNIT)

############# Cards
# adventurer
cardtest1: $(TEST_PATH)cardtest1.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest1: cardtest1 effects.c
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) effects.c >> $@result.out
	cat effects.c.gcov >> $@result.out
# council room
cardtest2: $(TEST_PATH)cardtest2.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest2: cardtest2 effects.c
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) effects.c >> $@result.out
	cat effects.c.gcov >> $@result.out
# smithy
cardtest3: $(TEST_PATH)cardtest3.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest3: cardtest3 effects.c
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) effects.c >> $@result.out
	cat effects.c.gcov >> $@result.out
# minion
cardtest4: $(TEST_PATH)cardtest4.c $(TEST_FILES) $(O_FILES)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest4: cardtest4 effects.c
	$(TEST_PATH)$< &> $@result.out
	gcov $(TEST_TYPE) effects.c >> $@result.out
	cat effects.c.gcov >> $@result.out
# build
cardtests: $(T_CARD)
# clean
_cardtests = rm -f $(T_CARD)

############# Old...
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
all: playdom player testDrawCard testBuyCard badTestDrawCard unittests cardtests

clean:
	$(_tests)
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
