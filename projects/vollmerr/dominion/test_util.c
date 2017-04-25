////////////////////////////////////////////////////////////////
// test_util.c
// By: Ryan Vollmer
//
// utility functions for running tests
////////////////////////////////////////////////////////////////
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * Assertion function, prints message on failure
 * @param  result - result to assert
 * @param  msg    - description of what it failed to do
 * @return        - success ? 0 : 1
 */
int test_result(int result, char *msg) {
  if (!result) {
    printf("\nFAILED test...\n It should have %s\n\n", msg);
    return 1;
  }
  return 0;
}

/**
 * Prints header for what is being tested
 * @param name - name to display
 */
void test_header(char *name) {
  printf("\n\n############ Testing %s ############\n\n", name);
}

/**
 * Prints array for testing purposes
 * @param arr - array to display
 * @param n   - size of array
 * @param msg - header to display
 */
void print_(int *arr, int n, char *msg) {
  printf("---- %s ---\n", msg);
  int i;
  for (i=0; i<n; i++) {
    printf("%d : %d\n", i, arr[i]);
  }
  printf("++++++++++++++++++\n");
}