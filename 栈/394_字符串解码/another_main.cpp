/*
时间复杂度： O(L) 或 O(N)，其中 L 是解码后最终字符串的长度。因为 std::string 在 += 拼接时底层需要进行字符的物理拷贝，所以最坏时间复杂度取决于最终生成的字符串总长。

空间复杂度： O(N)。空间消耗主要来自两个栈。在最坏情况下（例如 1[2[3[4[a]]]] 这样的层层嵌套），栈的深度等于原字符串的长度
*/
#include <string>
#include <stack>
#include <cctype>

using namespace std;

class Solution
{
public:
    string decodeString(string s)
    {
        stack<int> numStack;
        stack<string> strStack;

        string currentStr = ""; // 记录当前层的字符串
        int k = 0;              // 记录当前的数字

        for (char c : s)
        {
            if (isdigit(c))
            {
                // 处理多位数字
                k = k * 10 + (c - '0');
            }
            else if (isalpha(c))
            {
                // 普通字符直接追加
                currentStr += c;
            }
            else if (c == '[')
            {
                // 【核心】将当前状态封存入栈，并开启全新的一层
                numStack.push(k);
                strStack.push(currentStr);

                // 重置工作变量，给下一层（括号内的内容）使用
                k = 0;
                currentStr = "";
            }
            else if (c == ']')
            {
                // 【核心】结算当前层，并与上一层拼接

                // 1. 获取要重复的次数
                int repeatTimes = numStack.top();
                numStack.pop();

                // 2. 获取上一层（外层）积攒的字符串
                string prevStr = strStack.top();
                strStack.pop();

                // 3. 将当前层的字符串重复拼接，追加到外层字符串后面
                string temp = currentStr;
                currentStr = prevStr; // 现在的基底是外层字符串
                for (int i = 0; i < repeatTimes; i++)
                {
                    currentStr += temp;
                }
            }
        }

        return currentStr;
    }
};