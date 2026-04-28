// 这个不对
#include <stdlib.h>
#include <string.h>
char *decodeString(char *s)
{
    int len = strlen(s);
    if (len == 1)
        return s;
    int *stack = (int *)malloc(sizeof(int) * len);
    char *res = (char *)malloc(sizeof(char) * 100000);
    int top = -1;
    for (int i = 0; i < len; i++)
    {
        if (s[i] != ']')
        {
            stack[++top] = i;
        }
        else
        {
            while (top != -1 && s[stack[top--]] != '[')
                ;
            int j = top + 2;
            int t = 1;
            int cnt = 0;
            while (top != -1 && s[stack[top]] != '[')
            {
                cnt += t * (s[stack[top]] - '0');
                top--;
            }
        }
    }
}