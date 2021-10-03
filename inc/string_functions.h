#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void hm_swapChar(char *s1, char *s2);
void hm_reverse(char str[], int length);
char* hm_itoa(int num, char* str, int base);
char* hm_concatThreeStrings(const char* AbsPath, int fileNumber, const char* fExt);
char *mx_strcat(char *s1, const char *s2);
char *mx_itoa(int number);

#endif
