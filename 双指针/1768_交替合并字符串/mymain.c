// 2026.8.3
#include <string.h>
#include <stdlib.h>
char *mergeAlternately(char *word1, char *word2)
{
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    char *res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    int i = 0, k = 0;
    if (len1 > len2)
    {
        while (i < len2)
        {
            res[k++] = word1[i];
            res[k++] = word2[i];
            i++;
        }
        while (i < len1)
        {
            res[k++] = word1[i++];
        }
    }
    else
    {
        while (i < len1)
        {
            res[k++] = word1[i];
            res[k++] = word2[i];
            i++;
        }
        while (i < len2)
        {
            res[k++] = word2[i++];
        }
    }

    res[len1 + len2] = '\0';
    return res;
}