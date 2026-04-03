#include <string.h>
#include <stdlib.h>
#include <limits.h>

int isInclude(int* need, int* win) {
    for (int i = 0; i < 128; i++) {
        if (need[i] > win[i]) {
            return 0;
        }
    }
    return 1;
}

char* minWindow(char* s, char* t) {
    int lenS = strlen(s);
    int lenT = strlen(t);

    char* empty = (char*)malloc(1);
    empty[0] = '\0';

    if (lenS < lenT) return empty;

    int left = 0;
    int need[128] = { 0 };
    int window[128] = { 0 };

    int minleft = -1;
    int minLen = INT_MAX;

    for (int i = 0; i < lenT; i++) {
        need[(unsigned char)t[i]]++;
    }

    for (int right = 0; right < lenS; right++) {
        window[(unsigned char)s[right]]++;

        while (isInclude(need, window)) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minleft = left;
            }

            window[(unsigned char)s[left]]--;
            left++;
        }
    }

    if (minleft == -1) {
        return empty;
    }

    free(empty);

    char* result = (char*)malloc(minLen + 1);
    strncpy(result, s + minleft, minLen);
    result[minLen] = '\0';
    return result;
}
