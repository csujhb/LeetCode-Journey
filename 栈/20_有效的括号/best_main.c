/*
时间复杂度：O(N)。其中N为字符串长度，只需遍历一遍字符串，每次栈操作耗时为O(1)。
空间复杂度：O(N)。最坏情况下（全部为左括号），我们需要将所有字符压入栈中。
*/
#include <stdbool.h>
#include <string.h>

bool isValid(char * s) {
    int len = strlen(s);
    
    // 【剪枝优化】如果字符串长度是奇数，绝对不可能完全匹配
    if (len % 2 != 0) return false;

    // 用数组模拟栈（最坏情况下全是左括号，栈的大小需要等于字符串长度）
    char stack[len];
    int top = -1; // 栈顶指针，-1 代表空栈

    for (int i = 0; i < len; i++) {
        char c = s[i];

        // 1. 遇到左括号，入栈
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } 
        // 2. 遇到右括号，出栈匹配
        else {
            // 如果栈为空，说明多出了右括号
            if (top == -1) return false;

            // 获取栈顶的左括号
            char topChar = stack[top];

            // 检查是否匹配
            if ((c == ')' && topChar == '(') ||
                (c == ']' && topChar == '[') ||
                (c == '}' && topChar == '{')) {
                top--; // 匹配成功，栈顶元素出栈
            } else {
                return false; // 括号类型不匹配
            }
        }
    }

    // 3. 遍历完毕后，如果栈为空则说明全部合法
    return top == -1;
}