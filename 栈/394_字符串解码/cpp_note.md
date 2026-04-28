# 📚 算法学习笔记补充：字符串解码 (C++ 进阶篇)

##  核心解题思想：双栈法 (Double Stack)

在 C++ 中，我们不再依赖系统调用栈（递归），而是手动维护两个显式的栈，通过**迭代**的方式处理嵌套逻辑。

* **数字栈 (`numStack`)**：专门存重复次数 `k`。
* **字符串栈 (`strStack`)**：专门存“进入括号前”已经拼好的字符串。



---

##  状态转移逻辑 (迭代过程)

我们维护两个施工变量：`currentStr` (当前层字符串) 和 `k` (当前重复次数)。遍历字符串时：

1.  **数字 (`0-9`)**：
    * `k = k * 10 + (c - '0')`（处理多位数字）。
2.  **左括号 (`[`)**：**“封存现场”**。
    * 将当前的 `k` 压入 `numStack`。
    * 将当前的 `currentStr` 压入 `strStack`。
    * **重置** `k` 和 `currentStr` 为初始值，开始处理括号内的新任务。
3.  **右括号 (`]`)**：**“结算合并”**。
    * 从 `numStack` 弹出重复次数 `times`。
    * 从 `strStack` 弹出上一层的前缀字符串 `lastStr`。
    * 将当前的 `currentStr` 重复 `times` 次，并接在 `lastStr` 后面。
    * 更新后的结果重新赋值给 `currentStr`，作为新的当前层。
4.  **普通字母**：
    * 直接追加到 `currentStr` 末尾。

---

##  C++ 代码实现 (标准模板)

```cpp
#include <string>
#include <stack>
#include <cctype>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> numStack;     // 存储次数 k
        stack<string> strStack;  // 存储进入括号前的字符串前缀
        
        string currentStr = "";
        int k = 0;

        for (char c : s) {
            if (isdigit(c)) {
                // 1. 累加数字
                k = k * 10 + (c - '0');
            } 
            else if (c == '[') {
                // 2. 遇到左括号，把当前的次数和字符串压入各自的栈
                numStack.push(k);
                strStack.push(currentStr);
                
                // 重置变量，准备处理括号内的内容
                k = 0;
                currentStr = "";
            } 
            else if (c == ']') {
                // 3. 遇到右括号，弹出栈顶状态进行拼接
                int repeatTimes = numStack.top();
                numStack.pop();
                
                string prevStr = strStack.top();
                strStack.pop();
                
                // 将当前字符串重复 repeatTimes 次并拼接到上一层前缀后
                string temp = "";
                for (int i = 0; i < repeatTimes; i++) {
                    temp += currentStr;
                }
                currentStr = prevStr + temp;
            } 
            else {
                // 4. 普通字母直接追加
                currentStr += c;
            }
        }
        
        return currentStr;
    }
};
```

---

##  C 语言递归 vs. C++ 栈：深度对比

| 特性 | C 语言 (递归法) | C++ (双栈法) |
| :--- | :--- | :--- |
| **底层工具** | 系统调用栈 | `std::stack` 容器 |
| **内存管理** | 需手动 `malloc/free/realloc` | `std::string` 自动扩容与管理 |
| **逻辑重心** | 难点在于全局指针 `i` 的同步 | 难点在于 `[` 和 `]` 时的状态压栈与还原 |
| **安全性** | 嵌套过深时有“爆栈”风险 | 相对更稳定，内存随堆空间动态变化 |
| **适用场景** | 内存极度受限、底层嵌入式开发 | 标准算法面试、工程开发 |

## 💡 学习心法

* **嵌套即栈**：凡是涉及“括号嵌套”、“由内向外”处理的问题，首选栈或递归。
* **状态封存**：在 C++ 迭代法中，遇到 `[` 时的“压栈”动作本质上就是在封存当前的上下文，以便在 `]` 时能回到过去。
* **C++ 优势**：在处理字符串类题目时，C++ 的 `string` 类能极大地减少我们在指针操作和内存申请上的 Bug。