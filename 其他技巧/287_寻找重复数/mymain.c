/*
将数组视为一个链表：
索引视为一个节点，其对应的值视为其指向的下一个结点的索引

这样，当数组存在重复数字时，可视为链表存在环，可以利用寻找链表环的思路找到重复数字
因没节点会指向节点0,因此起始双指针可指向0节点。
*/
int findDuplicate(int* nums, int numsSize) {
    int fast=nums[nums[0]];
    int slow=nums[0];
    while(fast!=slow){
        slow=nums[slow];
        fast=nums[nums[fast]];
    }
    fast=0;
    while(fast!=slow){
        slow=nums[slow];
        fast=nums[fast];
    }
    return slow;
}