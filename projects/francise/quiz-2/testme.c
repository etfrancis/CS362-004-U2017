#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


/******************
 * inputChar -- returns a random character between 32 (ASCII space) and 126 (ASCII ~)
 ******************/
char inputChar()
{
    return rand() % 95 + 32;
}

/******************
 * inputString -- returns a pointer to a character buffer with random string of length specified by input parameter.
 * Takes address of char buffer, strength length (including terminal \0) as inputs.
 * Includes random but high-likelihood tests to replace characters in positions 0...5 with values r-e-s-e-t-\0, to ensure
 * coverage of these important input values, to increase overall branch coverage
 ******************/
char *inputString(char* str, size_t size)
{
    str[size-1] = '\0';
    int i;
    for(i = 0; i < size -1; i++)
        str[i] = rand() % 95 + 32;
    if(rand() % 3 == 0)
        str[0] = 'r';
    if(rand() % 3 == 0)
        str[1] = 'e';
    if(rand() % 3 == 0)
        str[2] = 's';
    if(rand() % 3 == 0)
        str[3] = 'e';
    if(rand() % 3 == 0)
        str[4] = 't';
    if(rand() % 3 == 0)
        str[5] = '\0';
    return str;
}

/******************
 * Function under test -- added parameter to accept character buffer for testing purposes, to avoid memory leaks
 ******************/
void testme(char* buffer, int buffer_size)
{
  int tcCount = 0;
  char *s = buffer;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString(s, rand() % (buffer_size - 5) + 6); //tests using a random string length between 6 and max buffer size
    
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
      printf("error \n");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    char* test_buffer = malloc(20 * sizeof(char));
    srand(time(NULL));
    testme(test_buffer, sizeof(test_buffer));
    free(test_buffer);
    return 0;
}
