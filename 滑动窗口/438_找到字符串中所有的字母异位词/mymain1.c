// 2026.6.7
#include <stdlib.h>
#include <string.h>

int isSame(int *p, int *q, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (p[i] != q[i])
            return 0;
    }
    return 1;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findAnagrams(char *s, char *p, int *returnSize)
{
    int s_len = strlen(s);
    int p_len = strlen(p);
    *returnSize = 0;
    if (s_len < p_len)
        return NULL;
    int p_used[26] = {0};
    int s_used[26] = {0};
    int *res = (int *)malloc((s_len - p_len + 1) * sizeof(int));
    for (int i = 0; i < p_len; i++)
    {
        p_used[p[i] - 'a']++;
        s_used[s[i] - 'a']++;
    }
    if (isSame(p_used, s_used, 26))
    {
        res[(*returnSize)] = 0;
        (*returnSize)++;
    }
    for (int i = p_len; i < s_len; i++)
    {
        s_used[s[i] - 'a']++;
        s_used[s[i - p_len] - 'a']--;
        if (isSame(p_used, s_used, 26))
        {
            res[(*returnSize)] = i - p_len + 1;
            (*returnSize)++;
        }
    }
    return res;
}