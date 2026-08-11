// 2026.8.3
#include <string.h>
#include <stdbool.h>
bool isSubsequence(char *s, char *t)
{
    int lens = strlen(s);
    int lent = strlen(t);
    if (lens > lent)
        return false;
    int ps = 0;
    int pt = 0;
    while (ps < lens && pt < lent)
    {
        while (pt < lent && s[ps] != t[pt])
        {
            pt++;
        }
        if (pt >= lent)
            return false;
        ps++;
        pt++;
    }
    if (ps >= lens)
        return true;
    return false;
}

// 最佳方案
#include <stdbool.h>

bool isSubsequence(char *s, char *t)
{
    int ps = 0;
    int pt = 0;

    while (s[ps] != '\0' && t[pt] != '\0')
    {
        if (s[ps] == t[pt])
        {
            ps++;
        }

        pt++;
    }

    return s[ps] == '\0';
}