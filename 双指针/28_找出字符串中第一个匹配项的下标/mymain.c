// 2026.8.4
int strStr(char *haystack, char *needle)
{
    if (*needle == '\0')
        return 0;

    for (int i = 0; haystack[i] != '\0'; i++)
    {
        int j = 0;

        while (needle[j] != '\0' &&
               haystack[i + j] != '\0' &&
               haystack[i + j] == needle[j])
        {
            j++;
        }

        if (needle[j] == '\0')
        {
            return i;
        }
    }

    return -1;
}

// 更优做法：KMP算法
#include <string.h>
#include <stdlib.h>

int strStr(char *haystack, char *needle)
{
    int n = strlen(haystack);
    int m = strlen(needle);

    if (m == 0)
        return 0;

    if (m > n)
        return -1;

    /* next[i]表示needle[0...i]的最长相等前后缀长度 */
    int *next = malloc(sizeof(int) * m);
    if (next == NULL)
        return -1;

    next[0] = 0;

    /* 构造next数组 */
    for (int i = 1, j = 0; i < m;)
    {
        if (needle[i] == needle[j])
        {
            next[i] = j + 1;
            i++;
            j++;
        }
        else if (j > 0)
        {
            j = next[j - 1];
        }
        else
        {
            next[i] = 0;
            i++;
        }
    }

    /* 使用KMP匹配 */
    for (int i = 0, j = 0; i < n;)
    {
        if (haystack[i] == needle[j])
        {
            i++;
            j++;

            /* needle全部匹配完成 */
            if (j == m)
            {
                free(next);
                return i - m;
            }
        }
        else if (j > 0)
        {
            j = next[j - 1];
        }
        else
        {
            i++;
        }
    }

    free(next);
    return -1;
}