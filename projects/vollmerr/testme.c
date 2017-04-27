#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAX_ASCII 127
#define MIN_ASCII 32
#define BIG_ENOUGH 5
#define THRESHOLD 10

char inputChar() {
  return rand() % (MAX_ASCII - MIN_ASCII) + MIN_ASCII;
}

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

void testme() {
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1) {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
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
  }
}


int main(int argc, char *argv[]) {
    srand(time(NULL));
    testme();
//    printf("\n\n[%s]\n\n", inputString());
    return 0;
}
