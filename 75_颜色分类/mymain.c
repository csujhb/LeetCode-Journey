/*
void swap(int *arr,int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
*/
void sortColors(int* nums, int numsSize) {
    int count0=0;
    int count1=0;
    int count2=0;
    for(int i=0;i<numsSize;i++){
        if(nums[i]==0){
            count0++;
        }else if(nums[i]==1){
            count1++;
        }else{
            count2++;
        }
    }
    int idx=0;
    while(count0--){
        nums[idx++]=0;
    }
     while(count1--){
        nums[idx++]=1;
    }
     while(count2--){
        nums[idx++]=2;
    }
}