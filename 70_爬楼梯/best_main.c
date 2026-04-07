int climbStairs(int n) {
    // 基础情况直接返回
    if (n <= 2) return n;
    
    int prev2 = 1; // 相当于 dp[i-2]
    int prev1 = 2; // 相当于 dp[i-1]
    int current = 0;
    
    // 从第 3 阶开始递推
    for (int i = 3; i <= n; i++) {
        current = prev1 + prev2; // 当前 = 前面两个之和
        prev2 = prev1;           // 状态滚动：原来的 prev1 变成下一轮的 prev2
        prev1 = current;         // 状态滚动：当前的 current 变成下一轮的 prev1
    }
    
    return prev1;
}