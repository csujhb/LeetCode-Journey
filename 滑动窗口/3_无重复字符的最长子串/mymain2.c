// 2026.8.11
#include <string.h>
int lengthOfLongestSubstring(char *s)
{
    int lens = strlen(s);
    if (lens <= 1)
        return lens;
    int last[128]; // last数组不能初始化为0，会影响下面的判断
    for (int i = 0; i < 128; i++)
    {
        last[i] = -1;
    }
    int left = 0;
    int res = 0;
    for (int i = 0; i < lens; i++)
    {
        char c = s[i];
        if (last[(int)c] >= left)
        {
            left = last[(int)c] + 1;
        }
        if (i - left + 1 > res)
            res = i - left + 1;
        last[(int)c] = i;
    }
    return res;
}