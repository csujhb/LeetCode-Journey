#include <stdlib.h>
#include <string.h>

static int isSame(int* a, int* b) {
    for (int i = 0; i < 26; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
    int sLen = strlen(s);
    int pLen = strlen(p);

    *returnSize = 0;

    if (sLen < pLen) {
        return NULL;
    }

    int need[26] = { 0 };
    int window[26] = { 0 };

    for (int i = 0; i < pLen; i++) {
        need[p[i] - 'a']++;
        window[s[i] - 'a']++;
    }

    int* result = (int*)malloc(sizeof(int) * sLen);

    if (isSame(need, window)) {
        result[(*returnSize)++] = 0;
    }

    for (int i = pLen; i < sLen; i++) {
        window[s[i] - 'a']++;
        window[s[i - pLen] - 'a']--;

        if (isSame(need, window)) {
            result[(*returnSize)++] = i - pLen + 1;
        }
    }

    return result;
}
