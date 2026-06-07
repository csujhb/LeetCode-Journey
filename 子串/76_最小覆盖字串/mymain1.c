// s ="a",t ="b"时还是有问题，最主要的是当没有找到时没进行处理，正确版本见下方注释
// 2026.6.6
#include <string.h>
#include <stdlib.h>

char *minWindow(char *s, char *t)
{
    int len_s = strlen(s);
    int len_t = strlen(t);
    if (len_s < len_t)
    {
        char *res = (char *)malloc(sizeof(char));
        res[0] = '\0';
        return res;
    }
    int s_table[128] = {0};
    int t_table[128] = {0};
    int required = 0;
    for (int i = 0; i < len_t; i++)
    {
        if (t_table[t[i]] == 0)
        {
            required++;
        }
        t_table[t[i]]++;
    }
    int own = 0;
    int min_len = 100001;
    int min_start = 0;
    int left = 0, right = 0;
    for (right = 0; right < len_s; right++)
    {
        if (t_table[s[right]] > 0 && s_table[s[right]] == t_table[s[right]] - 1)
        {
            own++;
        }
        s_table[s[right]]++;
        while (own == required && left <= right)
        {
            s_table[s[left]]--;
            left++;
            if (t_table[s[left - 1]] != 0 && s_table[s[left - 1]] == t_table[s[left - 1]] - 1)
            {
                own--;
            }
            if (own != required && right - left + 2 < min_len)
            {
                min_len = right - left + 2;
                min_start = left - 1;
            }
        }
    }
    char *res = (char *)malloc((min_len + 1) * sizeof(char));
    strncpy(res, s + min_start, min_len);
    res[min_len] = '\0';
    return res;
}

// char *minWindow(char *s, char *t)
// {
//     int len_s = strlen(s);
//     int len_t = strlen(t);
//     if (len_s < len_t)
//     {
//         char *res = (char *)malloc(sizeof(char));
//         res[0] = '\0';
//         return res;
//     }

//     int s_table[128] = {0};  // 修正数组大小
//     int t_table[128] = {0};
//     int required = 0;

//     for (int i = 0; i < len_t; i++)
//     {
//         if (t_table[t[i]] == 0)
//         {
//             required++;
//         }
//         t_table[t[i]]++;
//     }

//     int own = 0;
//     int min_len = len_s + 1;  // 用 len_s+1 作为初始最大值
//     int min_start = 0;
//     int left = 0;

//     for (int right = 0; right < len_s; right++)
//     {
//         char c = s[right];
//         s_table[c]++;

//         if (t_table[c] > 0 && s_table[c] == t_table[c])
//         {
//             own++;
//         }

//         while (own == required && left <= right)
//         {
//             // 更新最小窗口
//             if (right - left + 1 < min_len)
//             {
//                 min_len = right - left + 1;
//                 min_start = left;
//             }

//             // 移动左指针
//             char left_char = s[left];
//             s_table[left_char]--;
//             if (t_table[left_char] > 0 && s_table[left_char] < t_table[left_char])
//             {
//                 own--;
//             }
//             left++;
//         }
//     }

//     if (min_len == len_s + 1)  // 未找到
//     {
//         char *res = (char *)malloc(sizeof(char));
//         res[0] = '\0';
//         return res;
//     }

//     char *res = (char *)malloc((min_len + 1) * sizeof(char));
//     strncpy(res, s + min_start, min_len);
//     res[min_len] = '\0';
//     return res;
// }