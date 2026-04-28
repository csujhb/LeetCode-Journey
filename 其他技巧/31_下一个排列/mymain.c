void reverse(int *arr,int left,int right){
    while(left<right){
        int temp=arr[left];
        arr[left]=arr[right];
        arr[right]=temp;
        left++;
        right--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    if(numsSize==1) return;
    int right=numsSize-2;
    while(right>=0&&nums[right]>=nums[right+1]){
        right--;
    }
    if(right<0) {
        reverse(nums,0,numsSize-1);
        return;
    }
    int i=numsSize-1;
    while(nums[i]<=nums[right]) i--;
    int temp=nums[i];
    nums[i]=nums[right];
    nums[right]=temp;
    reverse(nums,right+1,numsSize-1);
}