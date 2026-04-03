

#include <limits.h>
int maxSubArray(int* nums, int numsSize) {
	int curPremix =0;
	int minPremix = 0;
	int maxNum = -INT_MAX;
	for (int i = 0; i < numsSize; i++) {
		curPremix += nums[i];
		if (minPremix > curPremix) minPremix = curPremix;//这一行和下一行应交换顺序
		if (maxNum < curPremix - minPremix) maxNum = curPremix - minPremix;//原因:需计算当前前缀和与前面的历史最小前缀和做差值，而不应该使用更新后的历史最小前缀和
		
	}
	return maxNum;
}
