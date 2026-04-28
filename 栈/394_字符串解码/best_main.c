#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 递归工作函数
// 传入原字符串 s，以及当前遍历到的全局索引指针 i
char *dfs(char *s, int *i)
{
    // 初始分配一块内存用于存放当前层的解析结果
    int capacity = 50;
    char *res = (char *)malloc(capacity * sizeof(char));
    res[0] = '\0';
    int len = 0; // 当前层结果字符串的长度

    int k = 0; // 记录当前的重复次数

    while (s[*i] != '\0')
    {
        char c = s[*i];

        if (isdigit(c))
        {
            // 1. 如果是数字：累加计算 k (注意数字可能是多位数，比如 "100[a]")
            k = k * 10 + (c - '0');
            (*i)++;
        }
        else if (c == '[')
        {
            // 2. 如果是左括号：开启新的一层递归！
            (*i)++;                   // 跳过 '['
            char *subStr = dfs(s, i); // 拿到了内层解码好的字符串
            (*i)++;                   // 跳过 ']'，从子递归回来时，*i 停在 ']' 上，需要再走一步

            // 将拿到的 subStr 重复 k 次拼接到当前 res 的尾部
            int subLen = strlen(subStr);
            // 动态扩容，确保内存够用 (加 1 是为了留给 '\0')
            while (len + k * subLen + 1 > capacity)
            {
                capacity *= 2;
                res = (char *)realloc(res, capacity * sizeof(char));
            }

            // 高效拼接：每次都在尾部写入，不用 strcat 以避免 O(N^2) 退化
            for (int j = 0; j < k; j++)
            {
                strcpy(res + len, subStr);
                len += subLen;
            }

            // 拼接完后，清空当前的数字，准备迎接下一段
            k = 0;
            free(subStr); // 释放内层申请的内存，防止内存泄漏
        }
        else if (c == ']')
        {
            // 3. 如果遇到右括号：当前层的任务结束，直接跳出循环返回
            break;
        }
        else
        {
            // 4. 如果是普通字母：直接追加到 res 尾部
            if (len + 2 > capacity)
            {
                capacity *= 2;
                res = (char *)realloc(res, capacity * sizeof(char));
            }
            res[len] = c;
            len++;
            res[len] = '\0';
            (*i)++;
        }
    }

    return res;
}

// 主入口函数
char *decodeString(char *s)
{
    int i = 0; // 全局遍历索引
    return dfs(s, &i);
}