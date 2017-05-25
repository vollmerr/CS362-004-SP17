CC = gcc
CFLAGS = -Wall -fpic -coverage -lm -fprofile-arcs -ftest-coverage -g
OBJ = dominion.o rngs.o

TEST_PATH = ./tests/
TEST_FILES = $(TEST_PATH)tests.h $(TEST_PATH)test_util.o
TEST_TYPE = -b

T_CARD = cardtest1 cardtest2 cardtest3 cardtest4
T_CARD_R = randomtestcard1 randomtestcard2 randomtestadventurer
T_UNIT = unittest1 unittest2 unittest3 unittest4
T_ALL = $(T_CARD) $(T_UNIT)

define runtest =
$(TEST_PATH)$(word 2, $^) &> $@result.out
gcov $(TEST_TYPE) $< >> $@result.out
cat $<.gcov >> $@result.out
endef


#######################################################################
#####################			BASE .o FILES				#########################
#######################################################################
rngs.o: rngs.h
dominion.o: dominion.h rngs.o
interface.o: interface.h

#######################################################################
####################				GAMEPLAY					#########################
#######################################################################
playdom: playdom.c $(OBJ)
player: player.c interface.o $(OBJ)

#######################################################################
#####################					TESTS						#########################
#######################################################################
#############	Utility
test_util.o: $(TEST_PATH)test_util.c $(TEST_PATH)tests.h
	gcc $(CFLAGS) -c -o $(TEST_PATH)$@ $<
# run all tests

gcov_all: $(T_ALL)
	echo "" > unittestresult.out
	@for n in $(T_ALL); do $(TEST_PATH)$$n &>> unittestresult.out; done
	gcov $(TEST_TYPE) dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

# clean
_tests = cd $(TEST_PATH) && rm -f *.o *.gcov *.gcda *.gcno *.so && $(_unittests) && $(_cardtests) && $(_randomcardtests) && cd ../

############# Game functions
# updateCoins
unittest1: $(TEST_PATH)unittest1.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest1: dominion.c unittest1
	$(runtest)
# discardCard
unittest2: $(TEST_PATH)unittest2.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest2: dominion.c unittest2
	$(runtest)
# playCard
unittest3: $(TEST_PATH)unittest3.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest3: dominion.c unittest3
	$(runtest)
# handCard
unittest4: $(TEST_PATH)unittest4.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_unittest4: dominion.c unittest4
	$(runtest)
# build
unittests: $(T_UNIT)
# clean
_unittests = rm -f $(T_UNIT)

############# Cards
#### UNIT TESTS
# adventurer
cardtest1: $(TEST_PATH)cardtest1.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest1: dominion.c cardtest1
	$(runtest)
# council room
cardtest2: $(TEST_PATH)cardtest2.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest2: dominion.c cardtest2
	$(runtest)
# smithy
cardtest3: $(TEST_PATH)cardtest3.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest3: dominion.c cardtest3
	$(runtest)
# minion
cardtest4: $(TEST_PATH)cardtest4.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_cardtest4: dominion.c cardtest4
	$(runtest)
# build
cardtests: $(T_CARD)
# clean
_cardtests = rm -f $(T_CARD)

#### RND TESTS
# smithy
randomtestcard1: $(TEST_PATH)randomtestcard1.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_randomtestcard1: dominion.c randomtestcard1
	$(runtest)
# council room
randomtestcard2: $(TEST_PATH)randomtestcard2.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_randomtestcard2: dominion.c randomtestcard2
	$(runtest)
# adventurer
randomtestadventurer: $(TEST_PATH)randomtestadventurer.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o $(TEST_PATH)$@ $^
gcov_randomtestadventurer: dominion.c randomtestadventurer
	$(runtest)
# build
randomcardtests: $(T_CARD_R)
# clean
_randomcardtests = rm -f $(T_CARD_R)

############# Old...
testDrawCard: testDrawCard.c $(OBJ)
	gcc $(CFLAGS) -o $@ $^
badTestDrawCard: badTestDrawCard.c $(OBJ)
	gcc $(CFLAGS) -o $@ $^
testBuyCard: testDrawCard.c $(OBJ)
	gcc $(CFLAGS) -o $@ $^
testAll: testSuite.c $(OBJ)
	gcc $(CFLAGS) -o $@ $^
runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

#######################################################################
#####################					UTILITY					#########################
#######################################################################
all: playdom player testDrawCard testBuyCard badTestDrawCard unittests cardtests randomcardtests

.PHONY: clean
clean:
	$(_tests)
	-rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
