// 2026.6.7
#include <string.h>
int lengthOfLongestSubstring(char *s)
{
    int len = strlen(s);
    if (len <= 1)
        return len;
    int last[128];
    for (int i = 0; i < 128; i++)
    {
        last[i] = -1;
    }
    int left = 0;
    int max_len = 0;
    for (int i = 0; i < len; i++)
    {
        if (last[s[i]] >= 0 && left <= last[s[i]]) // 第一次时left<=last[s[i]]没加
        {
            left = last[s[i]] + 1;
        }
        if (max_len < i - left + 1)
            max_len = i - left + 1;
        last[s[i]] = i;
    }
    return max_len;
}