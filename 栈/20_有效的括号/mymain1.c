#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
bool isValid(char *s)
{
    int len = strlen(s);
    if (len % 2 == 1)
        return false;
    int *stack = (int *)malloc(sizeof(int) * len);
    int top = -1;
    for (int i = 0; i < len; i++)
    {
        char a = s[i];
        if (a == '[' || a == '{' || a == '(')
        {
            stack[++top] = a;
        }
        else
        {
            if (top == -1)
                return false;
            char topChar = stack[top];

            if ((a == ')' && topChar == '(') ||
                (a == ']' && topChar == '[') ||
                (a == '}' && topChar == '{'))
            {
                top--;
            }
            else
            {
                return false;
            }
        }
    }
    free(stack);
    return top == -1;
}