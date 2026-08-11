// 2026.8.11
#include <stdlib.h>
#include <string.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int isSame(int *p1, int *p2)
{
    for (int i = 0; i < 26; i++)
    {
        if (p1[i] != p2[i])
            return 0;
    }
    return 1;
}

int *findAnagrams(char *s, char *p, int *returnSize)
{

    int lens = strlen(s);
    int lenp = strlen(p);
    *returnSize = 0;
    if (lenp > lens)
        return NULL;
    int *res = (int *)malloc((lens - lenp + 1) * sizeof(int));
    int need[26] = {0};
    int own[26] = {0};
    for (int i = 0; i < lenp; i++)
    {
        need[p[i] - 'a']++;
    }
    for (int i = 0; i < lenp; i++)
    {
        own[s[i] - 'a']++;
    }
    if (isSame(need, own))
        res[(*returnSize)++] = 0;
    for (int i = lenp; i < lens; i++)
    {
        own[s[i - lenp] - 'a']--;
        own[s[i] - 'a']++;
        if (isSame(need, own))
            res[(*returnSize)++] = i - lenp + 1;
    }
    return res;
}