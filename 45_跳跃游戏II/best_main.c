int jump(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;          // 只有一个元素时无需跳跃
    int steps = 0;                        // 跳跃次数
    int curEnd = 0;                       // 当前步数能到达的最远位置
    int farthest = 0;                     // 下一步能到达的最远位置
    for (int i = 0; i < numsSize - 1; i++) {
        // 更新下一步能到达的最远位置
        if (i + nums[i] > farthest) {
            farthest = i + nums[i];
        }
        // 如果到达当前步数的边界，必须再跳一步
        if (i == curEnd) {
            steps++;
            curEnd = farthest;
            if (curEnd >= numsSize - 1) break; // 已能到达末尾，提前结束
        }
    }
    return steps;
}