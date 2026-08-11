#include <stdbool.h>
#include <string.h>

bool isPalindrome(char *s)
{
    int len = strlen(s);
    int i = 0;
    int k = 0;

    /* 将有效字符整理到字符串前面，并把大写字母转为小写 */
    while (i < len)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[k++] = s[i] + ('a' - 'A');
        }
        else if ((s[i] >= 'a' && s[i] <= 'z') ||
                 (s[i] >= '0' && s[i] <= '9'))
        {
            s[k++] = s[i];
        }

        i++;
    }

    int left = 0;
    int right = k - 1;

    while (left < right)
    {
        if (s[left] != s[right])
        {
            return false;
        }

        left++;
        right--;
    }

    return true;
}