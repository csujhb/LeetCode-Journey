// 2026.8.12

#include <stdlib.h>
#include <string.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *partitionLabels(char *s, int *returnSize)
{
    int len = strlen(s);
    if (len == 1)
    {
        *returnSize = 1;
        int *res = (int *)malloc(sizeof(int));
        res[0] = 1;
        return res;
    }
    *returnSize = 0;
    int *res = (int *)malloc(len * sizeof(int));
    int last[26];

    for (int i = 0; i < len; i++)
    {
        last[s[i] - 'a'] = i;
    }
    int right = 0; // last[s[0] - 'a'];
    int left = 0;
    for (int i = 0; i < len; i++)
    {
        if (right < last[s[i] - 'a'])
        {
            right = last[s[i] - 'a'];
        }
        if (i == right)
        {
            res[(*returnSize)++] = right - left + 1;
            left = right + 1;
        }
    }
    return res;
}