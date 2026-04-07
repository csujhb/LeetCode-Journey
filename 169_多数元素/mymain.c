
int majorityElement(int* nums, int numsSize) {
    int res=nums[0];
    int count=1;
    for(int i=1;i<numsSize;i++){
        if(nums[i]!=res){
            if(count>0)  {
                count--;
            }
            else if(count==0) {
                count=1;
                res=nums[i];
            }
        }else{
            count++;
        }
    }
    return res;
}