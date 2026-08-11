// 2026.8.11

#include <string.h>
#include <stdlib.h>

char *minWindow(char *s, char *t)
{
    int lent = strlen(t);
    int lens = strlen(s);
    if (lent > lens)
    {
        char *res = (char *)malloc(sizeof(char));
        res[0] = '\0';
        return res;
    }
    int need[128] = {0};
    int required = 0;
    for (int i = 0; i < lent; i++)
    {
        if (need[t[i]] == 0)
            required++;
        need[t[i]]++;
    }
    int own[128] = {0};
    int owned = 0;
    int start = 0;
    int minLen = 100001;
    int minStart = -1;
    for (int i = 0; i < lens; i++)
    {
        char c = s[i];
        own[c]++;
        if (need[c] > 0 && own[c] == need[c])
        {
            owned++;
        }
        while (start <= i && owned == required)
        {
            char temp = s[start];
            own[temp]--;
            if (need[temp] > 0 && need[temp] > own[temp])
            {
                owned--;
            }
            start++;
            if (owned != required && i - start + 2 < minLen)
            {
                minLen = i - start + 2;
                minStart = start - 1;
            }
        }
    }
    char *res;
    if (minStart >= 0)
    {
        res = (char *)malloc((minLen + 1) * sizeof(char));
        strncpy(res, s + minStart, minLen);
        res[minLen] = '\0';
    }
    else
    {
        res = (char *)malloc(sizeof(char));
        res[0] = '\0';
        return res;
    }

    return res;
}

// 最优解
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char *minWindow(char *s, char *t)
{
    int lens = strlen(s);
    int lent = strlen(t);

    if (lent > lens)
    {
        char *res = (char *)malloc(1);
        res[0] = '\0';
        return res;
    }

    int need[128] = {0};

    /* 统计 t 中每个字符需要多少个 */
    for (int i = 0; i < lent; i++)
    {
        need[(unsigned char)t[i]]++;
    }

    /*
     * missing：
     * 当前窗口还缺多少个字符
     *
     * 注意：这里统计的是字符总数量，
     * 不是字符种类数量。
     */
    int missing = lent;

    int left = 0;

    int minLen = INT_MAX;
    int minStart = -1;

    for (int right = 0; right < lens; right++)
    {
        unsigned char c = s[right];

        /*
         * need[c] > 0
         * 说明这个字符正是我们需要的
         */
        if (need[c] > 0)
        {
            missing--;
        }

        /*
         * 当前窗口加入 c
         *
         * need[c]：
         * > 0  还缺
         * = 0  刚好
         * < 0  多出来了
         */
        need[c]--;

        /*
         * missing == 0
         * 说明窗口已经包含 t 的所有字符
         */
        while (missing == 0)
        {
            int len = right - left + 1;

            if (len < minLen)
            {
                minLen = len;
                minStart = left;
            }

            /* 尝试缩小左边界 */
            unsigned char temp = s[left];

            need[temp]++;

            /*
             * > 0 说明移走 temp 后，
             * 这个字符不够了
             */
            if (need[temp] > 0)
            {
                missing++;
            }

            left++;
        }
    }

    if (minStart == -1)
    {
        char *res = (char *)malloc(1);
        res[0] = '\0';
        return res;
    }

    char *res = (char *)malloc(minLen + 1);

    memcpy(res, s + minStart, minLen);

    res[minLen] = '\0';

    return res;
}