#include <stdio.h>

int lengthOfLongestSubstring(char* s) {
    int last[128];
    int i;
    // 初始化为 -1，表示字符还没出现过
    for (i = 0; i < 128; i++) {
        last[i] = -1;
    }

    int maxLen = 0;
    int left = 0;// 滑动窗口左边界

    for (i = 0; s[i] != '\0'; i++) {
        // 如果当前字符出现过，并且出现在当前窗口内
        if (last[(int)s[i]] >= left) {
            left = last[(int)s[i]] + 1;
        }

        last[(int)s[i]] = i;

        int len = i - left + 1;
        if (len > maxLen) {
            maxLen = len;
        }
    }

    return maxLen;
}

int main() {
    char s1[] = "abcabcbb";
    char s2[] = "bbbbb";
    char s3[] = "pwwkew";

    printf("s1 = %s, result = %d\n", s1, lengthOfLongestSubstring(s1));
    printf("s2 = %s, result = %d\n", s2, lengthOfLongestSubstring(s2));
    printf("s3 = %s, result = %d\n", s3, lengthOfLongestSubstring(s3));

    return 0;
}
