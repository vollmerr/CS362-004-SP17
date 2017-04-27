////////////////////////////////////////////////////////////
// Ryan Vollmer
// Results of random tester development
////////////////////////////////////////////////////////////

///////////////       Pre-Assumptions    ////////////////////
/*
 * These tests are running with the inital assumption that:
 *  -> over 2 million iterations is too many/ too much runtime and therefore a failure.
 *  -> random letters used are bound to the ASCII table in its entirety from 0-127
 *  -> makes assumption that all strings from input string are at least as big as the required size
 *    for testing as there is no bounds checking. Generating string of random length would
 *    would exponentially increase possible number of iterations.
 */

////////////////////////////////////////////////////////////
//  Attempt 1
//  - Uses Pre-Assumptions to set up inital testing
////////////////////////////////////////////////////////////
#define MAX_ASCII 127     // highest value on ASCII table of characters
#define BIG_ENOUGH 7      // larger than any string ever needed for these tests
// inputChar => return any random char in ASCII range (0-127)
char inputChar() {
  return rand() % (MAX_ASCII + 1);
}
// inputString => char array of size 11 (10 plus '\n'), each letter filled with inputChar's return value
char* inputString() {
  char* str;
  str = malloc(sizeof(char) * BIG_ENOUGH + 1);
  int i = 0;
  while (i < BIG_ENOUGH) {
    str[i] = inputChar();
    i++;
  }
  str[i] = '\0';
  return str;
}

/**
 * Result:
 *  -> Fine for testing single char.
 *    -> Almost immediately got to stage 9.
 *  -> Too random of input for string
 *    -> Ran past 2 million for iteration and still no error for string.
 *    -> String's combination of 6 chars that happen to be in that order is too small of a chance for reasonable test runtime.
 */

////////////////////////////////////////////////////////////
//  Attempt 2
//    - Reduction of letters in the random string to only be as long
//    as the string being tested for.
//    - The last character is now always guarenteed to be a null terminator ('\0').
//    - Only 5 instead of 6 random characters therfore need to lined up.
////////////////////////////////////////////////////////////
#define BIG_ENOUGH 5    // changed to size of string test is looking for

/**
 * Result:
 *  -> Still instantly gets to stage 9, but runs with iterations of over 2 million.
 *  -> Still too many permutations
 */

////////////////////////////////////////////////////////////
//  Attempt 3
//    - Reduction of random letters returned from inputChar
//     to only standard keyboard letters in the range 32-126
////////////////////////////////////////////////////////////
#define MIN_ASCII 32 // add value of lowest ASCII character to use (space)
// inputChar => random char in ASCII range (32-126)
char inputChar() {
  return rand() % (MAX_ASCII - MIN_ASCII) + MIN_ASCII;
}

/**
 * Result:
 *  -> Still instantly gets to stage 9, but runs with iterations of over 2 million.
 *  -> Still too many permutations
 */

////////////////////////////////////////////////////////////
//  Attempt 4
//    - Reduction of random letters in inputStrings return
//      value to only lower cased letters (ASCII 97-122)
////////////////////////////////////////////////////////////
#define MAX_LOW_ALPHA 122   // add definition of highest lowercase character (z)
#define MIN_LOW_ALPHA 97    // add definition of lowest lowercase character (a)
// inputString => string with random lowercase characters
char* inputString() {
  char* str;
  str = malloc(sizeof(char) * BIG_ENOUGH + 1);
  int i = 0;
  while (i < BIG_ENOUGH) {
    str[i] = rand() % (MAX_LOW_ALPHA - MIN_LOW_ALPHA) + MIN_LOW_ALPHA;
    i++;
  }
  str[i] = '\0';
  return str;
}

/**
 * Result:
 *  -> Still instantly gets to stage 9, but runs with iterations of over 2 million.
 *  -> Still too many permutations...
 *  -> Probably should have done some math on possible permutations....
 */

////////////////////////////////////////////////////////////
//  Attempt 5
//    - changing characters in inputString back to being return
//      of inputChar, however now having a smaller addtional chance that
//      each character will be its correct value
////////////////////////////////////////////////////////////
// removed min and max low alpha defines...
#define THRESHOLD 10    // add threshold for how often correct character in string
// inputString => string with random characters and high chance of correct letters
char* inputString() {
  char* str;
  char expected[BIG_ENOUGH+1] = "reset";
  str = malloc(sizeof(char) * BIG_ENOUGH + 1);
  int i = 0;
  while (i < BIG_ENOUGH) {
    if (!(rand() % THRESHOLD)) {
      str[i] = expected[i];
    }
    else {
      str[i] = inputChar();
    }
    i++;
  }
  str[i] = '\0';
  return str;
}

/**
 * Result:
 *  -> Sucessfully finds the string "reset" and breaks free
 *  -> On average 30000 to 70000 iterations to find
 *  -> could try higher threshold values if wanting more randomness
 */
