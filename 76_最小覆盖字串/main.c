#include <stdlib.h>
#include <string.h>
#include <limits.h>

char* minWindow(char* s, char* t) {
    int lenS = strlen(s);
    int lenT = strlen(t);

    if (lenS < lenT) {
        char* ans = (char*)malloc(1);
        ans[0] = '\0';
        return ans;
    }

    int need[128] = { 0 };
    int window[128] = { 0 };

    int required = 0;  // t中需要满足的不同字符种类数
    for (int i = 0; i < lenT; i++) {
        if (need[(unsigned char)t[i]] == 0) {
            required++;
        }
        need[(unsigned char)t[i]]++;
    }

    int formed = 0;
    int left = 0, right = 0;
    int minLen = INT_MAX;
    int start = 0;

    while (right < lenS) {
        char c = s[right];
        window[(unsigned char)c]++;

        // 如果当前字符数量刚好达到 need 要求，则 formed++
        if (need[(unsigned char)c] > 0 &&
            window[(unsigned char)c] == need[(unsigned char)c]) {
            formed++;
        }

        // 当前窗口已经满足要求，开始尝试缩小左边界
        while (left <= right && formed == required) {
            int windowLen = right - left + 1;
            if (windowLen < minLen) {
                minLen = windowLen;
                start = left;
            }

            char d = s[left];
            window[(unsigned char)d]--;

            // 如果移出后导致某个必要字符不够了，formed--
            if (need[(unsigned char)d] > 0 &&
                window[(unsigned char)d] < need[(unsigned char)d]) {
                formed--;
            }

            left++;
        }

        right++;
    }

    if (minLen == INT_MAX) {
        char* ans = (char*)malloc(1);
        ans[0] = '\0';
        return ans;
    }

    char* ans = (char*)malloc(minLen + 1);
    strncpy(ans, s + start, minLen);
    ans[minLen] = '\0';
    return ans;
}
