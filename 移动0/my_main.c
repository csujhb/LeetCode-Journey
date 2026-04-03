


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void moveZeroes(int* nums, int numsSize) {
	if (numsSize == 1) return;
	int i = 0;
	int flag;
	for (i = 0; i < numsSize; i++)
	{
		if (nums[i] != 0) continue;
		flag = i + 1;
		while (flag<numsSize||nums[flag] == 0)
			flag++;
		if(nums[flag] == 0)
		swap(&nums[i], &nums[flag]);
	}
}
