#ifndef _TESTS_H
#define _TESTS_H

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>

int test_result(int result, char *msg);
void test_header(char *name);
void print_(int *arr, int n, char *msg);

#endif
