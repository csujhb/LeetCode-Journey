#include <stdlib.h>
#include <string.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *partitionLabels(char *s, int *returnSize)
{
    int last[26] = {0};
    int len = strlen(s);
    int *res = (int *)calloc(len, sizeof(int));
    for (int i = 0; i < len; i++)
    {
        last[s[i] - 'a'] = i;
    }
    int count = 0;
    int left = 0;
    int right = 0;
    for (int i = 0; i < len; i++)
    {
        int curLast = last[s[i] - 'a'];
        if (curLast > right)
        {
            right = curLast;
        }
        if (i == right)
        {
            res[count++] = i - left + 1;
            left = i + 1;
        }
    }
    *returnSize = count;
    return res;
}