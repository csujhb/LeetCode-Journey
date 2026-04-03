#include <limits.h>
int maxSubArray(int* nums, int numsSize) {
	int curPremix = 0;
	int minPremix = 0;
	int maxNum = -INT_MAX;
	for (int i = 0; i < numsSize; i++) {
		curPremix += nums[i];
		if (maxNum < curPremix - minPremix) maxNum = curPremix - minPremix;
		if (minPremix > curPremix) minPremix = curPremix;
	}
	return maxNum;
}


/*
在 maxSubArray 函数中，curPremix 和 minPremix 初始化为 0 是为了正确实现基于前缀和的最大子数组和算法。

curPremix 初始化为 0：表示尚未遍历任何元素时的前缀和（即空数组的和）。随着遍历，curPremix 逐步累加当前元素，形成当前前缀和。

minPremix 初始化为 0：表示到当前位置之前的最小前缀和，初始时也取空前缀的和 0。这样，在计算 curPremix - minPremix 时，
如果子数组从数组开头开始，差值就是当前前缀和本身，从而正确得到以当前元素结尾的最大子数组和。

这种初始化方式能正确处理所有元素为负数的情况：此时 curPremix 始终为负，minPremix 保持为 0，curPremix - minPremix 就是当前前缀和，
最终 maxNum 会取到这些负数中的最大值，即最大的那个元素。如果不将 minPremix 初始化为 0，而改为其他值（如 INT_MAX），则可能导致计
算错误或无法覆盖从开头开始的子数组。因此，初始化为 0 是算法正确性的关键。
*/
