#include "string_functions.h"

void hm_swapChar(char *s1, char *s2) {
    char tmp = *s2;
    *s2 = *s1;
    *s1 = tmp;
}

void hm_reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    {
        hm_swapChar(str+start, str+end);
        //swap(*(str+start), *(str+end)); 
        start++; 
        end--; 
    } 
} 

char* hm_itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    bool isNegative = false;
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    }
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    }
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    }
    if (isNegative) 
        str[i++] = '-';
    str[i] = '\0';
    hm_reverse(str, i);
    return str; 
} 


char* hm_concatThreeStrings(const char* AbsPath, int fileNumber, const char* fExt) {
    char *fileNumberStr = (char*)malloc(sizeof(char) * 4);
    fileNumberStr = hm_itoa(fileNumber, fileNumberStr, 10);
    int fStrLen = strlen(AbsPath) + strlen(fileNumberStr) + strlen(AbsPath);
    char *ResStr = (char*)malloc(sizeof(char) * (fStrLen+10));
    strcat(ResStr, AbsPath);
    strcat(ResStr, fileNumberStr);
    strcat(ResStr, fExt);
    free(fileNumberStr);
    return ResStr;
}
