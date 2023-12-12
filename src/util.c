#include <utils.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Concatenate two strings
 *
 * @param s1 First string
 * @param s2 Second string
 *
 * @return pointer to the concatenated string
 * */
char *concat(const char *s1, const char *s2) {
  char *result = malloc(strlen(s1) + strlen(s2) + 1);

  strcpy(result, s1);
  strcat(result, s2);

  return result;
}

/**
 * Convert unsigned int to string
 *
 * @param num Unsigned int
 *
 * @return pointer to the string
 * */
char *intToString(unsigned int num) {
  char *str = malloc(sizeof(char) * 10);

  sprintf(str, "%d", num);

  return str;
}
