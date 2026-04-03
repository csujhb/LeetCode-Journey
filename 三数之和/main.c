#include <stdlib.h>

int cmp(const void* p1, const void* p2)
{
	return (*(int*)p1 - *(int*)p2);
}


int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;
	if (numsSize < 3)
	{
		*returnColumnSizes = NULL;
		return NULL;
	}

	int left = 0;
	int right = 0;
	qsort(nums, numsSize,sizeof(int), cmp);
	int capacity = numsSize * numsSize;
	int** result = (int**)malloc(sizeof(int*) * capacity);
	*returnColumnSizes = (int*)malloc(sizeof(int) * capacity);
	for (int i = 0; i < numsSize - 2; i++) {
		if(i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		if (nums[i] > 0)  break;
		left = i + 1;
		right = numsSize - 1;
		while (left < right)
		{
			int sum = nums[i] + nums[left] + nums[right];
			if (sum > 0)
			{
				right--;
			}
			else if (sum < 0)
			{
				left++;
			}
			else {
				result[*returnSize] = (int*)malloc(sizeof(int) * 3);
				result[*returnSize][0] = nums[i];
				result[*returnSize][1] = nums[left];
				result[*returnSize][2] = nums[right];
				(*returnColumnSizes)[*returnSize] = 3;
				(*returnSize)++;
				while (left < right && nums[left] == nums[left + 1])
					left++;
				while (left < right && nums[right] == nums[right - 1] )
					right--;
				left++;
				right--;
			}
		}
	}
	return result;
}
