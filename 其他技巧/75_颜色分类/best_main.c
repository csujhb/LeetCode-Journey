void sortColors(int* nums, int numsSize) {
    int p0 = 0;                 // 指向下一个 0 应该存放的位置
    int p2 = numsSize - 1;      // 指向下一个 2 应该存放的位置
    int i = 0;                  // 当前遍历指针

    // 注意这里是 i <= p2，因为 i 超过 p2 意味着后面的元素全都是处理好的 2 了
    while (i <= p2) {
        if (nums[i] == 0) {
            // 遇到 0，和 p0 交换，p0 和 i 都向后移动
            int temp = nums[i];
            nums[i] = nums[p0];
            nums[p0] = temp;
            p0++;
            i++;
        } 
        else if (nums[i] == 2) {
            // 遇到 2，和 p2 交换，p2 向前移动
            // 注意：此时 i 不动，因为从后面换过来的数字还没检查过
            int temp = nums[i];
            nums[i] = nums[p2];
            nums[p2] = temp;
            p2--;
        } 
        else {
            // 遇到 1，跳过即可
            i++;
        }
    }
}