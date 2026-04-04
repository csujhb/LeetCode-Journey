void reverse(int* arr, int left, int right) {
	while (left < right) {
		int temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left++;
		right--;
	}
}

void rotate(int* nums, int numsSize, int k) {
	if (k == 0) return;
	k = k % numsSize;
	reverse(nums, 0, numsSize-1);
	reverse(nums, 0, k - 1);
	reverse(nums, k, numsSize - 1);
}
