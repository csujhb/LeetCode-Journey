#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint16_t Key[26];


void buildKey(Key key, const char* s) {
    uint16_t count[26];
    while (*s) {
        count[*s - 'a']++;
        s++;
    }
    for (int i = 0; i < 26; i++)
        key[i] = (uint16_t)count[i];
}
int getIdx(char a) {
    return (a - 'a');
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
	*returnSize = 0;
	if (strlen(s) < strlen(p)) {
		return NULL;
	}
    int largeLen = strlen(s);
    int wide = strlen(p);
    Key littlekey;
    Key largekey = { 0 };
    buildKey(littlekey, p);
    int right = 0;
    
    int* result = (int*)calloc(largeLen, sizeof(int));
    while (right - wide + 1 < 0) {
        largekey[getIdx(s[right])]++;
        right++;
     }
    int left = right - wide + 1;
    while (right+1 < largeLen) {
        if (memcmp(littlekey, largekey, sizeof(Key)) == 0) {
            result[*returnSize] = left;
            (*returnSize)++;
        }
        largekey[getIdx(s[left])]--;
        left++;
        right++;
        largekey[getIdx(s[right])]++;
    }
    return result;
}
