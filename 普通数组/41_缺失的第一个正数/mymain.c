//这段代码在提交时显示超时

int firstMissingPositive(int* nums, int numsSize) {
	for (int i = 0; i < numsSize; i++) {
		while (nums[i] <= numsSize && nums[i] >= 1) {
			if (nums[i] - 1 != i) {
				int temp = nums[nums[i] - 1];
				nums[nums[i] - 1] = nums[i];
				nums[i] = temp;
			}
			else {
				break;
			}
		}
	}
	for (int i = 0; i < numsSize; i++) {
		if (nums[i] != i + 1) {
			return i + 1;
		}
	}
	return numsSize + 1;
}
